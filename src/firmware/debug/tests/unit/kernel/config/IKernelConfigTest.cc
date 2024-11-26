#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/config/IKernelConfig.hh"

using namespace mettle;

using namespace smeg::kernel::config;

namespace smeg::tests::unit::kernel::config
{
	suite<> iKernelConfigTest("IKernelConfig Test Suite", [](auto &unit)
	{
		unit.test("IKernelConfig_conceptPassedNonClass_expectFalseIsReturned", []()
		{
			expect(IKernelConfig<int>, equal_to(false));
			expect(IKernelConfig<double>, equal_to(false));
			expect(IKernelConfig<bool>, equal_to(false));
		});

		unit.test("IKernelConfig_conceptPassedEmptyConfig_expectFalseIsReturned", []()
		{
			struct EmptyConfig
			{
			};

			expect(IKernelConfig<EmptyConfig>, equal_to(false));
		});

		unit.test("IKernelConfig_conceptPassedConfigWithRequiredDrivers_expectTrueIsReturned", []()
		{
			struct ConfigWithRequiredDrivers
			{
				using RequiredDrivers = std::tuple<>;
			};

			expect(IKernelConfig<ConfigWithRequiredDrivers>, equal_to(true));
		});

		unit.test("IKernelConfig_conceptPassedConfigWithProvidedDrivers_expectTrueIsReturned", []()
		{
			struct ConfigWithProvidedDrivers
			{
				using Drivers = std::tuple<>;
			};

			expect(IKernelConfig<ConfigWithProvidedDrivers>, equal_to(true));
		});

		unit.test("IKernelConfig_conceptPassedConfigWithProvidedTasks_expectTrueIsReturned", []()
		{
			struct ConfigWithProvidedTasks
			{
				using Tasks = std::tuple<>;
			};

			expect(IKernelConfig<ConfigWithProvidedTasks>, equal_to(true));
		});
	});
}
