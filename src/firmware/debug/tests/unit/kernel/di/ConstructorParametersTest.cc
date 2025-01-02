#include <concepts>
#include <tuple>
#include <type_traits>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/di/ConstructorParameters.hh"

using namespace mettle;
using namespace smeg::kernel::di;

namespace smeg::tests::unit::kernel::di
{
	template <typename... T>
	struct TypeOf
	{
		using AsUnqualifiedTypes = TypeOf<std::remove_cvref_t<T> ...>;
		using AsTuple = std::tuple<T...>;
		using AsTupleOfUnqualifiedTypes = AsUnqualifiedTypes::AsTuple;
		static constexpr auto numberOfTypes = sizeof...(T);
	};

	template <typename T>
	struct TypeOf<T>
	{
		using Type = T;

		using AsUnqualifiedTypes = TypeOf<std::remove_cvref_t<T>>;
		using AsTuple = std::tuple<T>;
		using AsTupleOfUnqualifiedTypes = AsUnqualifiedTypes::AsTuple;
	};

	template <auto>
	struct Dummy
	{
	};

	template <typename TParameter>
	struct PublicConstructorWithSingleParameter
	{
		PublicConstructorWithSingleParameter(TParameter)
		{
		}
	};

	template <typename TParameter>
	struct PublicConstructorsForDefaultAndWithSingleParameter
	{
		PublicConstructorsForDefaultAndWithSingleParameter(TParameter)
		{
		}

		PublicConstructorsForDefaultAndWithSingleParameter(void)
		{
		}
	};

	template <typename...>
	struct PublicConstructorWithMultipleParameters;

	template <typename... TParameters>
	struct PublicConstructorWithMultipleParameters<TypeOf<TParameters...>>
	{
		using Types = TypeOf<TParameters...>;

		PublicConstructorWithMultipleParameters(TParameters...)
		{
		}
	};

	template <typename...>
	struct PublicConstructorsForDefaultAndWithMultipleParameters;

	template <typename... TParameters>
	struct PublicConstructorsForDefaultAndWithMultipleParameters<TypeOf<TParameters...>>
	{
		using Types = TypeOf<TParameters...>;

		PublicConstructorsForDefaultAndWithMultipleParameters(TParameters...)
		{
		}

		PublicConstructorsForDefaultAndWithMultipleParameters(void)
		{
		}
	};

	template <typename...>
	struct PublicConstructorsForMultipleAndFewerParameters;

	template <typename... TParameters>
	struct PublicConstructorsForMultipleAndFewerParameters<TypeOf<TParameters...>>
	{
		template <typename...>
		struct GetFirstParameter;

		template <typename TFirstParameter, typename... TOtherParameters>
		struct GetFirstParameter<TFirstParameter, TOtherParameters...>
		{
			using Type = TFirstParameter;
		};

		using AllParameterTypes = TypeOf<TParameters...>;
		using FewerParameterTypes = GetFirstParameter<TParameters...>::Type;
		using TupleOfFewerUnqualifiedParameterTypes = TypeOf<FewerParameterTypes>::AsTupleOfUnqualifiedTypes;

		PublicConstructorsForMultipleAndFewerParameters(TParameters...)
		{
		}

		PublicConstructorsForMultipleAndFewerParameters(FewerParameterTypes)
		{
		}
	};

	suite<> constructorParametersTest("ConstructorParameters Tests", [](auto &unit)
	{
		unit.test("For_getWhenClassOnlyHasDefaultConstructor_expectEmptyTuple", []()
		{
			struct DefaultConstructor
			{
				int whatever = 42;
			};

			expect(std::same_as<ConstructorParameters::For<DefaultConstructor>, std::tuple<>>, equal_to(true));
		});
	});

	suite<
		TypeOf<int>,
		TypeOf<Dummy<123> &>,
		TypeOf<Dummy<456> *>
	> constructorParametersNonClassTest("ConstructorParameters (non-class) Tests", [](auto &unit)
	{
		unit.test("For_getWhenPassedNonClass_expectEmptyTuple", [](auto fixture)
		{
			using NonClass = decltype(fixture)::Type;
			expect(std::same_as<ConstructorParameters::For<NonClass>, std::tuple<>>, equal_to(true));
		});
	});

