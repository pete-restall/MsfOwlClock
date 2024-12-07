#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/config/McuCoreTraitsFrom.hh"

using namespace mettle;

using namespace smeg::kernel::config;

namespace smeg::tests::unit::kernel::config
{
	template <auto N>
	struct ConfigWithMcuCoreTraits
	{
		struct McuCoreTraits
		{
			static constexpr auto numberOfMcuCores = N;

			static auto getMcuCoreId(void) noexcept
			{
				return 0;
			}
		};

		using Drivers = std::tuple<>;
	};

	struct ConfigWithInvalidMcuCoreTraits
	{
		struct McuCoreTraits
		{
			static constexpr auto whatever = 12345;
		};

		using Drivers = std::tuple<>;
	};

	struct ConfigWithoutMcuCoreTraits
	{
		using Drivers = std::tuple<>;
	};

	suite<> mcuCoreTraitsFromTest("McuCoreTraitsFrom Test Suite", [](auto &unit)
	{
		unit.test("McuCoreTraitsFrom_getWithSingleConfig_expectMcuCoreTraitsAreReturned", []()
		{
			using Config = ConfigWithMcuCoreTraits<65>;
			using ExpectedMcuCoreTraits = Config::McuCoreTraits;
			expect(std::same_as<McuCoreTraitsFrom<Config>, ExpectedMcuCoreTraits>, equal_to(true));
		});

		unit.test("McuCoreTraitsFrom_getWithTupleOfConfigs_expectMcuCoreTraitsAreReturned", []()
		{
			using ExpectedConfig = ConfigWithMcuCoreTraits<17>;
			using ExpectedMcuCoreTraits = ExpectedConfig::McuCoreTraits;
			using TupleOfConfigs = std::tuple<
				ConfigWithoutMcuCoreTraits,
				ConfigWithInvalidMcuCoreTraits,
				ExpectedConfig,
				ConfigWithInvalidMcuCoreTraits>;

			expect(std::same_as<McuCoreTraitsFrom<TupleOfConfigs>, ExpectedMcuCoreTraits>, equal_to(true));
		});

		unit.test("McuCoreTraitsFrom_getWithConfigOfTupleOfConfigs_expectMcuCoreTraitsAreReturned", []()
		{
			using ExpectedConfig = ConfigWithMcuCoreTraits<1>;
			using ExpectedMcuCoreTraits = ExpectedConfig::McuCoreTraits;
			using TupleOfConfigs = std::tuple<
				ConfigWithoutMcuCoreTraits,
				ExpectedConfig,
				ConfigWithInvalidMcuCoreTraits,
				ConfigWithoutMcuCoreTraits>;

			struct HasTupleOfConfigs
			{
				using AsTuple = TupleOfConfigs;
			};

			expect(std::same_as<McuCoreTraitsFrom<HasTupleOfConfigs>, ExpectedMcuCoreTraits>, equal_to(true));
		});
	});
}
