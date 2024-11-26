#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/ITupleOfDriverConfigs.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct ValidDriverConfig1
	{
		using ProvidedIsrs = std::tuple<>;
	};

	struct ValidDriverConfig2
	{
		using ProvidedApis = std::tuple<>;
	};

	struct ValidDriverConfig3
	{
		using ProvidedSyscalls = std::tuple<>;
	};

	struct DummyClass
	{
	};

	suite<> itupleOfDriverConfigsTest("ITupleOfDriverConfigs Test Suite", [](auto &unit)
	{
		unit.test("ITupleOfDriverConfigs_conceptPassedEmptyTuple_expectTrueIsReturned", []()
		{
			expect(ITupleOfDriverConfigs<std::tuple<>>, equal_to(true));
		});

		unit.test("ITupleOfDriverConfigs_conceptPassedTupleOfSingleDriverConfig_expectTrueIsReturned", []()
		{
			expect(ITupleOfDriverConfigs<std::tuple<ValidDriverConfig1>>, equal_to(true));
			expect(ITupleOfDriverConfigs<std::tuple<ValidDriverConfig2>>, equal_to(true));
			expect(ITupleOfDriverConfigs<std::tuple<ValidDriverConfig3>>, equal_to(true));
		});

		unit.test("ITupleOfDriverConfigs_conceptPassedTupleOfSingleNonDriverConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfDriverConfigs<std::tuple<int>>, equal_to(false));
			expect(ITupleOfDriverConfigs<std::tuple<float>>, equal_to(false));
			expect(ITupleOfDriverConfigs<std::tuple<bool>>, equal_to(false));
			expect(ITupleOfDriverConfigs<std::tuple<DummyClass>>, equal_to(false));
		});

		unit.test("ITupleOfDriverConfigs_conceptPassedTupleOfMultipleDriverConfigs_expectTrueIsReturned", []()
		{
			expect(ITupleOfDriverConfigs<std::tuple<ValidDriverConfig1, ValidDriverConfig2, ValidDriverConfig3>>, equal_to(true));
		});

		unit.test("ITupleOfDriverConfigs_conceptPassedTupleOfMultipleDriverConfigsWithNonDriverConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfDriverConfigs<std::tuple<ValidDriverConfig3, ValidDriverConfig1, DummyClass, ValidDriverConfig2>>, equal_to(false));
		});

		unit.test("ITupleOfDriverConfigs_conceptPassedArrayOfDriverConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfDriverConfigs<std::array<ValidDriverConfig1, 5>>, equal_to(false));
		});

		unit.test("ITupleOfDriverConfigs_conceptPassedPairOfDriverConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfDriverConfigs<std::pair<ValidDriverConfig2, ValidDriverConfig3>>, equal_to(false));
		});
	});
}
