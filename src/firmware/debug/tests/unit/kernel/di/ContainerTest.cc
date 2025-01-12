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
	template <typename T>
	struct TypeOf
	{
		using Type = T;
	};

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

	suite<> containerResolveWithoutKeyTest("Container (Resolve Without Key) Tests", [](auto &unit)
	{
		// all factories should be able to take up to the following:
		// factory<TContainer, T, TKey, ResolutionContext<TContext>>(container, context)

		// resolve<T>()
		// resolve<T, TKey>()

		// resolve<T>(TContext &)
		// resolve<T, TKey>(TContext &)

		// Don't forget to test for const (instances, references, pointers and pointers-to) and volatile (references, and pointers-to) and the valid combinations thereof

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

		unit.test("resolve_calledWithClassRequiringRegisteredMixOfConstVolatileReferences_expectSameExactRegisteredReferences", []()
		{
			using Class = ClassRequiringInjection<
				volatile ClassWithDefaultConstructor &,
				const ClassWithDefaultConstructor &,
				ClassWithDefaultConstructor &,
				const volatile ClassWithDefaultConstructor &>;

			std::array<ClassWithDefaultConstructor, 4> registered;
			const auto container(Container<>()
				.registerFactory([&registered]() -> const auto & { return registered[0]; })
				.registerFactory([&registered]() -> volatile auto & { return registered[1]; })
				.registerFactory([&registered]() -> const volatile auto & { return registered[2]; })
				.registerFactory([&registered]() -> auto & { return registered[3]; }));

			auto resolved(container.template resolve<Class>());
			std::tuple injected{
				&std::get<0>(resolved.injected).value,
				&std::get<1>(resolved.injected).value,
				&std::get<2>(resolved.injected).value,
				&std::get<3>(resolved.injected).value};
			expect(injected, tuple(&registered[1], &registered[0], &registered[3], &registered[2]));
		});

		unit.test("resolve_calledWithClassRequiringConstReference_expectRegisteredNonConstReference", []()
		{
			using Class = ClassRequiringInjection<const ClassWithDefaultConstructor &>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> auto & { return registered; }));
			auto resolved(container.template resolve<Class>());
			expect(&std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		unit.test("resolve_calledWithClassRequiringVolatileReference_expectRegisteredNonVolatileReference", []()
		{
			using Class = ClassRequiringInjection<volatile ClassWithDefaultConstructor &>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> auto & { return registered; }));
			auto resolved(container.template resolve<Class>());
			expect(&std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		unit.test("resolve_calledWithClassRequiringConstVolatileReference_expectRegisteredNonConstVolatileReference", []()
		{
			using Class = ClassRequiringInjection<const volatile ClassWithDefaultConstructor &>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> auto & { return registered; }));
			auto resolved(container.template resolve<Class>());
			expect(&std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		unit.test("resolve_calledWithClassRequiringConstVolatileReference_expectRegisteredConstNonVolatileReference", []()
		{
			using Class = ClassRequiringInjection<const volatile ClassWithDefaultConstructor &>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> const auto & { return registered; }));
			auto resolved(container.template resolve<Class>());
			expect(&std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		unit.test("resolve_calledWithClassRequiringConstVolatileReference_expectRegisteredNonConstVolatileReference", []()
		{
			using Class = ClassRequiringInjection<const volatile ClassWithDefaultConstructor &>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> volatile auto & { return registered; }));
			auto resolved(container.template resolve<Class>());
			expect(&std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		mettle::subsuite<
			TypeOf<ClassWithDefaultConstructor *>,
			TypeOf<const ClassWithDefaultConstructor *>,
			TypeOf<volatile ClassWithDefaultConstructor *>,
			TypeOf<const volatile ClassWithDefaultConstructor *>
		>(unit, "Pointers", [](auto &unit) {
			unit.test("resolve_calledWithRegisteredPointer_expectSameRegisteredPointer", [](auto fixture)
			{
				using PointerToClass = decltype(fixture)::Type;
				using Class = std::remove_cvref_t<std::remove_pointer_t<PointerToClass>>;
				Class registered;
				const auto container(Container<>().registerFactory([&registered]() -> PointerToClass { return &registered; }));
				auto resolved(container.template resolve<PointerToClass>());
				expect(resolved, equal_to(&registered));
			});

			unit.test("resolve_calledWithConstRegisteredPointer_expectSameRegisteredNonConstPointer", [](auto fixture)
			{
				using PointerToClass = decltype(fixture)::Type;
				using Class = std::remove_cvref_t<std::remove_pointer_t<PointerToClass>>;
				Class registered;
				const auto container(Container<>().registerFactory([&registered]() -> PointerToClass { return &registered; }));
				const auto resolved(container.template resolve<const PointerToClass>());
				expect(resolved, equal_to(&registered));
			});

			unit.test("resolve_calledWithRegisteredPointer_expectSameRegisteredConstPointer", [](auto fixture)
			{
				using PointerToClass = decltype(fixture)::Type;
				using Class = std::remove_cvref_t<std::remove_pointer_t<PointerToClass>>;
				Class registered;
				const auto container(Container<>().registerFactory([&registered]() -> const PointerToClass { return &registered; }));
				auto resolved(container.template resolve<PointerToClass>());
				expect(resolved, equal_to(&registered));
			});

			unit.test("resolve_calledWithClassRequiringRegisteredPointer_expectSameRegisteredPointer", [](auto fixture)
			{
				using PointerToClass = decltype(fixture)::Type;
				using Class = std::remove_cvref_t<std::remove_pointer_t<PointerToClass>>;
				Class registered;
				const auto container(Container<>().registerFactory([&registered]() -> PointerToClass { return &registered; }));
				auto resolved(container.template resolve<ClassRequiringInjection<PointerToClass>>());
				expect(std::get<0>(resolved.injected).value, equal_to(&registered));
			});

			unit.test("resolve_calledWithClassRequiringConstRegisteredPointer_expectSameRegisteredPointer", [](auto fixture)
			{
				using PointerToClass = decltype(fixture)::Type;
				using Class = std::remove_cvref_t<std::remove_pointer_t<PointerToClass>>;
				Class registered;
				const auto container(Container<>().registerFactory([&registered]() -> PointerToClass { return &registered; }));
				const auto resolved(container.template resolve<ClassRequiringInjection<const PointerToClass>>());
				expect(std::get<0>(resolved.injected).value, equal_to(&registered));
			});

			unit.test("resolve_calledWithClassRequiringRegisteredPointer_expectSameRegisteredConstPointer", [](auto fixture)
			{
				using PointerToClass = decltype(fixture)::Type;
				using Class = std::remove_cvref_t<std::remove_pointer_t<PointerToClass>>;
				Class registered;
				const auto container(Container<>().registerFactory([&registered]() -> const PointerToClass { return &registered; }));
				auto resolved(container.template resolve<ClassRequiringInjection<PointerToClass>>());
				expect(std::get<0>(resolved.injected).value, equal_to(&registered));
			});
		});

		unit.test("resolve_calledWithClassRequiringRegisteredMixOfConstVolatilePointers_expectSameExactRegisteredPointers", []()
		{
			using Class = ClassRequiringInjection<
				volatile ClassWithDefaultConstructor *,
				const ClassWithDefaultConstructor *,
				ClassWithDefaultConstructor *,
				const volatile ClassWithDefaultConstructor *>;

			std::array<ClassWithDefaultConstructor, 4> registered;
			const auto container(Container<>()
				.registerFactory([&registered]() -> const ClassWithDefaultConstructor * { return &registered[0]; })
				.registerFactory([&registered]() -> volatile ClassWithDefaultConstructor * { return &registered[1]; })
				.registerFactory([&registered]() -> const volatile ClassWithDefaultConstructor * { return &registered[2]; })
				.registerFactory([&registered]() -> auto { return &registered[3]; }));

			auto resolved(container.template resolve<Class>());
			std::tuple injected{
				std::get<0>(resolved.injected).value,
				std::get<1>(resolved.injected).value,
				std::get<2>(resolved.injected).value,
				std::get<3>(resolved.injected).value};
			expect(injected, tuple(&registered[1], &registered[0], &registered[3], &registered[2]));
		});

		unit.test("resolve_calledWithClassRequiringPointerToConst_expectRegisteredPointerToNonConst", []()
		{
			using Class = ClassRequiringInjection<const ClassWithDefaultConstructor *>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> auto { return &registered; }));
			auto resolved(container.template resolve<Class>());
			expect(std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		unit.test("resolve_calledWithClassRequiringPointerToVolatile_expectRegisteredPonterToNonVolatile", []()
		{
			using Class = ClassRequiringInjection<volatile ClassWithDefaultConstructor *>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> auto { return &registered; }));
			auto resolved(container.template resolve<Class>());
			expect(std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		unit.test("resolve_calledWithClassRequiringPointerToConstVolatile_expectRegisteredPointerToNonConstVolatile", []()
		{
			using Class = ClassRequiringInjection<const volatile ClassWithDefaultConstructor *>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> auto { return &registered; }));
			auto resolved(container.template resolve<Class>());
			expect(std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		unit.test("resolve_calledWithClassRequiringPointerToConstVolatile_expectRegisteredPointerToConstNonVolatile", []()
		{
			using Class = ClassRequiringInjection<const volatile ClassWithDefaultConstructor *>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> const auto { return &registered; }));
			auto resolved(container.template resolve<Class>());
			expect(std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		unit.test("resolve_calledWithClassRequiringPointerToConstVolatile_expectRegisteredPointerToNonConstVolatile", []()
		{
			using Class = ClassRequiringInjection<const volatile ClassWithDefaultConstructor *>;
			ClassWithDefaultConstructor registered;
			const auto container(Container<>().registerFactory([&registered]() -> volatile ClassWithDefaultConstructor * { return &registered; }));
			auto resolved(container.template resolve<Class>());
			expect(std::get<0>(resolved.injected).value, equal_to(&registered));
		});

		// TODO: what about requesting 'const T' when only 'T' is available ?  It should resolve exactly...
		// TODO: what about requesting 'const T' and 'T' when both are available ?  They should resolve exactly...
		// TODO: what about requesting 'const T &' when only 'T' is available ?  It should resolve exactly...
		// TODO: what about requesting 'const T &' and 'T &' when both are available ?  They should resolve exactly...
		// TODO: what about requesting 'volatile T &' when only 'T' is available ?  It should resolve exactly...
		// TODO: what about requesting 'volatile T &' and 'T &' when both are available ?  They should resolve exactly...
		// TODO: what about requesting 'const volatile T &' when only 'T' is available ?  It should resolve exactly...
		// TODO: what about requesting 'const volatile T &' and 'T &' when both are available ?  They should resolve exactly...
	});

	suite<> containerResolveWithKeyTest("Container (Resolve With Key) Tests", [](auto &unit)
	{
		// TODO: Think about how key-based resolution will work:
		//     Do all dependencies need to be keyed ?  Only if there is no registered default factory for the given key, ie. we should be able to provide a default factory for a given key that is invoked whenever there is an unregistered instance; before that invocation we should also call into parent containers, if any.
		//     Does the initial dependency need to be keyed ?  Again, only if there is no default factory for the given key, and no parent container supplying it.
	});
}
