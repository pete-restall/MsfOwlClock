#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/IHaveRequiredApis.hh"

using namespace mettle;

using namespace smeg::kernel;

namespace smeg::tests::unit::kernel
{
	template <typename T>
	struct StubWithRequiredApisTypedefOnly
	{
		using RequiredApis = T;
	};

	template <typename...>
	struct DummyApis
	{
	};

	template <typename...>
	struct DummyOtherApis
	{
	};

	template <auto>
	struct DummyApi
	{
	};

	suite<> iHaveAnyRequiredApisTypedefTest("IHaveAnyRequiredApisTypedef Test Suite", [](auto &unit)
	{
		unit.test("IHaveAnyRequiredApisTypedef_conceptPassedClassWithClassRequiredApisMember_expectTrueIsReturned", []()
		{
			struct DummyClass { };
			expect(IHaveAnyRequiredApisTypedef<StubWithRequiredApisTypedefOnly<DummyClass>>, equal_to(true));
		});

		unit.test("IHaveAnyRequiredApisTypedef_conceptPassedClassWithNonClassRequiredApisMember_expectFalseIsReturned", []()
		{
			expect(IHaveAnyRequiredApisTypedef<StubWithRequiredApisTypedefOnly<int>>, equal_to(false));
			expect(IHaveAnyRequiredApisTypedef<StubWithRequiredApisTypedefOnly<double>>, equal_to(false));
			expect(IHaveAnyRequiredApisTypedef<StubWithRequiredApisTypedefOnly<bool>>, equal_to(false));
		});
	});

	suite<> iHaveAnyRequiredApisTest("IHaveAnyRequiredApis Test Suite", [](auto &unit)
	{
		unit.test("IHaveAnyRequiredApis_conceptPassedValidClass_expectTrueIsReturned", []()
		{
			struct ValidClass
			{
				using RequiredApis = DummyApis<DummyApi<12>, DummyApi<34>>;

				ValidClass(RequiredApis)
				{
				}
			};

			expect(IHaveAnyRequiredApis<ValidClass>, equal_to(true));
		});

		unit.test("IHaveAnyRequiredApis_conceptPassedClassWithConstructorTakingApisButNoRequiredApisTypedef_expectFalseIsReturned", []()
		{
			struct WithValidConstructorButNoRequiredApisTypedef
			{
				WithValidConstructorButNoRequiredApisTypedef(DummyApis<DummyApi<56>>)
				{
				}
			};

			expect(IHaveAnyRequiredApis<WithValidConstructorButNoRequiredApisTypedef>, equal_to(false));
		});

		unit.test("IHaveAnyRequiredApis_conceptPassedClassWithValidRequiredApisTypedefButNoCorrespondingConstructor_expectFalseIsReturned", []()
		{
			struct WithValidRequiredApisTypedefButNoCorrespondingConstructor
			{
				using RequiredApis = DummyApis<DummyApi<25>>;
			};

			expect(IHaveAnyRequiredApis<WithValidRequiredApisTypedefButNoCorrespondingConstructor>, equal_to(false));
		});

		unit.test("IHaveAnyRequiredApis_conceptPassedClassWithConstructorTakingConstApis_expectTrueIsReturned", []()
		{
			struct WithValidConstructor
			{
				using RequiredApis = const DummyApis<DummyApi<-8>>;

				WithValidConstructor(RequiredApis)
				{
				}
			};

			expect(IHaveAnyRequiredApis<WithValidConstructor>, equal_to(true));
		});

		unit.test("IHaveAnyRequiredApis_conceptPassedClassWithConstructorTakingReferenceToApis_expectFalseIsReturned", []()
		{
			struct WithInvalidConstructor
			{
				using RequiredApis = DummyApis<DummyApi<6>> &;

				WithInvalidConstructor(RequiredApis) noexcept
				{
				}
			};

			expect(IHaveAnyRequiredApis<WithInvalidConstructor>, equal_to(false));
		});

		unit.test("IHaveAnyRequiredApis_conceptPassedClassWithConstructorTakingPointerToApis_expectFalseIsReturned", []()
		{
			struct WithInvalidConstructor
			{
				using RequiredApis = DummyApis<DummyApi<-1>> *;

				WithInvalidConstructor(RequiredApis)
				{
				}
			};

			expect(IHaveAnyRequiredApis<WithInvalidConstructor>, equal_to(false));
		});

		unit.test("IHaveAnyRequiredApis_conceptPassedClassWithConstructorTakingApisAndOtherParameters_expectFalseIsReturnedWhenNoArgumentsGiven", []()
		{
			struct ConstructorWithExtraArgs
			{
				using RequiredApis = DummyApis<DummyApi<14>>;

				ConstructorWithExtraArgs(RequiredApis, int, bool, DummyApi<123>)
				{
				}
			};

			expect(IHaveAnyRequiredApis<ConstructorWithExtraArgs>, equal_to(false));
		});

		unit.test("IHaveAnyRequiredApis_conceptPassedClassWithConstructorTakingApisAndOtherParameters_expectTrueIsReturnedWhenCompatibleArgumentsGiven", []()
		{
			struct ConstructorWithExtraArgs
			{
				using RequiredApis = DummyApis<DummyApi<14>>;

				ConstructorWithExtraArgs(RequiredApis, int, bool, DummyApi<123>)
				{
				}
			};

			expect(IHaveAnyRequiredApis<ConstructorWithExtraArgs, int, bool, DummyApi<123>>, equal_to(true));
		});
	});

