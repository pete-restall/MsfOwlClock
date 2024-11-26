#include <concepts>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IProvidedApiConfig.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct DummyApi
	{
	};

	struct StubApi
	{
	};

	template <typename... T>
	struct DummyApiInterface
	{
	};

	template <typename T>
	concept IInterfaceApi = std::same_as<T, StubApi>;

	template <IInterfaceApi... T>
	struct StubApiInterface
	{
	};

	struct ValidApiConfig
	{
		template <typename... T>
		using Interface = DummyApiInterface<T...>;

		using Type = DummyApi;
	};

	template <typename TNonClassType>
	struct ApiConfigWithNonClassType
	{
		template <typename... T>
		using Interface = DummyApiInterface<T...>;

		using Type = TNonClassType;
	};

	struct ApiConfigWithoutType
	{
		template <typename... T>
		using Interface = DummyApiInterface<T...>;
	};

	struct ApiConfigWithApiNotConformingToInterface
	{
		template <typename... T>
		using Interface = StubApiInterface<T...>;

		using Type = DummyApi;
	};

	suite<> iprovidedApiConfigTest("IProvidedApiConfig Test Suite", [](auto &unit)
	{
		unit.test("IProvidedApiConfig_conceptPassedValidApiConfig_expectTrueIsReturned", []()
		{
			expect(IProvidedApiConfig<ValidApiConfig>, equal_to(true));
		});

		unit.test("IProvidedApiConfig_conceptPassedApiConfigWithoutInterface_expectFalseIsReturned", []()
		{
			struct ApiConfigWithoutInterface
			{
				using Type = DummyApi;
			};

			expect(IProvidedApiConfig<ApiConfigWithoutInterface>, equal_to(false));
		});

		unit.test("IProvidedApiConfig_conceptPassedApiConfigWitNonInterface_expectFalseIsReturned", []()
		{
			struct ApiConfigWithNonInterface
			{
				struct Interface
				{
				};

				using Type = DummyApi;
			};

			expect(IProvidedApiConfig<ApiConfigWithNonInterface>, equal_to(false));
		});

		unit.test("IProvidedApiConfig_conceptPassedApiConfigWithNonClassType_expectFalseIsReturned", []()
		{
			expect(IProvidedApiConfig<ApiConfigWithNonClassType<double>>, equal_to(false));
			expect(IProvidedApiConfig<ApiConfigWithNonClassType<int>>, equal_to(false));
			expect(IProvidedApiConfig<ApiConfigWithNonClassType<bool>>, equal_to(false));
		});

		unit.test("IProvidedApiConfig_conceptPassedApiConfigWithoutType_expectFalseIsReturned", []()
		{
			expect(IProvidedApiConfig<ApiConfigWithoutType>, equal_to(false));
		});

		unit.test("IProvidedApiConfig_conceptPassedApiConfigWithoutTypeNotConformingToInterface_expectFalseIsReturned", []()
		{
			expect(IProvidedApiConfig<ApiConfigWithApiNotConformingToInterface>, equal_to(false));
		});
	});
}
