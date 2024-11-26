#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/config/ITupleOfKernelConfigs.hh"

using namespace mettle;

using namespace smeg::kernel::config;

namespace smeg::tests::unit::kernel::config
{
	struct ValidKernelConfig
	{
		using Tasks = std::tuple<>;
	};

	struct DummyClass
	{
	};

	suite<> itupleOfKernelConfigsTest("ITupleOfKernelConfigs Test Suite", [](auto &unit)
	{
		unit.test("ITupleOfKernelConfigs_conceptPassedEmptyTuple_expectTrueIsReturned", []()
		{
			expect(ITupleOfKernelConfigs<std::tuple<>>, equal_to(true));
		});

		unit.test("ITupleOfKernelConfigs_conceptPassedTupleOfSingleKernelConfig_expectTrueIsReturned", []()
		{
			expect(ITupleOfKernelConfigs<std::tuple<ValidKernelConfig>>, equal_to(true));
		});

		unit.test("ITupleOfKernelConfigs_conceptPassedTupleOfSingleNonKernelConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfKernelConfigs<std::tuple<int>>, equal_to(false));
			expect(ITupleOfKernelConfigs<std::tuple<float>>, equal_to(false));
			expect(ITupleOfKernelConfigs<std::tuple<bool>>, equal_to(false));
			expect(ITupleOfKernelConfigs<std::tuple<DummyClass>>, equal_to(false));
		});

		unit.test("ITupleOfKernelConfigs_conceptPassedTupleOfMultipleKernelConfigs_expectTrueIsReturned", []()
		{
			expect(ITupleOfKernelConfigs<std::tuple<ValidKernelConfig, ValidKernelConfig, ValidKernelConfig, ValidKernelConfig>>, equal_to(true));
		});

		unit.test("ITupleOfKernelConfigs_conceptPassedTupleOfMultipleKernelConfigsWithNonKernelConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfKernelConfigs<std::tuple<ValidKernelConfig, DummyClass, ValidKernelConfig, ValidKernelConfig>>, equal_to(false));
		});

		unit.test("ITupleOfKernelConfigs_conceptPassedArrayOfKernelConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfKernelConfigs<std::array<ValidKernelConfig, 5>>, equal_to(false));
		});

		unit.test("ITupleOfKernelConfigs_conceptPassedPairOfKernelConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfKernelConfigs<std::pair<ValidKernelConfig, ValidKernelConfig>>, equal_to(false));
		});
	});
}
