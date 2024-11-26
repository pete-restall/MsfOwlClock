#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/IIsr.hh"

using namespace mettle;

using namespace smeg::kernel::drivers;

namespace smeg::tests::unit::kernel::drivers
{
	suite<> iisrTest("IIsr Test Suite", [](auto &unit)
	{
		unit.test("IIsr_conceptPassedValidIsr_expectTrueIsReturned", []()
		{
			struct ValidIsr
			{
				static void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<ValidIsr>, equal_to(true));
		});

		unit.test("IIsr_conceptPassedIsrMissingNoExcept_expectFalseIsReturned", []()
		{
			struct IsrMissingNoExcept
			{
				static void onInterrupt(void)
				{
				}
			};

			expect(IIsr<IsrMissingNoExcept>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrWithNonStaticHandler_expectFalseIsReturned", []()
		{
			struct IsrWithNonStaticHandler
			{
				void onInterrupt(void) noexcept
				{
				}
			};

			expect(IIsr<IsrWithNonStaticHandler>, equal_to(false));
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
			struct IsrTakingValue
			{
				static void onInterrupt(int) noexcept
				{
				}
			};

			expect(IIsr<IsrTakingValue>, equal_to(false));
		});

		unit.test("IIsr_conceptPassedIsrReturningValue_expectFalseIsReturned", []()
		{
			struct IsrReturningValue
			{
				static int onInterrupt(void) noexcept
				{
					return 1;
				}
			};

			expect(IIsr<IsrReturningValue>, equal_to(false));
		});
	});
}
