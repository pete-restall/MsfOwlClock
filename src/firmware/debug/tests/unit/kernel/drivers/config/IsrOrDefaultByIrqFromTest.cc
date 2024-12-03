#include <concepts>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IsrOrDefaultByIrqFrom.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	template <auto Irq>
	struct DummyIsr
	{
		static void onInterrupt(void) noexcept
		{
		}
	};

	template <auto Irq>
	struct StubIsrConfig
	{
		using Handler = DummyIsr<Irq>;
		static constexpr auto irq = Irq;
	};

	template <auto Irq>
	using NonMatchingIsrConfig = StubIsrConfig<Irq>;

	suite<> isrOrDefaultByIrqFromTupleTest("IsrOrDefaultByIrqFrom (std::tuple<>) Test Suite", [](auto &unit)
	{
		unit.test("Config_getWhenGivenEmptyTupleOfConfigs_expectConfigWithDefaultIsrIsReturned", []()
		{
			using NoConfigs = std::tuple<>;
			using DefaultIsr = DummyIsr<1>;
			using ReturnedConfig = IsrOrDefaultByIrqFrom<NoConfigs, 0, DefaultIsr>::Config;
			expect(std::same_as<typename ReturnedConfig::Handler, DefaultIsr>, equal_to(true));
		});

		unit.test("Config_getWhenGivenTupleOfSingleConfigWhoseIrqDoesNotMatch_expectConfigWithDefaultIsrIsReturned", []()
		{
			using DefaultIsr = DummyIsr<1>;
			using ReturnedConfig = IsrOrDefaultByIrqFrom<std::tuple<StubIsrConfig<7>>, 8, DefaultIsr>::Config;
			expect(std::same_as<typename ReturnedConfig::Handler, DefaultIsr>, equal_to(true));
		});

		unit.test("Config_getWhenGivenTupleOfSingleConfigWhoseIrqMatches_expectSameConfigIsReturned", []()
		{
			using MatchingIsrConfig = StubIsrConfig<7>;
			using DefaultIsr = DummyIsr<1>;
			using ReturnedConfig = IsrOrDefaultByIrqFrom<std::tuple<MatchingIsrConfig>, MatchingIsrConfig::irq, DefaultIsr>::Config;
			expect(std::same_as<ReturnedConfig, MatchingIsrConfig>, equal_to(true));
		});

		unit.test("Config_getWhenGivenTupleOfConfigsContainingOneWhoseIrqMatches_expectConfigWithMatchingIrqIsReturned", []()
		{
			using MatchingIsrConfig = StubIsrConfig<872>;
			using DefaultIsr = DummyIsr<19>;
			using ReturnedConfig = IsrOrDefaultByIrqFrom<
				std::tuple<
					NonMatchingIsrConfig<2>,
					NonMatchingIsrConfig<-29>,
					NonMatchingIsrConfig<17>,
					MatchingIsrConfig,
					NonMatchingIsrConfig<13>,
					NonMatchingIsrConfig<3>>,
				MatchingIsrConfig::irq,
				DefaultIsr>::Config;

			expect(std::same_as<ReturnedConfig, MatchingIsrConfig>, equal_to(true));
		});
	});
}
