#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/config/TaskConfigToResourceAssociation.hh"
#include "kernel/tasks/config/dsl/DefaultTaskStack.hh"

#include "DummyTask.hh"

using namespace mettle;

using namespace smeg::kernel::tasks::config;

namespace smeg::tests::unit::kernel::tasks::config
{
	template <auto TaskId, typename TTask>
	static void Type_getWhenPassedConfigForSimpleTask_expectResourceToTaskAssociationOfTaskConfigToTaskId(void)
	{
		struct SimpleTaskConfig
		{
			using Type = TTask;
		};

		expect(
			typeid(typename TaskConfigToResourceAssociation<TaskId, SimpleTaskConfig>::Type) == typeid(ResourceToTaskAssociation<SimpleTaskConfig, TaskId>),
			equal_to(true));
	}

	template <auto TaskId, typename TTask>
	static void numberOfTasks_getWhenPassedConfigForSimpleTask_expectOne(void)
	{
		struct SimpleTaskConfig
		{
			using Type = TTask;
		};

		expect(TaskConfigToResourceAssociation<TaskId, SimpleTaskConfig>::numberOfTasks, equal_to(1));
	}

	template <auto TaskId, typename TTask>
	static void nextTaskId_getWhenPassedConfigForSimpleTask_expectTaskIdIncrementedByOne(void)
	{
		struct SimpleTaskConfig
		{
			using Type = TTask;
		};

		expect(TaskConfigToResourceAssociation<TaskId, SimpleTaskConfig>::nextTaskId, equal_to(TaskId + 1));
	}

	template <auto FirstTaskId, typename... TTasks>
	static void numberOfTasks_getWhenPassedConfigForOverlaidTasks_expectSameNumberOfTasksAsOverlay(void)
	{
		struct OverlaidTaskConfig
		{
			using Types = std::tuple<TTasks...>;
		};

		expect(TaskConfigToResourceAssociation<FirstTaskId, OverlaidTaskConfig>::numberOfTasks, equal_to(sizeof...(TTasks)));
	}

	template <auto FirstTaskId, typename... TTasks>
	static void nextTaskId_getWhenPassedConfigForOverlaidTasks_expectTaskIdIncrementedByNumberOfTasks(void)
	{
		struct OverlaidTaskConfig
		{
			using Types = std::tuple<TTasks...>;
		};

		expect(TaskConfigToResourceAssociation<FirstTaskId, OverlaidTaskConfig>::nextTaskId, equal_to(FirstTaskId + sizeof...(TTasks)));
	}

	suite<> taskConfigToResourceAssociationTest("TaskConfigToResourceAssociation Test Suite", [](auto &unit)
	{
		unit.test("Type_getWhenPassedConfigForSimpleTask_expectResourceToTaskAssociationOfTaskConfigToTaskId", []()
		{
			Type_getWhenPassedConfigForSimpleTask_expectResourceToTaskAssociationOfTaskConfigToTaskId<123, DummyTask<456>>();
			Type_getWhenPassedConfigForSimpleTask_expectResourceToTaskAssociationOfTaskConfigToTaskId<0, DummyTask<1>>();
		});

		unit.test("numberOfTasks_getWhenPassedConfigForSimpleTask_expectOne", []()
		{
			numberOfTasks_getWhenPassedConfigForSimpleTask_expectOne<0, DummyTask<15633>>();
			numberOfTasks_getWhenPassedConfigForSimpleTask_expectOne<8, DummyTask<5>>();
		});

		unit.test("nextTaskId_getWhenPassedConfigForSimpleTask_expectTaskIdIncrementedByOne", []()
		{
			nextTaskId_getWhenPassedConfigForSimpleTask_expectTaskIdIncrementedByOne<0, DummyTask<828129>>();
			nextTaskId_getWhenPassedConfigForSimpleTask_expectTaskIdIncrementedByOne<8, DummyTask<1253>>();
		});

		unit.test("Type_getWhenPassedConfigForOverlaidTasks_expectResourceToTaskAssociationOfTaskConfigToIncrementingTaskId", []()
		{
			struct OverlaidTaskConfig
			{
				using Types = std::tuple<DummyTask<1>, DummyTask<1>, DummyTask<2>, DummyTask<3>, DummyTask<5>, DummyTask<8>>;
			};

			expect(
				typeid(typename TaskConfigToResourceAssociation<18912, OverlaidTaskConfig>::Type) ==
					typeid(ResourceToTaskAssociation<OverlaidTaskConfig, 18912, 18913, 18914, 18915, 18916, 18917>),
				equal_to(true));
		});

		unit.test("numberOfTasks_getWhenPassedConfigForOverlaidTasks_expectSameNumberOfTasksAsOverlay", []()
		{
			numberOfTasks_getWhenPassedConfigForOverlaidTasks_expectSameNumberOfTasksAsOverlay<0, DummyTask<2>>();
			numberOfTasks_getWhenPassedConfigForOverlaidTasks_expectSameNumberOfTasksAsOverlay<7, DummyTask<2345>, DummyTask<8075>>();
			numberOfTasks_getWhenPassedConfigForOverlaidTasks_expectSameNumberOfTasksAsOverlay<34, DummyTask<2>, DummyTask<4>, DummyTask<6>>();
		});

		unit.test("nextTaskId_getWhenPassedConfigForOverlaidTasks_expectTaskIdIncrementedByNumberOfTasks", []()
		{
			nextTaskId_getWhenPassedConfigForOverlaidTasks_expectTaskIdIncrementedByNumberOfTasks<0, DummyTask<6573>>();
			nextTaskId_getWhenPassedConfigForOverlaidTasks_expectTaskIdIncrementedByNumberOfTasks<91, DummyTask<912674>, DummyTask<912674>>();
			nextTaskId_getWhenPassedConfigForOverlaidTasks_expectTaskIdIncrementedByNumberOfTasks<128974, DummyTask<2>, DummyTask<4>, DummyTask<6>>();
		});
	});
}
