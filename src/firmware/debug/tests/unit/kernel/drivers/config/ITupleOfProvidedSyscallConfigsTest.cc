#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/ITupleOfProvidedSyscallConfigs.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct DummyContext
	{
	};

	struct DummySyscall
	{
	};

	struct ValidSyscallConfig
	{
		struct Handler
		{
			void onSyscall(DummyContext &, DummySyscall &)
			{
			}
		};
	};

	struct DummyClass
	{
	};

	suite<> itupleOfProvidedSyscallConfigsTest("ITupleOfProvidedSyscallConfigs Test Suite", [](auto &unit)
	{
		unit.test("ITupleOfProvidedSyscallConfigs_conceptPassedEmptyTuple_expectTrueIsReturned", []()
		{
			expect(ITupleOfProvidedSyscallConfigs<std::tuple<>>, equal_to(true));
		});

		unit.test("ITupleOfProvidedSyscallConfigs_conceptPassedTupleOfSingleSyscallConfig_expectTrueIsReturned", []()
		{
			expect(ITupleOfProvidedSyscallConfigs<std::tuple<ValidSyscallConfig>>, equal_to(true));
		});

		unit.test("ITupleOfProvidedSyscallConfigs_conceptPassedTupleOfSingleNonSyscallConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedSyscallConfigs<std::tuple<int>>, equal_to(false));
			expect(ITupleOfProvidedSyscallConfigs<std::tuple<float>>, equal_to(false));
			expect(ITupleOfProvidedSyscallConfigs<std::tuple<bool>>, equal_to(false));
			expect(ITupleOfProvidedSyscallConfigs<std::tuple<DummyClass>>, equal_to(false));
		});

		unit.test("ITupleOfProvidedSyscallConfigs_conceptPassedTupleOfMultipleSyscallConfigs_expectTrueIsReturned", []()
		{
			expect(ITupleOfProvidedSyscallConfigs<std::tuple<ValidSyscallConfig, ValidSyscallConfig, ValidSyscallConfig>>, equal_to(true));
		});

		unit.test("ITupleOfProvidedSyscallConfigs_conceptPassedTupleOfMultipleSyscallConfigsWithNonSyscallConfig_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedSyscallConfigs<std::tuple<ValidSyscallConfig, DummyClass, ValidSyscallConfig, ValidSyscallConfig>>, equal_to(false));
		});

		unit.test("ITupleOfProvidedSyscallConfigs_conceptPassedArrayOfSyscallConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedSyscallConfigs<std::array<ValidSyscallConfig, 5>>, equal_to(false));
		});

		unit.test("ITupleOfProvidedSyscallConfigs_conceptPassedPairOfSyscallConfigs_expectFalseIsReturned", []()
		{
			expect(ITupleOfProvidedSyscallConfigs<std::pair<ValidSyscallConfig, ValidSyscallConfig>>, equal_to(false));
		});
	});
}
