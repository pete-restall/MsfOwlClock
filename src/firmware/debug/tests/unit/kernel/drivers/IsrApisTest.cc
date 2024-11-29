#include <array>
#include <concepts>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/IsrApis.hh"

#include "../../NonDeterminism.hh"

using namespace mettle;

using namespace smeg::kernel::drivers;

namespace smeg::tests::unit::kernel::drivers
{
	template <auto X>
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

	template <typename TApi>
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
		auto create(void) const
		{
			if constexpr (std::same_as<T, TApi>)
				return this->api;
		}
	};

	template <typename TApi>
	class StubFactoryReturningDifferentInstances
	{
	public:
		template <typename T>
		auto create(void) const
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

		unit.test("get_called_expectApiInstanceCreatedByFactoryPassedToConstructorIsReturned", []()
		{
			StubRequiredApi apiFromFactory(anyValueOf<int>());
			StubFactory apiFactory(apiFromFactory);
			IsrApis<StubRequiredApi> apis(apiFactory);
			auto api(apis.get<StubRequiredApi>());
			expect(api.token, equal_to(apiFromFactory.token));
		});

		unit.test("get_calledMultipleTimes_expectSameApiInstanceIsReturned", []()
		{
			StubFactoryReturningDifferentInstances<StubRequiredApi> apiFactory;
			IsrApis<StubRequiredApi> apis(apiFactory);
			std::array apiPtrs{&apis.get<StubRequiredApi>(), &apis.get<StubRequiredApi>()};
			expect(apiPtrs[0], equal_to(apiPtrs[1]));
		});
	});
}
