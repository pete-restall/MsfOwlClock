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
	static void nextTaskId_getWhenPassedConfigForSimpleTask_expectTaskIdIncrementedByOne(void)
	{
		struct SimpleTaskConfig
		{
			using Type = TTask;
		};

		expect(TaskConfigToResourceAssociation<TaskId, SimpleTaskConfig>::nextTaskId, equal_to(TaskId + 1));
	}

	template <auto TaskId>
	static void nextTaskId_getWhenPassedConfigForNoOverlaidTasks_expectSameTaskIdAsPassedToTemplate(void)
	{
		struct OverlaidTaskConfig
		{
			using Types = std::tuple<>;
		};

		expect(TaskConfigToResourceAssociation<TaskId, OverlaidTaskConfig>::nextTaskId, equal_to(TaskId));
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

		unit.test("nextTaskId_getWhenPassedConfigForSimpleTask_expectTaskIdIncrementedByOne", []()
		{
			nextTaskId_getWhenPassedConfigForSimpleTask_expectTaskIdIncrementedByOne<0, DummyTask<828129>>();
			nextTaskId_getWhenPassedConfigForSimpleTask_expectTaskIdIncrementedByOne<8, DummyTask<1253>>();
		});

/* TODO: When we allow ResourceToTaskAssociation with no associated tasks, we can uncomment this and it should compile...
		unit.test("Type_getWhenPassedConfigForNoOverlaidTasks_expectResourceToTaskAssociationOfTaskConfigToNoTaskIds", []()
		{
			struct OverlaidTaskConfig
			{
				using Types = std::tuple<>;
			};

			expect(
				typeid(typename TaskConfigToResourceAssociation<12, OverlaidTaskConfig>::Type) == typeid(ResourceToTaskAssociation<OverlaidTaskConfig>),
				equal_to(true));
		});

		unit.test("nextTaskId_getWhenPassedConfigForNoOverlaidTasks_expectSameTaskIdAsPassedToTemplate", []()
		{
			nextTaskId_getWhenPassedConfigForNoOverlaidTasks_expectSameTaskIdAsPassedToTemplate<0>();
			nextTaskId_getWhenPassedConfigForNoOverlaidTasks_expectSameTaskIdAsPassedToTemplate<91>();
			nextTaskId_getWhenPassedConfigForNoOverlaidTasks_expectSameTaskIdAsPassedToTemplate<128974>();
		});
*/
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

		unit.test("nextTaskId_getWhenPassedConfigForOverlaidTasks_expectTaskIdIncrementedByNumberOfTasks", []()
		{
			nextTaskId_getWhenPassedConfigForOverlaidTasks_expectTaskIdIncrementedByNumberOfTasks<0, DummyTask<6573>>();
			nextTaskId_getWhenPassedConfigForOverlaidTasks_expectTaskIdIncrementedByNumberOfTasks<91, DummyTask<912674>, DummyTask<912674>>();
			nextTaskId_getWhenPassedConfigForOverlaidTasks_expectTaskIdIncrementedByNumberOfTasks<128974, DummyTask<2>, DummyTask<4>, DummyTask<6>>();
		});
	});
}
