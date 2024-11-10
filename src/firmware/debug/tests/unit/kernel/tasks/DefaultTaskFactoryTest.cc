#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/DefaultTaskFactory.hh"

#include "../../NonDeterminism.hh"
#include "TaskTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel::tasks;

namespace smeg::tests::unit::kernel::tasks
{
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

	template <template <typename...> typename TApis>
	struct Dummy
	{
		using Apis = TApis<DummyRequiredApi>;
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
		constexpr auto create(void) const;
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

	template <typename TRequiredApis>
	struct SpyTaskWithBothDefaultAndRequiredApisConstructors
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		RequiredApis apis;

		SpyTaskWithBothDefaultAndRequiredApisConstructors(RequiredApis apis) :
			apis(apis)
		{
		}

		SpyTaskWithBothDefaultAndRequiredApisConstructors(void)
		{
			throw std::runtime_error("Expected SpyTask to be created with APIs, not via the default constructor");
		}

		void run(void)
		{
		}
	};

	template <typename... TRequiredApis>
	struct StubApiFactory
	{
		template <typename T>
		constexpr auto create(void) const
		{
			if constexpr (std::same_as<T, StubRequiredApi>)
				return StubRequiredApi(token);
			else
				throw std::runtime_error("StubApiFactory.create<T>() is only stubbed for T=StubRequiredApi");
		}

		static thread_local int token;
	};

	template <typename... TRequiredApis>
	thread_local int StubApiFactory<TRequiredApis...>::token(anyValueOf<int>());

	suite<Stub<AppToDriverApis>, Stub<DriverToDriverApis>, Stub<DriverToKernelApis>> defaultTaskFactoryTest("DefaultTaskFactory (Default API Factory) Test Suite", [](auto &unit)
	{
		unit.test("createTask_calledWhenTaskHasNoRequiredApisAndHasDefaultConstructor_expectTaskCanBeCreated", [](auto)
		{
			auto task(DefaultTaskFactory<StubTaskWithDefaultConstructor>::createTask());
			auto isTaskExpectedType(typeid(task) == typeid(StubTaskWithDefaultConstructor));
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasRequiredApisButOnlyHasDefaultConstructor_expectTaskCanBeCreated", [](auto fixture)
		{
			using StubTask = StubTaskWithRequiredApisAndDefaultConstructor<typename decltype(fixture)::Apis>;
			auto task(DefaultTaskFactory<StubTask>::createTask());
			auto isTaskExpectedType(typeid(task) == typeid(StubTask));
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasRequiredApisAndHasMatchingConstructor_expectTaskCanBeCreated", [](auto fixture)
		{
			using StubTask = StubTaskWithRequiredApisConstructor<typename decltype(fixture)::Apis>;
			auto task(DefaultTaskFactory<StubTask>::createTask());
			auto isTaskExpectedType(typeid(task) == typeid(StubTask));
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasBothDefaultAndRequiredApisConstructors_expectTaskIsCreatedWithRequiredApis", [](auto fixture)
		{
			using MockTask = MockTaskWithBothDefaultAndRequiredApisConstructors<typename decltype(fixture)::Apis>;
			auto task(DefaultTaskFactory<MockTask>::createTask());
			expect(task.wasRequiredApisConstructorCalled, equal_to(true));
		});

		unit.test("createTask_called_expectSameInstanceOfApiIsReturnedForEachGet", [](auto fixture)
		{
			using SpyTask = SpyTaskWithRequiredApisConstructor<typename decltype(fixture)::Apis>;
			auto task(DefaultTaskFactory<SpyTask>::createTask());
			std::array resolvedApiPtrs{&task.apis.template get<StubRequiredApi>(), &task.apis.template get<StubRequiredApi>()};
			expect(resolvedApiPtrs[0], equal_to(resolvedApiPtrs[1]));
		});
	});

	suite<Stub<AppToDriverApis>, Stub<DriverToDriverApis>, Stub<DriverToKernelApis>> defaultTaskFactoryWithSpecifiedApiFactoryTest("DefaultTaskFactory (Specified API Factory) Test Suite", [](auto &unit)
	{
		unit.test("createTask_calledWhenTaskHasNoRequiredApisAndHasDefaultConstructor_expectTaskCanBeCreated", [](auto)
		{
			auto task(DefaultTaskFactory<StubTaskWithDefaultConstructor, DummyApiFactory>::createTask());
			auto isTaskExpectedType(typeid(task) == typeid(StubTaskWithDefaultConstructor));
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasRequiredApisButOnlyHasDefaultConstructor_expectTaskCanBeCreated", [](auto fixture)
		{
			using StubTask = StubTaskWithRequiredApisAndDefaultConstructor<typename decltype(fixture)::Apis>;
			auto task(DefaultTaskFactory<StubTask, DummyApiFactory>::createTask());
			auto isTaskExpectedType(typeid(task) == typeid(StubTask));
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasRequiredApisAndHasMatchingConstructor_expectTaskIsCreatedWithApisFromFactory", [](auto fixture)
		{
			using SpyTask = SpyTaskWithRequiredApisConstructor<typename decltype(fixture)::Apis>;
			auto task(DefaultTaskFactory<SpyTask, StubApiFactory>::createTask());
			auto resolvedApi(task.apis.template get<StubRequiredApi>());
			expect(resolvedApi.token, equal_to(StubApiFactory<StubRequiredApi>::token));
		});

		unit.test("createTask_calledWhenTaskHasBothDefaultAndRequiredApisConstructors_expectTaskIsCreatedWithApisFromFactory", [](auto fixture)
		{
			using SpyTask = SpyTaskWithBothDefaultAndRequiredApisConstructors<typename decltype(fixture)::Apis>;
			auto task(DefaultTaskFactory<SpyTask, StubApiFactory>::createTask());
			auto resolvedApi(task.apis.template get<StubRequiredApi>());
			expect(resolvedApi.token, equal_to(StubApiFactory<StubRequiredApi>::token));
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
