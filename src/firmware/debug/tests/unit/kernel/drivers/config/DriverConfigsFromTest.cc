#include <concepts>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/DriverConfigsFrom.hh"

#include "DummyDriverConfig.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	suite<> driverConfigsFromTest("DriverConfigsFrom Test Suite", [](auto &unit)
	{
		unit.test("PerConfig_getWhenPassedConfigWithEmptyTupleOfDrivers_expectEmptyTuple", []()
		{
			struct EmptyTupleConfig
			{
				using Drivers = std::tuple<>;
			};

			expect(std::tuple_size_v<typename DriverConfigsFrom<EmptyTupleConfig>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedConfigWithSingleDriver_expectTupleOfSameDriver", []()
		{
			struct Config
			{
				using Drivers = std::tuple<StubDriverConfig<1>>;
			};

			expect(std::same_as<typename DriverConfigsFrom<Config>::PerConfig, typename Config::Drivers>, equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedConfigWithMultipleDrivers_expectTupleOfSameDrivers", []()
		{
			struct Config
			{
				using Drivers = std::tuple<StubDriverConfig<1>, StubDriverConfig<2>, StubDriverConfig<3>>;
			};

			expect(std::same_as<typename DriverConfigsFrom<Config>::PerConfig, typename Config::Drivers>, equal_to(true));
		});
	});
}
