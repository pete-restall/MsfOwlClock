#include <array>
#include <concepts>
#include <cstdint>
#include <tuple>
#include <type_traits>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/di/Container.hh"

#include "../../NonDeterminism.hh"

using namespace mettle;
using namespace smeg::kernel::di;

namespace smeg::tests::unit::kernel::di
{
	struct ClassWithDefaultConstructor
	{
	};

	template <typename T>
	struct Value
	{
		T value;

		Value(T value) :
			value(value)
		{
		}
	};

	template <typename... T>
	struct ClassRequiringInjection
	{
		std::tuple<Value<T> ...> injected;

		ClassRequiringInjection(T... injected) :
			injected{Value<T>(injected) ...}
		{
		}
	};

	struct ClassRequiringToken
	{
		ClassRequiringToken(std::uint32_t token) :
			token(token)
		{
		}

		const std::uint32_t token;
	};

	suite<> containerTest("Container Tests", [](auto &unit)
	{
		// all factories should be able to take up to the following:
		// factory<TContainer, T, TKey, ResolutionContext<TContext>>(container, context)

		// resolve<T>()
		// resolve<T, TKey>()

		// resolve<T>(TContext &)
		// resolve<T, TKey>(TContext &)

		unit.test("resolve_calledWithUnregisteredClassWithDefaultConstructor_expectClassIsConstructed", []()
		{
			const Container container;
			auto resolved(container.resolve<ClassWithDefaultConstructor>());
			expect(std::same_as<decltype(resolved), ClassWithDefaultConstructor>, equal_to(true));
		});

		unit.test("resolve_calledWithUnregisteredClassWithConstructorTakingAnotherWithDefaultConstructor_expectClassIsConstructed", []()
		{
			using RequestedClass = ClassRequiringInjection<ClassWithDefaultConstructor>;
			const Container container;
			auto resolved(container.resolve<RequestedClass>());
			expect(std::same_as<decltype(resolved), RequestedClass>, equal_to(true));
		});

		unit.test("resolve_calledWithUnregisteredClassWithConstructorTakingTwoOthersWithDefaultConstructors_expectClassIsConstructed", []()
		{
			using RequestedClass = ClassRequiringInjection<ClassWithDefaultConstructor, ClassWithDefaultConstructor>;
			const Container container;
			auto resolved(container.resolve<RequestedClass>());
			expect(std::same_as<decltype(resolved), RequestedClass>, equal_to(true));
		});

		unit.test("resolve_calledWithUnregisteredClassWithConstructorRequiringNestedInjection_expectClassIsConstructed", []()
		{
			using RequestedClass = ClassRequiringInjection<ClassRequiringInjection<ClassWithDefaultConstructor>>;
			const Container container;
			auto resolved(container.resolve<RequestedClass>());
			expect(std::same_as<decltype(resolved), RequestedClass>, equal_to(true));
		});

		unit.test("resolve_calledWithTypeThatIsRegisteredDependencyFromStaticFactory_expectClassIsConstructed", []()
		{
			constexpr std::uint32_t registeredToken = 125694390;
			const auto container(Container<>().registerFactory([]() static { return registeredToken; }));
			auto resolved(container.template resolve<std::uint32_t>());
			expect(resolved, equal_to(registeredToken));
		});

		unit.test("resolve_calledWithClassRequiringRegisteredDependencyFromStaticFactory_expectClassIsConstructed", []()
		{
			constexpr std::uint32_t registeredToken = 9812378;
			const auto container(Container<>().registerFactory([]() static { return registeredToken; }));
			auto resolved(container.template resolve<ClassRequiringToken>());
			expect(resolved.token, equal_to(registeredToken));
		});

		unit.test("resolve_calledWithTypeThatIsRegisteredDependencyFromInstanceFactoryWithoutClosure_expectClassIsConstructed", []()
		{
			constexpr std::uint32_t registeredToken = 8973;
			const auto container(Container<>().registerFactory([]() { return registeredToken; }));
			auto resolved(container.template resolve<std::uint32_t>());
			expect(resolved, equal_to(registeredToken));
		});

		unit.test("resolve_calledWithClassRequiringRegisteredDependencyFromWithoutClosure_expectClassIsConstructed", []()
		{
			constexpr std::uint32_t registeredToken = 103620;
			const auto container(Container<>().registerFactory([]() { return registeredToken; }));
			auto resolved(container.template resolve<ClassRequiringToken>());
			expect(resolved.token, equal_to(registeredToken));
		});

		unit.test("resolve_calledWithTypeThatIsRegisteredDependencyFromInstanceFactory_expectClassIsConstructed", []()
		{
			auto registeredToken(anyValueOf<std::uint32_t>());
			const auto container(Container<>().registerFactory([registeredToken]() { return registeredToken; }));
			auto resolved(container.template resolve<std::uint32_t>());
			expect(resolved, equal_to(registeredToken));
		});

		unit.test("resolve_calledWithClassRequiringRegisteredDependencyFromInstanceFactory_expectClassIsConstructed", []()
		{
			auto registeredToken(anyValueOf<std::uint32_t>());
			const auto container(Container<>().registerFactory([registeredToken]() { return registeredToken; }));
			auto resolved(container.template resolve<ClassRequiringToken>());
			expect(resolved.token, equal_to(registeredToken));
		});

		unit.test("resolve_calledWhenFactoryHasBeenMovedBecauseOfNewRegistrations_expectSameClosureIsUsed", []()
		{
			auto registeredToken(anyValueOf<std::uint32_t>());
			const auto container(Container<>()
				.registerFactory([registeredToken]() { return registeredToken; })
				.registerFactory([]() { return "whatever"; }));

			auto resolved(container.template resolve<ClassRequiringToken>());
			expect(resolved.token, equal_to(registeredToken));
		});

		unit.test("resolve_calledWhenFactoryHasBeenCopiedBecauseOfNewRegistrations_expectAllContainersUseSameClosure", []()
		{
			auto registeredToken(anyValueOf<std::uint32_t>());
			const auto firstContainer(Container<>().registerFactory([registeredToken]() { return registeredToken; }));
			const auto secondContainer(firstContainer.registerFactory([]() { return "whatever"; }));
			auto firstResolved(firstContainer.template resolve<ClassRequiringToken>());
			auto secondResolved(secondContainer.template resolve<ClassRequiringToken>());
			expect(firstResolved.token, equal_to(secondResolved.token));
		});

		unit.test("resolve_calledOnDerivedContainerWithInitialRegistration_expectAllContainersUseSameClosure", []()
		{
			std::uint32_t counter(0);
			const auto firstContainer(Container<>().registerFactory([&counter]() { return counter++; }));
			const auto secondContainer(firstContainer.registerFactory([]() { return "whatever"; }));
			auto firstResolved(firstContainer.template resolve<std::uint32_t>());
			auto secondResolved(secondContainer.template resolve<std::uint32_t>());
			expect(std::array{firstResolved, secondResolved}, array(0, 1));
		});

		unit.test("resolve_calledWithRegisteredReference_expectSameRegisteredReference", []()
		{
			using Class = ClassRequiringInjection<std::uint32_t>;
			Class registered(anyValueOf<std::uint32_t>());
			const auto container(Container<>().registerFactory([&registered]() -> auto & { return registered; }));
			auto &resolved(container.template resolve<Class &>());
			expect(&resolved, equal_to(&registered));
		});

		unit.test("resolve_calledWithClassRequiringRegisteredReference_expectSameRegisteredReference", []()
		{
			auto token(anyValueOf<std::uint32_t>());
			using Class = ClassRequiringInjection<std::uint32_t &>;
			Class registered(token);
			const auto container(Container<>().registerFactory([&token]() -> auto & { return token; }));
			auto resolved(container.template resolve<Class>());
			expect(&std::get<0>(resolved.injected).value, equal_to(&token));
		});

		unit.test("resolve_calledWithClassRequiringRegisteredDependencies_expectSameRegisteredDependencies", []()
		{
			std::tuple tokens{anyValueOf<std::uint32_t>(), anyValueOf<std::uint16_t>()};
			using Class = ClassRequiringInjection<std::uint16_t, std::uint32_t>;
			const auto container(Container<>()
				.registerFactory([tokens]() -> auto { return std::get<0>(tokens); })
				.registerFactory([tokens]() -> auto { return std::get<1>(tokens); }));

			auto resolved(container.template resolve<Class>());
			std::tuple injected{std::get<0>(resolved.injected).value, std::get<1>(resolved.injected).value};
			expect(injected, tuple(std::get<1>(tokens), std::get<0>(tokens)));
		});

		unit.test("resolve_calledWithClassRequiringRegisteredReferences_expectSameRegisteredReferences", []()
		{
			std::tuple tokens{anyValueOf<std::int16_t>(), anyValueOf<std::int8_t>()};
			using Class = ClassRequiringInjection<std::int8_t &, std::int16_t &>;
			const auto container(Container<>()
				.registerFactory([&tokens]() -> auto & { return std::get<0>(tokens); })
				.registerFactory([&tokens]() -> auto & { return std::get<1>(tokens); }));

			auto resolved(container.template resolve<Class>());
			std::tuple injected{&std::get<0>(resolved.injected).value, &std::get<1>(resolved.injected).value};
			expect(injected, tuple(&std::get<1>(tokens), &std::get<0>(tokens)));
		});
	});
}