	suite<> iHaveRequiredApisTest("IHaveRequiredApis Test Suite", [](auto &unit)
	{
		unit.test("IHaveRequiredApis_conceptPassedValidClass_expectTrueIsReturned", []()
		{
			struct ValidClass
			{
				using RequiredApis = DummyApis<DummyApi<12>, DummyApi<34>>;

				ValidClass(RequiredApis)
				{
				}
			};

			expect(IHaveRequiredApis<ValidClass, DummyApis>, equal_to(true));
		});

		unit.test("IHaveRequiredApis_conceptPassedValidClassButDifferentApisInterface_expectFalseIsReturned", []()
		{
			struct ValidClass
			{
				using RequiredApis = DummyApis<DummyApi<12>, DummyApi<34>>;

				ValidClass(RequiredApis)
				{
				}
			};

			expect(IHaveRequiredApis<ValidClass, DummyOtherApis>, equal_to(false));
		});

		unit.test("IHaveRequiredApis_conceptPassedClassWithConstructorTakingApisButNoRequiredApisTypedef_expectFalseIsReturned", []()
		{
			struct WithValidConstructorButNoRequiredApisTypedef
			{
				WithValidConstructorButNoRequiredApisTypedef(DummyApis<DummyApi<56>>)
				{
				}
			};

			expect(IHaveRequiredApis<WithValidConstructorButNoRequiredApisTypedef, DummyApis>, equal_to(false));
		});

		unit.test("IHaveRequiredApis_conceptPassedClassWithValidRequiredApisTypedefButNoCorrespondingConstructor_expectFalseIsReturned", []()
		{
			struct WithValidRequiredApisTypedefButNoCorrespondingConstructor
			{
				using RequiredApis = DummyApis<DummyApi<25>>;
			};

			expect(IHaveRequiredApis<WithValidRequiredApisTypedefButNoCorrespondingConstructor, DummyApis>, equal_to(false));
		});

		unit.test("IHaveRequiredApis_conceptPassedClassWithConstructorTakingConstApis_expectTrueIsReturned", []()
		{
			struct WithValidConstructor
			{
				using RequiredApis = const DummyApis<DummyApi<-8>>;

				WithValidConstructor(RequiredApis)
				{
				}
			};

			expect(IHaveRequiredApis<WithValidConstructor, DummyApis>, equal_to(true));
		});

		unit.test("IHaveRequiredApis_conceptPassedClassWithConstructorTakingReferenceToApis_expectFalseIsReturned", []()
		{
			struct WithInvalidConstructor
			{
				using RequiredApis = DummyApis<DummyApi<6>> &;

				WithInvalidConstructor(RequiredApis) noexcept
				{
				}
			};

			expect(IHaveRequiredApis<WithInvalidConstructor, DummyApis>, equal_to(false));
		});

		unit.test("IHaveRequiredApis_conceptPassedClassWithConstructorTakingPointerToApis_expectFalseIsReturned", []()
		{
			struct WithInvalidConstructor
			{
				using RequiredApis = DummyApis<DummyApi<-1>> *;

				WithInvalidConstructor(RequiredApis)
				{
				}
			};

			expect(IHaveRequiredApis<WithInvalidConstructor, DummyApis>, equal_to(false));
		});

		unit.test("IHaveRequiredApis_conceptPassedClassWithConstructorTakingApisAndOtherParameters_expectFalseIsReturnedWhenNoArgumentsGiven", []()
		{
			struct ConstructorWithExtraArgs
			{
				using RequiredApis = DummyApis<DummyApi<14>>;

				ConstructorWithExtraArgs(RequiredApis, int, bool, DummyApi<123>)
				{
				}
			};

			expect(IHaveRequiredApis<ConstructorWithExtraArgs, DummyApis>, equal_to(false));
		});

		unit.test("IHaveRequiredApis_conceptPassedClassWithConstructorTakingApisAndOtherParameters_expectTrueIsReturnedWhenCompatibleArgumentsGiven", []()
		{
			struct ConstructorWithExtraArgs
			{
				using RequiredApis = DummyApis<DummyApi<14>>;

				ConstructorWithExtraArgs(RequiredApis, int, bool, DummyApi<123>)
				{
				}
			};

			expect(IHaveRequiredApis<ConstructorWithExtraArgs, DummyApis, int, bool, DummyApi<123>>, equal_to(true));
		});
	});
}
