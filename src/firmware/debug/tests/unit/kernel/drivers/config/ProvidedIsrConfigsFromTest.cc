#include <concepts>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/ProvidedIsrConfigsFrom.hh"

#include "DummyDriverConfig.hh"
#include "DummyProvidedIsrConfig.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	suite<> providedIsrConfigsFromIDriverConfigTest("ProvidedIsrConfigsFrom (IDriverConfig) Test Suite", [](auto &unit)
	{
		unit.test("PerConfig_getWhenPassedConfigWithNoProvidedIsrs_expectEmptyTuple", []()
		{
			struct NoTupleConfig
			{
				using Tasks = std::tuple<>;
			};

			expect(std::tuple_size_v<typename ProvidedIsrConfigsFrom<NoTupleConfig>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedConfigWithEmptyTupleOfIsrs_expectEmptyTuple", []()
		{
			struct EmptyTupleConfig
			{
				using ProvidedIsrs = std::tuple<>;
			};

			expect(std::tuple_size_v<typename ProvidedIsrConfigsFrom<EmptyTupleConfig>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedConfigWithSingleIsr_expectTupleOfSameDriver", []()
		{
			struct Config
			{
				using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<1>>;
			};

			expect(std::same_as<typename ProvidedIsrConfigsFrom<Config>::PerConfig, typename Config::ProvidedIsrs>, equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedConfigWithMultipleIsrs_expectTupleOfSameIsrs", []()
		{
			struct Config
			{
				using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<1>, DummyProvidedIsrConfig<2>, DummyProvidedIsrConfig<3>>;
			};

			expect(std::same_as<typename ProvidedIsrConfigsFrom<Config>::PerConfig, typename Config::ProvidedIsrs>, equal_to(true));
		});
	});

	suite<> providedIsrConfigsFromITupleOfDriverConfigsTest("ProvidedIsrConfigsFrom (ITupleOfDriverConfigs) Test Suite", [](auto &unit)
	{
		unit.test("PerConfig_getWhenPassedEmptyTupleOfConfigs_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<typename ProvidedIsrConfigsFrom<std::tuple<>>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedTupleOfSingleDriverConfig_expectTupleOfSameIsrsInDriverConfig", []()
		{
			struct DriverConfig
			{
				using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<1>, DummyProvidedIsrConfig<1>, DummyProvidedIsrConfig<2>>;
			};

			expect(
				std::same_as<
					typename ProvidedIsrConfigsFrom<std::tuple<DriverConfig>>::PerConfig,
					typename DriverConfig::ProvidedIsrs>,
				equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedTupleOfMultipleDriverConfigs_expectTupleOfConcatenatedIsrsFromDriverConfigs", []()
		{
			struct DriverConfig1
			{
				using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<2>, DummyProvidedIsrConfig<3>>;
			};

			struct DriverConfig2
			{
				using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<5>>;
			};

			struct DriverConfig3
			{
				using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<8>, DummyProvidedIsrConfig<8>, DummyProvidedIsrConfig<13>>;
			};

			expect(
				std::same_as<
					typename ProvidedIsrConfigsFrom<std::tuple<DriverConfig1, DriverConfig2, DriverConfig3>>::PerConfig,
					decltype(std::tuple_cat(
						typename DriverConfig1::ProvidedIsrs{},
						typename DriverConfig2::ProvidedIsrs{},
						typename DriverConfig3::ProvidedIsrs{}))>,
				equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedTupleOfMultipleDriverConfigsSomeWithoutProvidedIsrs_expectTupleOfConcatenatedIsrsFromDriverConfigs", []()
		{
			struct DriverConfig1
			{
				using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<2>, DummyProvidedIsrConfig<3>>;
			};

			struct DriverConfig2
			{
				using ProvidedApis = std::tuple<typename DummyDriverConfig<7>::UselessApiConfig>;
			};

			struct DriverConfig3
			{
				using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<5>, DummyProvidedIsrConfig<8>>;
			};

			expect(
				std::same_as<
					typename ProvidedIsrConfigsFrom<std::tuple<DriverConfig1, DriverConfig2, DriverConfig3>>::PerConfig,
					decltype(std::tuple_cat(typename DriverConfig1::ProvidedIsrs{}, typename DriverConfig3::ProvidedIsrs{}))>,
				equal_to(true));
		});
	});

	suite<> providedIsrConfigsFromIKernelConfigTest("ProvidedIsrConfigsFrom (IKernelConfig) Test Suite", [](auto &unit)
	{
		unit.test("PerConfig_getWhenPassedConfigWithNoDrivers_expectEmptyTuple", []()
		{
			struct NoDriversKernelConfig
			{
				using Tasks = typename DummyDriverConfig<123>::Tasks;
			};

			expect(std::tuple_size_v<typename ProvidedIsrConfigsFrom<NoDriversKernelConfig>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedConfigWithEmptyTupleOfDrivers_expectEmptyTuple", []()
		{
			struct EmptyDriversKernelConfig
			{
				using Drivers = std::tuple<>;
			};

			expect(std::tuple_size_v<typename ProvidedIsrConfigsFrom<EmptyDriversKernelConfig>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedConfigWithSingleDriverWithoutProvidedIsrs_expectEmptyTuple", []()
		{
			struct NoIsrsKernelConfig
			{
				struct DriverWithNoIsrs
				{
					using ProvidedSyscalls = typename DummyDriverConfig<72>::ProvidedSyscalls;
				};

				using Drivers = std::tuple<DriverWithNoIsrs>;
			};

			expect(std::tuple_size_v<typename ProvidedIsrConfigsFrom<NoIsrsKernelConfig>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedConfigWithDriversContainingProvidedIsrs_expectTupleOfConcatenatedIsrsFromDriverConfigs", []()
		{
			struct KernelConfig
			{
				struct DriverConfig1
				{
					using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<3>>;
				};

				struct DriverConfig2
				{
					using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<1>, DummyProvidedIsrConfig<4>, DummyProvidedIsrConfig<1>>;
				};

				struct DriverConfig3
				{
					using ProvidedIsrs = std::tuple<>;
				};

				struct DriverConfig4
				{
					using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<5>>;
				};

				using Drivers = std::tuple<DriverConfig1, DriverConfig2, DriverConfig3, DriverConfig4>;
			};

			expect(
				std::same_as<
					typename ProvidedIsrConfigsFrom<KernelConfig>::PerConfig,
					decltype(std::tuple_cat(
						typename KernelConfig::DriverConfig1::ProvidedIsrs{},
						typename KernelConfig::DriverConfig2::ProvidedIsrs{},
						typename KernelConfig::DriverConfig3::ProvidedIsrs{},
						typename KernelConfig::DriverConfig4::ProvidedIsrs{}))>,
				equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedConfigWithDriversContainingSomeWithAndWithoutProvidedIsrs_expectTupleOfConcatenatedIsrsFromDriverConfigs", []()
		{
			struct KernelConfig
			{
				struct DriverConfig1
				{
					using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<4>, DummyProvidedIsrConfig<2>>;
				};

				struct DriverConfig2
				{
					using ProvidedApis = DummyDriverConfig<1>::ProvidedApis;
				};

				struct DriverConfig3
				{
					using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<2>, DummyProvidedIsrConfig<4>>;
				};

				using Drivers = std::tuple<DriverConfig1, DriverConfig2, DriverConfig3>;
			};

			expect(
				std::same_as<
					typename ProvidedIsrConfigsFrom<KernelConfig>::PerConfig,
					decltype(std::tuple_cat(
						typename KernelConfig::DriverConfig1::ProvidedIsrs{},
						typename KernelConfig::DriverConfig3::ProvidedIsrs{}))>,
				equal_to(true));
		});
	});

	suite<> providedIsrConfigsFromITupleOfKernelConfigsTest("ProvidedIsrConfigsFrom (ITupleOfKernelConfigs) Test Suite", [](auto &unit)
	{
		unit.test("PerConfig_getWhenPassedEmptyTuple_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<typename ProvidedIsrConfigsFrom<std::tuple<>>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedSingleConfigWithEmptyTupleOfDrivers_expectEmptyTuple", []()
		{
			struct EmptyDriversKernelConfig
			{
				using Drivers = std::tuple<>;
			};

			expect(std::tuple_size_v<typename ProvidedIsrConfigsFrom<std::tuple<EmptyDriversKernelConfig>>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedSingleConfigWithSingleTupleOfDrivers_expectSameTupleFromDriverConfig", []()
		{
			struct KernelConfig
			{
				struct DriverConfig
				{
					using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<11>, DummyProvidedIsrConfig<22>, DummyProvidedIsrConfig<33>>;
				};

				using Drivers = std::tuple<DriverConfig>;
			};

			expect(
				std::same_as<
					typename ProvidedIsrConfigsFrom<std::tuple<KernelConfig>>::PerConfig,
					typename KernelConfig::DriverConfig::ProvidedIsrs>,
				equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedMultipleConfigsWithMixOfDriversAndNoDriversWithAndWithoutProvidedIsrs_expectTupleOfConcatenatedIsrsFromDriverConfigs", []()
		{
			struct KernelConfigWithDriversAndProvidedIsrs
			{
				struct DriverConfig1
				{
					using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<2>, DummyProvidedIsrConfig<4>>;
				};

				struct DriverConfig2
				{
					using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<6>, DummyProvidedIsrConfig<8>>;
				};

				using Drivers = std::tuple<DriverConfig1, DriverConfig2>;
			};

			struct KernelConfigWithDriversAndNoProvidedIsrs
			{
				struct DriverConfig1
				{
					using ProvidedApis = DummyDriverConfig<10>::ProvidedApis;
				};

				struct DriverConfig2
				{
					using ProvidedIsrs = std::tuple<DummyProvidedIsrConfig<10>>;
				};

				using Drivers = std::tuple<DriverConfig1, DriverConfig2>;
			};

			struct KernelConfigWithoutDrivers
			{
				using Tasks = std::tuple<>;
			};

			expect(
				std::same_as<
					typename ProvidedIsrConfigsFrom<std::tuple<
						KernelConfigWithDriversAndProvidedIsrs,
						KernelConfigWithDriversAndNoProvidedIsrs,
						KernelConfigWithoutDrivers,
						KernelConfigWithDriversAndNoProvidedIsrs>>::PerConfig,
					decltype(tuple_cat(
						typename KernelConfigWithDriversAndProvidedIsrs::DriverConfig1::ProvidedIsrs{},
						typename KernelConfigWithDriversAndProvidedIsrs::DriverConfig2::ProvidedIsrs{},
						typename KernelConfigWithDriversAndNoProvidedIsrs::DriverConfig2::ProvidedIsrs{},
						typename KernelConfigWithDriversAndNoProvidedIsrs::DriverConfig2::ProvidedIsrs{}))>,
				equal_to(true));
		});
	});
}
