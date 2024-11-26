#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/ITupleOfProvidedIsrConfigs.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct ValidIsrConfig
	{
		struct Handler
		{
			static void onInterrupt(void) noexcept
			{
			}
		};

		static constexpr auto irq = 123;
	};

	struct DummyClass
	{
	};

	suite<> itupleOfProvidedIsrConfigsTest("ITupleOfProvidedIsrConfigs Test Suite", [](auto &unit)
	{
		unit.test("ITupleOfProvidedIsrConfigs_conceptPassedEmptyTuple_expectTrueIsReturned", []()
		{
			expect(ITupleOfProvidedIsrConfigs<std::tuple<>>, equal_to(true));
		});

		unit.test("ITupleOfProvidedIsrConfigs_conceptPassedTupleOfSingleIsrConfig_expectTrueIsReturned", []()
		{
			expect(ITupleOfProvidedIsrConfigs<std::tuple<ValidIsrConfig>>, equal_to(true));
		});

		unit.test("ITupleOfProvidedIsrConfigs_conceptPassedTupleOfSingleNonIsrConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedIsrConfigs<std::tuple<int>>, equal_to(false));
			expect(ITupleOfProvidedIsrConfigs<std::tuple<float>>, equal_to(false));
			expect(ITupleOfProvidedIsrConfigs<std::tuple<bool>>, equal_to(false));
			expect(ITupleOfProvidedIsrConfigs<std::tuple<DummyClass>>, equal_to(false));
		});

		unit.test("ITupleOfProvidedIsrConfigs_conceptPassedTupleOfMultipleIsrConfigs_expectTrueIsReturned", []()
		{
			expect(ITupleOfProvidedIsrConfigs<std::tuple<ValidIsrConfig, ValidIsrConfig, ValidIsrConfig, ValidIsrConfig, ValidIsrConfig>>, equal_to(true));
		});

		unit.test("ITupleOfProvidedIsrConfigs_conceptPassedTupleOfMultipleIsrConfigsWithNonIsrConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedIsrConfigs<std::tuple<ValidIsrConfig, ValidIsrConfig, DummyClass, ValidIsrConfig, ValidIsrConfig>>, equal_to(false));
		});

		unit.test("ITupleOfProvidedIsrConfigs_conceptPassedArrayOfIsrConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedIsrConfigs<std::array<ValidIsrConfig, 5>>, equal_to(false));
		});

		unit.test("ITupleOfProvidedIsrConfigs_conceptPassedPairOfIsrConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedIsrConfigs<std::pair<ValidIsrConfig, ValidIsrConfig>>, equal_to(false));
		});
	});
}