	suite<
		TypeOf<int>,
		TypeOf<float>,
		TypeOf<Dummy<123>>,
		TypeOf<Dummy<123> &>,
		TypeOf<int &>,
		TypeOf<const long>,
		TypeOf<const volatile char *>,
		TypeOf<const volatile short &>,
		TypeOf<const Dummy<456> *>,
		TypeOf<const int *const>,
		TypeOf<void(*)(int, double, const char *)>,
		TypeOf<char(*)(volatile long *const)>,
		TypeOf<Dummy<789> &&>
	> constructorParametersSingleParameterTest("ConstructorParameters (Single Parameter) Tests", [](auto &unit)
	{
		unit.test("For_getWhenClassHasPublicConstructorWithSingleParameter_expectTupleWithSingleElement", [](auto fixture)
		{
			using FixtureParameterType = decltype(fixture)::Type;
			using Class = PublicConstructorWithSingleParameter<FixtureParameterType>;
			expect(std::tuple_size_v<ConstructorParameters::For<Class>>, equal_to(1));
		});

		unit.test("For_getWhenClassHasPublicConstructorWithSingleParameter_expectTupleWithSingleElementOfUnqualifiedType", [](auto fixture)
		{
			using FixtureParameterType = decltype(fixture)::Type;
			using ExpectedParameterType = std::remove_cvref_t<FixtureParameterType>;
			using Class = PublicConstructorWithSingleParameter<FixtureParameterType>;
			using ActualParameterType = std::tuple_element_t<0, ConstructorParameters::For<Class>>;
			expect(std::same_as<ActualParameterType, ExpectedParameterType>, equal_to(true));
		});

		unit.test("For_getWhenClassHasPublicConstructorsForDefaultAndWithSingleParameter_expectEmptyTuple", [](auto fixture)
		{
			using FixtureParameterType = decltype(fixture)::Type;
			using Class = PublicConstructorsForDefaultAndWithSingleParameter<FixtureParameterType>;
			expect(std::same_as<ConstructorParameters::For<Class>, std::tuple<>>, equal_to(true));
		});
	});

	suite<
		TypeOf<int, Dummy<1> &, float>,
		TypeOf<const long, Dummy<2>>,
		TypeOf<Dummy<3>, volatile Dummy<4> &, Dummy<5> *, Dummy<6>, Dummy<7> *const>,
		TypeOf<void(*)(int, double, const char *), char(*)(volatile long *const)>,
		TypeOf<Dummy<8> &&, Dummy<9>, Dummy<10>>
	> constructorParametersMultipleParameterTest("ConstructorParameters (Multiple Parameter) Tests", [](auto &unit)
	{
		unit.test("For_getWhenClassHasPublicConstructorWithMultipleParameters_expectTupleWithSameNumberOfElements", [](auto fixture)
		{
			using FixtureParameterTypes = decltype(fixture);
			using Class = PublicConstructorWithMultipleParameters<FixtureParameterTypes>;
			expect(std::tuple_size_v<ConstructorParameters::For<Class>>, equal_to(FixtureParameterTypes::numberOfTypes));
		});

		unit.test("For_getWhenClassHasPublicConstructorWithMultipleParameters_expectTupleOfUnqualifiedTypes", [](auto fixture)
		{
			using FixtureParameterTypes = decltype(fixture);
			using ExpectedParameterTypes = FixtureParameterTypes::AsTupleOfUnqualifiedTypes;
			using Class = PublicConstructorWithMultipleParameters<FixtureParameterTypes>;
			using ActualParameterTypes = ConstructorParameters::For<Class>;
			expect(std::same_as<ActualParameterTypes, ExpectedParameterTypes>, equal_to(true));
		});

		unit.test("For_getWhenClassHasPublicConstructorsForDefaultAndWithMultipleParameters_expectEmptyTuple", [](auto fixture)
		{
			using FixtureParameterTypes = decltype(fixture);
			using Class = PublicConstructorsForDefaultAndWithMultipleParameters<FixtureParameterTypes>;
			expect(std::same_as<ConstructorParameters::For<Class>, std::tuple<>>, equal_to(true));
		});

		unit.test("For_getWhenClassHasPublicConstructorsForMultipleAndFewerParameters_expectTupleOfUnqualifiedTypesRequiredByLessGreedyConstructor", [](auto fixture)
		{
			using FixtureParameterTypes = decltype(fixture);
			using Class = PublicConstructorsForMultipleAndFewerParameters<FixtureParameterTypes>;
			using ExpectedParameterTypes = Class::TupleOfFewerUnqualifiedParameterTypes;
			using ActualParameterTypes = ConstructorParameters::For<Class>;
			expect(std::same_as<ActualParameterTypes, ExpectedParameterTypes>, equal_to(true));
		});
	});
}
