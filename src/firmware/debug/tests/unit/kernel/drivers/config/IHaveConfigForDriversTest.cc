#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IHaveConfigForDrivers.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	template <auto X>
	struct StubDriverConfig
	{
		using ProvidedApis = std::tuple<>;
		using ProvidedIsrs = std::tuple<>;
		using ProvidedSyscalls = std::tuple<>;
		using Tasks = std::tuple<>;
	};

	suite<> iHaveConfigForDriversTest("IHaveConfigForDrivers Test Suite", [](auto &unit)
	{
		unit.test("IHaveConfigForDrivers_conceptPassedConfigWithoutDrivers_expectFalseIsReturned", []()
		{
			struct ConfigWithoutDrivers
			{
			};

			expect(IHaveConfigForDrivers<ConfigWithoutDrivers>, equal_to(false));
		});

		unit.test("IHaveConfigForDrivers_conceptPassedConfigWithEmptyTuple_expectTrueIsReturned", []()
		{
			struct ConfigWithEmptyDrivers
			{
				using Drivers = std::tuple<>;
			};

			expect(IHaveConfigForDrivers<ConfigWithEmptyDrivers>, equal_to(true));
		});

		unit.test("IHaveConfigForDrivers_conceptPassedConfigWithSingleDriverConfig_expectTrueIsReturned", []()
		{
			struct ConfigWithSingleDriver
			{
				using Drivers = std::tuple<StubDriverConfig<1>>;
			};

			expect(IHaveConfigForDrivers<ConfigWithSingleDriver>, equal_to(true));
		});

		unit.test("IHaveConfigForDrivers_conceptPassedConfigWithSingleInvalidDriverConfig_expectFalseIsReturned", []()
		{
			struct ConfigWithSingleInvalidDriver
			{
				struct NonDriverConfig
				{
					struct ProvidedSyscalls
					{
					};
				};

				using Drivers = std::tuple<NonDriverConfig>;
			};

			expect(IHaveConfigForDrivers<ConfigWithSingleInvalidDriver>, equal_to(false));
		});

		unit.test("IHaveConfigForDrivers_conceptPassedConfigWithMultipleDriverConfigs_expectTrueIsReturned", []()
		{
			struct ConfigWithMultipleDrivers
			{
				using Drivers = std::tuple<StubDriverConfig<1>, StubDriverConfig<2>, StubDriverConfig<3>>;
			};

			expect(IHaveConfigForDrivers<ConfigWithMultipleDrivers>, equal_to(true));
		});

		unit.test("IHaveConfigForDrivers_conceptPassedConfigWithMultipleDriverConfigsIncludingNonDriverConfig_expectFalseIsReturned", []()
		{
			struct ConfigWithInvalidDriver
			{
				struct NonDriverConfig
				{
					struct ProvidedApis
					{
					};
				};

				using Drivers = std::tuple<StubDriverConfig<1>, StubDriverConfig<2>, NonDriverConfig, StubDriverConfig<3>>;
			};

			expect(IHaveConfigForDrivers<ConfigWithInvalidDriver>, equal_to(false));
		});

		unit.test("IHaveConfigForDrivers_conceptPassedConfigWithArrayOfDrivers_expectFalseIsReturned", []()
		{
			struct ConfigWithArrayOfDrivers
			{
				using Drivers = std::array<StubDriverConfig<1>, 3>;
			};

			expect(IHaveConfigForDrivers<ConfigWithArrayOfDrivers>, equal_to(false));
		});

		unit.test("IHaveConfigForDrivers_conceptPassedConfigWithPairOfDrivers_expectFalseIsReturned", []()
		{
			struct ConfigWithPairOfDrivers
			{
				using Drivers = std::pair<StubDriverConfig<1>, StubDriverConfig<2>>;
			};

			expect(IHaveConfigForDrivers<ConfigWithPairOfDrivers>, equal_to(false));
		});
	});
}
