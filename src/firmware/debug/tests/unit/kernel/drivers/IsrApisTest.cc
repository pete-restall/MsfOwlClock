#include <array>
#include <concepts>
#include <cstddef>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/IsrApis.hh"

#include "../../NonDeterminism.hh"

using namespace mettle;

using namespace smeg::kernel::drivers;

namespace smeg::tests::unit::kernel::drivers
{
	template <auto>
	struct DummyRequiredApi
	{
	};

	struct StubRequiredApi
	{
		const int token;

		StubRequiredApi(void) :
			token(0)
		{
		}

		StubRequiredApi(int token) :
			token(token)
		{
		}
	};

	struct DummyConfig
	{
	};

	template <typename, std::size_t, typename...>
	struct DummyFactory
	{
		template <typename T>
		auto createApi(void) const noexcept
		{
			return T();
		}
	};

	template <typename, std::size_t, typename TApi>
	class StubFactory
	{
	private:
		TApi &api;

	public:
		StubFactory(TApi &api) :
			api(api)
		{
		}

		template <typename T>
		auto createApi(void) const noexcept
		{
			if constexpr (std::same_as<T, TApi>)
				return this->api;
		}
	};

	template <typename, std::size_t, typename...>
	class StubFactoryReturningDifferentInstances
	{
	public:
		template <typename T>
		auto createApi(void) const noexcept
		{
			return T();
		}
	};

	suite<> isrApisTest("IsrApis Test Suite", [](auto &unit)
	{
		unit.test("AsTuple_get_expectTupleOfApisPassedAsClassTemplateArguments", []()
		{
			std::array assertions
			{
				std::same_as<typename IsrApis<DummyRequiredApi<1>>::AsTuple, std::tuple<DummyRequiredApi<1>>>,
				std::same_as<typename IsrApis<DummyRequiredApi<2>, DummyRequiredApi<3>>::AsTuple, std::tuple<DummyRequiredApi<2>, DummyRequiredApi<3>>>,
				std::same_as<typename IsrApis<DummyRequiredApi<4>, DummyRequiredApi<5>, DummyRequiredApi<6>>::AsTuple, std::tuple<DummyRequiredApi<4>, DummyRequiredApi<5>, DummyRequiredApi<6>>>
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("constructor_testedForExceptions_expectQualifiedWithNoexcept", []()
		{
			using Apis = IsrApis<DummyRequiredApi<-1>>;
			using DummyFactory = DummyFactory<DummyConfig, 2, DummyRequiredApi<-1>>;
			expect(noexcept(Apis(DummyFactory())), equal_to(true));
		});

		unit.test("get_called_expectApiInstanceCreatedByFactoryPassedToConstructorIsReturned", []()
		{
			constexpr std::size_t mcuCoreId = 3;
			StubRequiredApi apiFromFactory(anyValueOf<int>());
			StubFactory<DummyConfig, mcuCoreId, StubRequiredApi> apiFactory(apiFromFactory);
			IsrApis<StubRequiredApi> apis(apiFactory);
			auto api(apis.get<StubRequiredApi>());
			expect(api.token, equal_to(apiFromFactory.token));
		});

		unit.test("get_calledMultipleTimes_expectSameApiInstanceIsReturned", []()
		{
			constexpr std::size_t mcuCoreId = 1;
			StubFactoryReturningDifferentInstances<DummyConfig, mcuCoreId, StubRequiredApi> apiFactory;
			IsrApis<StubRequiredApi> apis(apiFactory);
			std::array apiPtrs{&apis.get<StubRequiredApi>(), &apis.get<StubRequiredApi>()};
			expect(apiPtrs[0], equal_to(apiPtrs[1]));
		});
	});
}
