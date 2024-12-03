#include <concepts>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IsrWithDefaultTrampoline.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct StubNakedIsrConfig
	{
		struct Handler
		{
			static void onInterrupt(void) noexcept
			{
			}
		};

		static constexpr auto irq = -1;
	};

	struct StubPerCoreIsrConfig
	{
		struct Handler
		{
			void onInterrupt(void) noexcept
			{
			}
		};

		static constexpr auto irq = -1;
	};

	template <typename TIsrConfig>
	struct DummyTrampoline
	{
	};

	template <typename TIsrConfig>
	struct SpyTrampoline
	{
		using Handler = TIsrConfig::Handler;
	};

	suite<> isrWithDefaultTrampolineTest("IsrWithDefaultTrampolineTest Test Suite", [](auto &unit)
	{
		unit.test("ForConfig_getWhenGivenConfigForNakedIsr_expectSameHandlerIsReturned", []()
		{
			using IsrConfig = StubNakedIsrConfig;
			using TrampolinedIsr = IsrWithDefaultTrampoline<DummyTrampoline>::ForConfig<IsrConfig>;
			expect(std::same_as<TrampolinedIsr, typename IsrConfig::Handler>, equal_to(true));
		});

		unit.test("ForConfig_getWhenGivenConfigForPerCoreIsr_expectTrampolineForHandlerIsReturned", []()
		{
			using IsrConfig = StubPerCoreIsrConfig;
			using TrampolinedIsr = IsrWithDefaultTrampoline<SpyTrampoline>::ForConfig<IsrConfig>;
			expect(std::same_as<TrampolinedIsr, SpyTrampoline<IsrConfig>>, equal_to(true));
		});
	});
}
