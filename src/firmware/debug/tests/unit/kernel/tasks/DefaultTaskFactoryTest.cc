#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/AppTaskApis.hh"
#include "kernel/tasks/DefaultTaskFactory.hh"

#include "../../NonDeterminism.hh"
#include "TaskTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel::tasks;

namespace smeg::tests::unit::kernel::tasks
{
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

	template <template <typename...> typename TApis>
	struct Stub
	{
		using Apis = TApis<StubRequiredApi>;
	};

	template <typename... TRequiredApis>
	struct DummyApiFactory
	{
		template <typename T>
		constexpr auto createApi(void) const;
	};

	template <typename TRequiredApis>
	struct SpyTaskWithRequiredApisConstructor
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		RequiredApis apis;

		SpyTaskWithRequiredApisConstructor(RequiredApis apis) :
			apis(apis)
		{
		}

		void run(void)
		{
		}
	};

	template <typename... TRequiredApis>
	struct StubApiFactory
	{
		template <typename T>
		constexpr auto createApi(void) const
		{
			if constexpr (std::same_as<T, StubRequiredApi>)
				return StubRequiredApi(token);
			else
				throw std::runtime_error("StubApiFactory.create<T>() is only stubbed for T=StubRequiredApi");
		}

		static thread_local inline int token = anyValueOf<int>();
	};

	template <typename... TApis>
	class StubTaskApis
	{
	private:
		std::tuple<TApis...> apis;

	public:
		using AsTuple = decltype(apis);

		template <typename TConfig, template <typename, typename...> typename TApiFactory>
		StubTaskApis(TApiFactory<TConfig, TApis...> apiFactory) :
			apis(apiFactory.template createApi<TApis>() ...)
		{
		}

		template <typename TApi>
		auto &get(void)
		{
			return std::get<TApi>(this->apis);
		}
	};

	suite<Stub<AppTaskApis>, Stub<StubTaskApis>> defaultTaskFactoryTest("DefaultTaskFactory Test Suite", [](auto &unit)
	{
		unit.test("createTask_calledWhenTaskHasNoRequiredApisAndHasDefaultConstructor_expectTaskCanBeCreated", [](auto)
		{
			auto task(DefaultTaskFactory<StubTaskWithDefaultConstructor, DummyApiFactory>::createTask());
			auto isTaskExpectedType(typeid(task) == typeid(StubTaskWithDefaultConstructor));
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasRequiredApisAndHasMatchingConstructor_expectTaskIsCreatedWithApisFromFactory", [](auto fixture)
		{
			using SpyTask = SpyTaskWithRequiredApisConstructor<typename decltype(fixture)::Apis>;
			auto task(DefaultTaskFactory<SpyTask, StubApiFactory>::createTask());
			auto resolvedApi(task.apis.template get<StubRequiredApi>());
			expect(resolvedApi.token, equal_to(StubApiFactory<SpyTask, StubRequiredApi>::token));
		});

		unit.test("createTask_called_expectSameInstanceOfApiIsReturnedForEachGet", [](auto fixture)
		{
			using SpyTask = SpyTaskWithRequiredApisConstructor<typename decltype(fixture)::Apis>;
			auto task(DefaultTaskFactory<SpyTask, StubApiFactory>::createTask());
			std::array resolvedApiPtrs{&task.apis.template get<StubRequiredApi>(), &task.apis.template get<StubRequiredApi>()};
			expect(resolvedApiPtrs[0], equal_to(resolvedApiPtrs[1]));
		});
	});
}
