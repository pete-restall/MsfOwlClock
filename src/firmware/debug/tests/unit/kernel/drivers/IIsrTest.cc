#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/IIsr.hh"
#include "kernel/drivers/IsrApis.hh"

using namespace mettle;

using namespace smeg::kernel::drivers;

namespace smeg::tests::unit::kernel::drivers
{
	template <typename... TApis>
	struct DummyApis
	{
	};

	template <auto X>
	struct DummyApi
	{
	};

	suite<> iIsrTest("IIsr Test Suite", [](auto &unit)
	{
		unit.test("IIsr_conceptPassedValidIsr_expectTrueIsReturned", []()
		{
			struct StaticValidIsr
			{
				static void onInterrupt(void) noexcept
				{
				}
			};

			struct NonStaticValidIsr
			{
				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<StaticValidIsr>, equal_to(true));
			expect(IIsr<NonStaticValidIsr>, equal_to(true));
		});

		unit.test("IIsr_conceptPassedIsrWithExplicitDefaultConstructorButMissingNoExcept_expectFalseIsReturned", []()
		{
			struct StaticIsrWithConstructorMissingNoExcept
			{
				StaticIsrWithConstructorMissingNoExcept()
				{
					throw "this would leak into the static initialisers (.init)";
				}

				static void onInterrupt(void) noexcept
				{
				}
			};

			struct NonStaticIsrWithConstructorMissingNoExcept
			{
				NonStaticIsrWithConstructorMissingNoExcept()
				{
					throw "this would leak into the static initialisers (.init)";
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<StaticIsrWithConstructorMissingNoExcept>, equal_to(false));
			expect(IIsr<NonStaticIsrWithConstructorMissingNoExcept>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrMissingNoExcept_expectFalseIsReturned", []()
		{
			struct StaticIsrMissingNoExcept
			{
				static void onInterrupt(void)
				{
				}
			};

			struct NonStaticIsrMissingNoExcept
			{
				void onInterrupt(void)
				{
				}
			};

			expect(IIsr<StaticIsrMissingNoExcept>, equal_to(false));
			expect(IIsr<NonStaticIsrMissingNoExcept>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrWithoutHandler_expectFalseIsReturned", []()
		{
			struct IsrWithoutHandler
			{
				void someOtherMethod(void) noexcept
				{
				}
			};

			expect(IIsr<IsrWithoutHandler>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrTakingValue_expectFalseIsReturned", []()
		{
			struct StaticIsrTakingValue
			{
				static void onInterrupt(int) noexcept
				{
				}
			};

			struct NonStaticIsrTakingValue
			{
				void onInterrupt(int) noexcept
				{
				}
			};

			expect(IIsr<StaticIsrTakingValue>, equal_to(false));
			expect(IIsr<NonStaticIsrTakingValue>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrReturningValue_expectFalseIsReturned", []()
		{
			struct StaticIsrReturningValue
			{
				static int onInterrupt(void) noexcept
				{
					return 1;
				}
			};

			struct NonStaticIsrReturningValue
			{
				int onInterrupt(void) noexcept
				{
					return 1;
				}
			};

			expect(IIsr<StaticIsrReturningValue>, equal_to(false));
			expect(IIsr<NonStaticIsrReturningValue>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrWithConstructorTakingIsrApis_expectTrueIsReturned", []()
		{
			struct IsrWithValidConstructor
			{
				using RequiredApis = IsrApis<DummyApi<56>>;

				IsrWithValidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<IsrWithValidConstructor>, equal_to(true));
		});

		unit.test("IIsr_conceptPassedIsrWithConstructorTakingIsrApisButNoRequiredApisTypedef_expectFalseIsReturned", []()
		{
			struct IsrWithValidConstructorButNoRequiredApisTypedef
			{
				IsrWithValidConstructorButNoRequiredApisTypedef(IsrApis<DummyApi<89>>) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<IsrWithValidConstructorButNoRequiredApisTypedef>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrWithValidRequiredApisTypedefButNoCorrespondingConstructor_expectFalseIsReturned", []()
		{
			struct IsrWithValidRequiredApisTypedefButNoCorrespondingConstructor
			{
				using RequiredApis = IsrApis<DummyApi<2>>;

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<IsrWithValidRequiredApisTypedefButNoCorrespondingConstructor>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrWithConstructorTakingConstIsrApis_expectTrueIsReturned", []()
		{
			struct IsrWithValidConstructor
			{
				using RequiredApis = const IsrApis<DummyApi<105>>;

				IsrWithValidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<IsrWithValidConstructor>, equal_to(true));
		});

		unit.test("IIsr_conceptPassedIsrWithConstructorTakingReferenceToIsrApis_expectFalseIsReturned", []()
		{
			struct IsrWithInvalidConstructor
			{
				using RequiredApis = IsrApis<DummyApi<6>> &;

				IsrWithInvalidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<IsrWithInvalidConstructor>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrWithConstructorTakingPointerToIsrApis_expectFalseIsReturned", []()
		{
			struct IsrWithInvalidConstructor
			{
				using RequiredApis = IsrApis<DummyApi<44>> *;

				IsrWithInvalidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<IsrWithInvalidConstructor>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrWithConstructorNotTakingIsrApis_expectFalseIsReturned", []()
		{
			struct IsrWithInvalidConstructor
			{
				using RequiredApis = DummyApis<DummyApi<198>>;

				IsrWithInvalidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<IsrWithInvalidConstructor>, equal_to(false));
		});
	});

	suite<> iNakedIsrTest("INakedIsr Test Suite", [](auto &unit)
	{
		unit.test("INakedIsr_conceptPassedValidIsrWithoutExplicitDefaultConstructor_expectTrueIsReturned", []()
		{
			struct ValidIsr
			{
				static void onInterrupt(void) noexcept
				{
				}
			};

			expect(INakedIsr<ValidIsr>, equal_to(true));
		});

		unit.test("INakedIsr_conceptPassedIsrWithExplicitDefaultConstructor_expectTrueIsReturned", []()
		{
			struct ValidIsr
			{
				ValidIsr() noexcept
				{
				}

				static void onInterrupt(void) noexcept
				{
				}
			};

			expect(INakedIsr<ValidIsr>, equal_to(true));
		});

		unit.test("INakedIsr_conceptPassedIsrWithExplicitDefaultConstructorButMissingNoExcept_expectFalseIsReturned", []()
		{
			struct IsrWithConstructorMissingNoExcept
			{
				IsrWithConstructorMissingNoExcept()
				{
					throw "this would leak into the static initialisers (.init)";
				}

				static void onInterrupt(void) noexcept
				{
				}
			};

			expect(INakedIsr<IsrWithConstructorMissingNoExcept>, equal_to(false));
		});

		unit.test("INakedIsr_conceptPassedIsrMissingNoExcept_expectFalseIsReturned", []()
		{
			struct IsrMissingNoExcept
			{
				static void onInterrupt(void)
				{
				}
			};

			expect(INakedIsr<IsrMissingNoExcept>, equal_to(false));
		});

		unit.test("INakedIsr_conceptPassedIsrWithNonStaticHandler_expectFalseIsReturned", []()
		{
			struct IsrWithNonStaticHandler
			{
				void onInterrupt(void) noexcept
				{
				}
			};

			expect(INakedIsr<IsrWithNonStaticHandler>, equal_to(false));
		});

		unit.test("INakedIsr_conceptPassedIsrTakingValue_expectFalseIsReturned", []()
		{
			struct IsrTakingValue
			{
				static void onInterrupt(int) noexcept
				{
				}
			};

			expect(INakedIsr<IsrTakingValue>, equal_to(false));
		});

		unit.test("INakedIsr_conceptPassedIsrReturningValue_expectFalseIsReturned", []()
		{
			struct IsrReturningValue
			{
				static int onInterrupt(void) noexcept
				{
					return 1;
				}
			};

			expect(INakedIsr<IsrReturningValue>, equal_to(false));
		});

		unit.test("INakedIsr_conceptPassedIsrWithValidConstructorForPerCoreIsr_expectFalseIsReturned", []()
		{
			struct IsrWithValidConstructorForPerCoreIsr
			{
				using RequiredApis = IsrApis<DummyApi<3>>;

				IsrWithValidConstructorForPerCoreIsr(RequiredApis) noexcept
				{
				}

				static void onInterrupt(void) noexcept
				{
				}
			};

			expect(INakedIsr<IsrWithValidConstructorForPerCoreIsr>, equal_to(false));
		});
	});

	suite<> iPerCoreIsrTest("IPerCoreIsr Test Suite", [](auto &unit)
	{
		unit.test("IPerCoreIsr_conceptPassedValidIsrWithoutRequiredApis_expectTrueIsReturned", []()
		{
			struct ValidIsr
			{
				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<ValidIsr>, equal_to(true));
		});

		unit.test("IPerCoreIsr_conceptPassedValidIsrWithExplicitDefaultConstructorAndWithoutRequiredApis_expectTrueIsReturned", []()
		{
			struct ValidIsr
			{
				ValidIsr() noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<ValidIsr>, equal_to(true));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithoutRequiredApisButConstructorMissingNoExcept_expectFalseIsReturned", []()
		{
			struct IsrWithConstructorMissingNoExcept
			{
				IsrWithConstructorMissingNoExcept()
				{
					throw "this would leak into the static initialisers (.init)";
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithConstructorMissingNoExcept>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrMissingNoExcept_expectFalseIsReturned", []()
		{
			struct IsrMissingNoExcept
			{
				void onInterrupt(void)
				{
				}
			};

			expect(IPerCoreIsr<IsrMissingNoExcept>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithStaticHandler_expectFalseIsReturned", []()
		{
			struct IsrWithStaticHandler
			{
				static void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithStaticHandler>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithoutHandler_expectFalseIsReturned", []()
		{
			struct IsrWithoutHandler
			{
				void someOtherMethod(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithoutHandler>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrTakingValue_expectFalseIsReturned", []()
		{
			struct IsrTakingValue
			{
				void onInterrupt(int) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrTakingValue>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrReturningValue_expectFalseIsReturned", []()
		{
			struct IsrReturningValue
			{
				int onInterrupt(void) noexcept
				{
					return 1;
				}
			};

			expect(IPerCoreIsr<IsrReturningValue>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithConstructorTakingIsrApis_expectTrueIsReturned", []()
		{
			struct IsrWithValidConstructor
			{
				using RequiredApis = IsrApis<DummyApi<73>>;

				IsrWithValidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithValidConstructor>, equal_to(true));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithConstructorTakingIsrApisButMissingNoExcept_expectFalseIsReturned", []()
		{
			struct IsrWithValidConstructor
			{
				using RequiredApis = IsrApis<DummyApi<73>>;

				IsrWithValidConstructor(RequiredApis)
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithValidConstructor>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithConstructorTakingIsrApisButNoRequiredApisTypedef_expectFalseIsReturned", []()
		{
			struct IsrWithValidConstructorButNoRequiredApisTypedef
			{
				IsrWithValidConstructorButNoRequiredApisTypedef(IsrApis<DummyApi<73>>) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithValidConstructorButNoRequiredApisTypedef>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithValidRequiredApisTypedefButNoCorrespondingConstructor_expectFalseIsReturned", []()
		{
			struct IsrWithValidRequiredApisTypedefButNoCorrespondingConstructor
			{
				using RequiredApis = IsrApis<DummyApi<73>>;

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithValidRequiredApisTypedefButNoCorrespondingConstructor>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithConstructorTakingConstIsrApis_expectTrueIsReturned", []()
		{
			struct IsrWithValidConstructor
			{
				using RequiredApis = const IsrApis<DummyApi<15>>;

				IsrWithValidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithValidConstructor>, equal_to(true));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithConstructorTakingReferenceToIsrApis_expectFalseIsReturned", []()
		{
			struct IsrWithInvalidConstructor
			{
				using RequiredApis = IsrApis<DummyApi<73>> &;

				IsrWithInvalidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithInvalidConstructor>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithConstructorTakingPointerToIsrApis_expectFalseIsReturned", []()
		{
			struct IsrWithInvalidConstructor
			{
				using RequiredApis = IsrApis<DummyApi<73>> *;

				IsrWithInvalidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithInvalidConstructor>, equal_to(false));
		});

		unit.test("IPerCoreIsr_conceptPassedIsrWithConstructorNotTakingIsrApis_expectFalseIsReturned", []()
		{
			struct IsrWithInvalidConstructor
			{
				using RequiredApis = DummyApis<DummyApi<1>>;

				IsrWithInvalidConstructor(RequiredApis) noexcept
				{
				}

				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IPerCoreIsr<IsrWithInvalidConstructor>, equal_to(false));
		});
	});
}
