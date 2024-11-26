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
		unit.test("Handler_getWhenGivenEmptyTupleOfConfigs_expectDefaultIsr", []()
		{
			using NoConfigs = std::tuple<>;
			using DefaultIsr = DummyIsr<1>;
			using ReturnedIsr = IsrOrDefaultByIrqFrom<NoConfigs, 0, DefaultIsr>::Handler;
			expect(std::same_as<ReturnedIsr, DefaultIsr>, equal_to(true));
		});

		unit.test("Handler_getWhenGivenTupleOfSingleConfigWhoseIrqDoesNotMatch_expectDefaultIsr", []()
		{
			using DefaultIsr = DummyIsr<1>;
			using ReturnedIsr = IsrOrDefaultByIrqFrom<std::tuple<StubIsrConfig<7>>, 8, DefaultIsr>::Handler;
			expect(std::same_as<ReturnedIsr, DefaultIsr>, equal_to(true));
		});

		unit.test("Handler_getWhenGivenTupleOfSingleConfigWhoseIrqMatches_expectIsrWithMatchingIrq", []()
		{
			using MatchingIsrConfig = StubIsrConfig<7>;
			using DefaultIsr = DummyIsr<1>;
			using ReturnedIsr = IsrOrDefaultByIrqFrom<std::tuple<MatchingIsrConfig>, MatchingIsrConfig::irq, DefaultIsr>::Handler;
			expect(std::same_as<ReturnedIsr, typename MatchingIsrConfig::Handler>, equal_to(true));
		});

		unit.test("Handler_getWhenGivenTupleOfConfigsContainingOneWhoseIrqMatches_expectIsrWithMatchingIrq", []()
		{
			using MatchingIsrConfig = StubIsrConfig<872>;
			using DefaultIsr = DummyIsr<19>;
			using ReturnedIsr = IsrOrDefaultByIrqFrom<
				std::tuple<
					NonMatchingIsrConfig<2>,
					NonMatchingIsrConfig<29>,
					NonMatchingIsrConfig<17>,
					MatchingIsrConfig,
					NonMatchingIsrConfig<13>,
					NonMatchingIsrConfig<3>>,
				MatchingIsrConfig::irq,
				DefaultIsr>::Handler;

			expect(std::same_as<ReturnedIsr, typename MatchingIsrConfig::Handler>, equal_to(true));
		});
	});
}
