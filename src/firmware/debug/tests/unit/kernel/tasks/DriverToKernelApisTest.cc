#include <concepts>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/DriverToKernelApis.hh"

#include "../../NonDeterminism.hh"
#include "TaskTestDoubles.hh"

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

	suite<> driverToKernelApisTest("DriverToKernelApis Test Suite", [](auto &unit)
	{
		unit.test("AsTuple_get_expectTupleOfApisPassedAsClassTemplateArguments", []()
		{
			std::array assertions
			{
				typeid(typename DriverToKernelApis<DummyRequiredApi<1>>::AsTuple) == typeid(std::tuple<DummyRequiredApi<1>>),
				typeid(typename DriverToKernelApis<DummyRequiredApi<2>, DummyRequiredApi<3>>::AsTuple) == typeid(std::tuple<DummyRequiredApi<2>, DummyRequiredApi<3>>),
				typeid(typename DriverToKernelApis<DummyRequiredApi<4>, DummyRequiredApi<5>, DummyRequiredApi<6>>::AsTuple) == typeid(std::tuple<DummyRequiredApi<4>, DummyRequiredApi<5>, DummyRequiredApi<6>>)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("get_called_expectApiInstanceCreatedByFactoryPassedToConstructorIsReturned", []()
		{
			StubRequiredApi apiFromFactory(anyValueOf<int>());
			StubFactory apiFactory(apiFromFactory);
			DriverToKernelApis<StubRequiredApi> apis(apiFactory);
			auto api(apis.get<StubRequiredApi>());
			expect(api.token, equal_to(apiFromFactory.token));
		});

		unit.test("get_calledMultipleTimes_expectSameApiInstanceIsReturned", []()
		{
			StubFactoryReturningDifferentInstances<StubRequiredApi> apiFactory;
			DriverToKernelApis<StubRequiredApi> apis(apiFactory);
			std::array apiPtrs{&apis.get<StubRequiredApi>(), &apis.get<StubRequiredApi>()};
			expect(apiPtrs[0], equal_to(apiPtrs[1]));
		});
	});
}
