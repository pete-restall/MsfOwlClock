#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IProvidedIsrConfig.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct StubIsr
	{
		static void onInterrupt(void) noexcept
		{
		}
	};

	struct ValidIsrConfig
	{
		using Handler = StubIsr;
		static constexpr auto irq = 123;
	};

	struct IsrConfigWithoutHandler
	{
		static constexpr auto irq = 123;
	};

	struct IsrConfigWithNonIsrHandler
	{
		struct Handler
		{
			static void onInterrupt(void)
			{
			}
		};

		static constexpr auto irq = 123;
	};

	template <auto Irq>
	struct IsrConfigWithNonIntegerIrq
	{
		using Handler = StubIsr;
		static constexpr auto irq = Irq;
	};

	struct IsrConfigWithoutIrq
	{
		using Handler = StubIsr;
	};

	struct IsrConfigWithNonConstexprIrq
	{
		using Handler = StubIsr;
		static int irq;
	};

	int IsrConfigWithNonConstexprIrq::irq(1);

	struct DummyClass
	{
	};

	suite<> iprovidedIsrConfigTest("IProvidedIsrConfig Test Suite", [](auto &unit)
	{
		unit.test("IProvidedIsrConfig_conceptPassedValidIsrConfig_expectTrueIsReturned", []()
		{
			expect(IProvidedIsrConfig<ValidIsrConfig>, equal_to(true));
		});

		unit.test("IProvidedIsrConfig_conceptPassedIsrConfigWithoutHandler_expectFalseIsReturned", []()
		{
			expect(IProvidedIsrConfig<IsrConfigWithoutHandler>, equal_to(false));
		});

		unit.test("IProvidedIsrConfig_conceptPassedIsrConfigWitNonIsrHandler_expectFalseIsReturned", []()
		{
			expect(IProvidedIsrConfig<IsrConfigWithNonIsrHandler>, equal_to(false));
		});

		unit.test("IProvidedIsrConfig_conceptPassedIsrConfigWithNonIntegerIrq_expectFalseIsReturned", []()
		{
			expect(IProvidedIsrConfig<IsrConfigWithNonIntegerIrq<1.23>>, equal_to(false));
			expect(IProvidedIsrConfig<IsrConfigWithNonIntegerIrq<DummyClass{}>>, equal_to(false));
			expect(IProvidedIsrConfig<IsrConfigWithNonIntegerIrq<true>>, equal_to(false));
		});

		unit.test("IProvidedIsrConfig_conceptPassedIsrConfigWithoutIrq_expectFalseIsReturned", []()
		{
			expect(IProvidedIsrConfig<IsrConfigWithoutIrq>, equal_to(false));
		});

		unit.test("IProvidedIsrConfig_conceptPassedIsrConfigWithNonConstexprIrq_expectFalseIsReturned", []()
		{
			expect(IProvidedIsrConfig<IsrConfigWithNonConstexprIrq>, equal_to(false));
		});
	});
}
