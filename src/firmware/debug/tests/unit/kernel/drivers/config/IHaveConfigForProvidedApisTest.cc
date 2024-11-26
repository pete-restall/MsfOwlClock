#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IHaveConfigForProvidedApis.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	template <auto X>
	struct StubApiConfig
	{
		template <typename TApi>
		struct Interface
		{
		};

		struct Type
		{
		};
	};

	suite<> iHaveConfigForProvidedApisTest("IHaveConfigForProvidedApis Test Suite", [](auto &unit)
	{
		unit.test("IHaveConfigForProvidedApis_conceptPassedConfigWithoutApis_expectFalseIsReturned", []()
		{
			struct ConfigWithoutApis
			{
			};

			expect(IHaveConfigForProvidedApis<ConfigWithoutApis>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedApis_conceptPassedConfigWithEmptyTuple_expectTrueIsReturned", []()
		{
			struct ConfigWithEmptyApis
			{
				using ProvidedApis = std::tuple<>;
			};

			expect(IHaveConfigForProvidedApis<ConfigWithEmptyApis>, equal_to(true));
		});

		unit.test("IHaveConfigForProvidedApis_conceptPassedConfigWithSingleProvidedApi_expectTrueIsReturned", []()
		{
			struct ConfigWithSingleApi
			{
				using ProvidedApis = std::tuple<StubApiConfig<1>>;
			};

			expect(IHaveConfigForProvidedApis<ConfigWithSingleApi>, equal_to(true));
		});

		unit.test("IHaveConfigForProvidedApis_conceptPassedConfigWithSingleInvalidApi_expectFalseIsReturned", []()
		{
			struct ConfigWithSingleInvalidApi
			{
				struct NonApiConfig
				{
					struct Interface
					{
					};

					struct Type
					{
					};
				};

				using ProvidedApis = std::tuple<NonApiConfig>;
			};

			expect(IHaveConfigForProvidedApis<ConfigWithSingleInvalidApi>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedApis_conceptPassedConfigWithMultipleApis_expectTrueIsReturned", []()
		{
			struct ConfigWithMultipleApis
			{
				using ProvidedApis = std::tuple<StubApiConfig<1>, StubApiConfig<2>, StubApiConfig<3>>;
			};

			expect(IHaveConfigForProvidedApis<ConfigWithMultipleApis>, equal_to(true));
		});

		unit.test("IHaveConfigForProvidedApis_conceptPassedConfigWithMultipleApisIncludingNonApiConfig_expectFalseIsReturned", []()
		{
			struct ConfigWithInvalidApi
			{
				struct NonApiConfig
				{
					struct Interface
					{
					};

					struct Type
					{
					};
				};

				using ProvidedApis = std::tuple<StubApiConfig<1>, StubApiConfig<2>, NonApiConfig, StubApiConfig<3>>;
			};

			expect(IHaveConfigForProvidedApis<ConfigWithInvalidApi>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedApis_conceptPassedConfigWithArrayOfApis_expectFalseIsReturned", []()
		{
			struct ConfigWithArrayOfApis
			{
				using ProvidedApis = std::array<StubApiConfig<1>, 3>;
			};

			expect(IHaveConfigForProvidedApis<ConfigWithArrayOfApis>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedApis_conceptPassedConfigWithPairOfApis_expectFalseIsReturned", []()
		{
			struct ConfigWithPairOfApis
			{
				using ProvidedApis = std::pair<StubApiConfig<1>, StubApiConfig<2>>;
			};

			expect(IHaveConfigForProvidedApis<ConfigWithPairOfApis>, equal_to(false));
		});
	});
}
