#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/ITupleOfProvidedApiConfigs.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct ValidApiConfig
	{
		template <typename... T>
		struct Interface
		{
		};

		struct Type
		{
		};
	};

	struct DummyClass
	{
	};

	suite<> itupleOfProvidedApiConfigsTest("ITupleOfProvidedApiConfigs Test Suite", [](auto &unit)
	{
		unit.test("ITupleOfProvidedApiConfigs_conceptPassedEmptyTuple_expectTrueIsReturned", []()
		{
			expect(ITupleOfProvidedApiConfigs<std::tuple<>>, equal_to(true));
		});

		unit.test("ITupleOfProvidedApiConfigs_conceptPassedTupleOfSingleApiConfig_expectTrueIsReturned", []()
		{
			expect(ITupleOfProvidedApiConfigs<std::tuple<ValidApiConfig>>, equal_to(true));
		});

		unit.test("ITupleOfProvidedApiConfigs_conceptPassedTupleOfSingleNonApiConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedApiConfigs<std::tuple<int>>, equal_to(false));
			expect(ITupleOfProvidedApiConfigs<std::tuple<float>>, equal_to(false));
			expect(ITupleOfProvidedApiConfigs<std::tuple<bool>>, equal_to(false));
			expect(ITupleOfProvidedApiConfigs<std::tuple<DummyClass>>, equal_to(false));
		});

		unit.test("ITupleOfProvidedApiConfigs_conceptPassedTupleOfMultipleApiConfigs_expectTrueIsReturned", []()
		{
			expect(ITupleOfProvidedApiConfigs<std::tuple<ValidApiConfig, ValidApiConfig, ValidApiConfig>>, equal_to(true));
		});

		unit.test("ITupleOfProvidedApiConfigs_conceptPassedTupleOfMultipleApiConfigsWithNonApiConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedApiConfigs<std::tuple<ValidApiConfig, ValidApiConfig, DummyClass, ValidApiConfig>>, equal_to(false));
		});

		unit.test("ITupleOfProvidedApiConfigs_conceptPassedArrayOfApiConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedApiConfigs<std::array<ValidApiConfig, 5>>, equal_to(false));
		});

		unit.test("ITupleOfProvidedApiConfigs_conceptPassedPairOfApiConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedApiConfigs<std::pair<ValidApiConfig, ValidApiConfig>>, equal_to(false));
		});
	});
}
