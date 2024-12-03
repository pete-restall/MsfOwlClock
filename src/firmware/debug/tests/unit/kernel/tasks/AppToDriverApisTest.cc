// TODO: The AppToDriverApis class will be removed.  In its place will be AppTaskApis and KernelTaskApis, plus, in Drivers, SyscallApis, IsrApis and ApiApis.
#include <array>
#include <concepts>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/AppToDriverApis.hh"

#include "../../NonDeterminism.hh"

using namespace mettle;

using namespace smeg::kernel::tasks;

namespace smeg::tests::unit::kernel::tasks
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

	struct DummyConfig
	{
	};

	template <typename TConfig, typename TApi>
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
		auto createApi(void) const
		{
			if constexpr (std::same_as<T, TApi>)
				return this->api;
		}
	};

	template <typename TConfig, typename TApi>
	class StubFactoryReturningDifferentInstances
	{
	public:
		template <typename T>
		auto createApi(void) const
		{
			return T();
		}
	};

	suite<> appToDriverApisTest("AppToDriverApis Test Suite", [](auto &unit)
	{
		unit.test("AsTuple_get_expectTupleOfApisPassedAsClassTemplateArguments", []()
		{
			std::array assertions
			{
				std::same_as<typename AppToDriverApis<DummyRequiredApi<123>>::AsTuple, std::tuple<DummyRequiredApi<123>>>,
				std::same_as<typename AppToDriverApis<DummyRequiredApi<456>, DummyRequiredApi<789>>::AsTuple, std::tuple<DummyRequiredApi<456>, DummyRequiredApi<789>>>,
				std::same_as<typename AppToDriverApis<DummyRequiredApi<2>, DummyRequiredApi<4>, DummyRequiredApi<6>>::AsTuple, std::tuple<DummyRequiredApi<2>, DummyRequiredApi<4>, DummyRequiredApi<6>>>
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("get_called_expectApiInstanceCreatedByFactoryPassedToConstructorIsReturned", []()
		{
			StubRequiredApi apiFromFactory(anyValueOf<int>());
			StubFactory<DummyConfig, StubRequiredApi> apiFactory(apiFromFactory);
			AppToDriverApis<StubRequiredApi> apis(apiFactory);
			auto api(apis.get<StubRequiredApi>());
			expect(api.token, equal_to(apiFromFactory.token));
		});

		unit.test("get_calledMultipleTimes_expectSameApiInstanceIsReturned", []()
		{
			StubFactoryReturningDifferentInstances<DummyConfig, StubRequiredApi> apiFactory;
			AppToDriverApis<StubRequiredApi> apis(apiFactory);
			std::array apiPtrs{&apis.get<StubRequiredApi>(), &apis.get<StubRequiredApi>()};
			expect(apiPtrs[0], equal_to(apiPtrs[1]));
		});
	});
}
