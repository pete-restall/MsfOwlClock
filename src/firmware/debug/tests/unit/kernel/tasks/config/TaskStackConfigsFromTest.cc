#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/config/ResourceToTaskAssociation.hh"
#include "kernel/tasks/config/TaskStackConfigsFrom.hh"

#include "DummyTask.hh"

using namespace mettle;

using namespace smeg::kernel::tasks::config;

namespace smeg::tests::unit::kernel::tasks::config
{
	template <auto N>
	struct DummyTaskStack
	{
	};

	suite<> taskStackConfigsFromTest("TaskStackConfigsFrom Test Suite", [](auto &unit)
	{
		unit.test("PerStack_getWhenPassedConfigWithEmptyTasks_expectEmptyTuple", []()
		{
			struct EmptyConfig
			{
				using Tasks = std::tuple<>;
			};

			expect(std::tuple_size_v<typename TaskStackConfigsFrom<EmptyConfig>::PerStack>, equal_to(0));
		});

		unit.test("PerStack_getWhenPassedConfigWithSingleSimpleTask_expectStackConfigIsAssociatedWithFirstTask", []()
		{
			struct Config
			{
				struct LonelyTask
				{
					using Type = DummyTask<1>;
					using Stack = DummyTaskStack<42>;
				};

				using Tasks = std::tuple<LonelyTask>;
			};

			expect(
				typeid(typename TaskStackConfigsFrom<Config>::PerStack) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::LonelyTask::Stack, 0>>),
				equal_to(true));
		});

		unit.test("PerStack_getWhenPassedConfigWithMultipleSimpleTasksWithSameStackTypes_expectStackConfigsAreAssociatedWithTheirCorrespondingTask", []()
		{
			struct Config
			{
				struct FirstTask
				{
					using Type = DummyTask<2>;
					using Stack = DummyTaskStack<7>;
				};

				struct SecondTask
				{
					using Type = DummyTask<3>;
					using Stack = DummyTaskStack<7>;
				};

				using Tasks = std::tuple<FirstTask, SecondTask>;
			};

			expect(
				typeid(typename TaskStackConfigsFrom<Config>::PerStack) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::FirstTask::Stack, 0>,
					ResourceToTaskAssociation<typename Config::SecondTask::Stack, 1>>),
				equal_to(true));
		});

		unit.test("PerStack_getWhenPassedConfigWithMultipleSimpleTasksWithDifferentStackTypes_expectStackConfigsAreAssociatedWithTheirCorrespondingTask", []()
		{
			struct Config
			{
				struct FirstTask
				{
					using Type = DummyTask<356>;
					using Stack = DummyTaskStack<32>;
				};

				struct SecondTask
				{
					using Type = DummyTask<91>;
					using Stack = DummyTaskStack<19>;
				};

				using Tasks = std::tuple<FirstTask, SecondTask>;
			};

			expect(
				typeid(typename TaskStackConfigsFrom<Config>::PerStack) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::FirstTask::Stack, 0>,
					ResourceToTaskAssociation<typename Config::SecondTask::Stack, 1>>),
				equal_to(true));
		});

		unit.test("PerStack_getWhenPassedConfigWithSingleOverlayTask_expectStackConfigIsAssociatedWithAllTasksInOverlay", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<7>, DummyTask<5>, DummyTask<13>>;
					using Stack = DummyTaskStack<12>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(
				typeid(typename TaskStackConfigsFrom<Config>::PerStack) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::OverlaidTasks::Stack, 0, 1, 2>>),
				equal_to(true));
		});

		unit.test("PerStack_getWhenPassedConfigWithMultipleOverlayTasksOfSameType_expectStackConfigsAreAssociatedWithEachOverlay", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<7>, DummyTask<5>, DummyTask<13>>;
					using Stack = DummyTaskStack<12>;
				};

				using Tasks = std::tuple<OverlaidTasks, OverlaidTasks>;
			};

			expect(
				typeid(typename TaskStackConfigsFrom<Config>::PerStack) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::OverlaidTasks::Stack, 0, 1, 2>,
					ResourceToTaskAssociation<typename Config::OverlaidTasks::Stack, 3, 4, 5>>),
				equal_to(true));
		});

		unit.test("PerStack_getWhenPassedConfigWithMultipleOverlayTasksOfDifferentTypes_expectStackConfigsAreAssociatedWithEachTaskInEachOverlay", []()
		{
			struct Config
			{
				struct FirstOverlaidTasks
				{
					using Types = std::tuple<DummyTask<7>, DummyTask<5>, DummyTask<13>>;
					using Stack = DummyTaskStack<12>;
				};

				struct SecondOverlaidTasks
				{
					using Types = std::tuple<DummyTask<11>, DummyTask<12>>;
					using Stack = DummyTaskStack<16>;
				};

				using Tasks = std::tuple<FirstOverlaidTasks, SecondOverlaidTasks>;
			};

			expect(
				typeid(typename TaskStackConfigsFrom<Config>::PerStack) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::FirstOverlaidTasks::Stack, 0, 1, 2>,
					ResourceToTaskAssociation<typename Config::SecondOverlaidTasks::Stack, 3, 4>>),
				equal_to(true));
		});

		unit.test("PerStack_getWhenPassedConfigWithMixOfOverlayAndSimpleTasks_expectStackConfigsAreAssociatedWithEachTask", []()
		{
			struct Config
			{
				struct FirstOverlaidTasks
				{
					using Types = std::tuple<DummyTask<7>, DummyTask<5>, DummyTask<13>, DummyTask<9183>>;
					using Stack = DummyTaskStack<12>;
				};

				struct FirstSimpleTask
				{
					using Type = DummyTask<7>;
					using Stack = DummyTaskStack<12>;
				};

				struct SecondOverlaidTasks
				{
					using Types = std::tuple<DummyTask<11>, DummyTask<12>>;
					using Stack = DummyTaskStack<16>;
				};

				struct SecondSimpleTask
				{
					using Type = DummyTask<77>;
					using Stack = DummyTaskStack<16>;
				};

				using Tasks = std::tuple<FirstOverlaidTasks, FirstSimpleTask, SecondOverlaidTasks, SecondSimpleTask>;
			};

			expect(
				typeid(typename TaskStackConfigsFrom<Config>::PerStack) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::FirstOverlaidTasks::Stack, 0, 1, 2, 3>,
					ResourceToTaskAssociation<typename Config::FirstSimpleTask::Stack, 4>,
					ResourceToTaskAssociation<typename Config::SecondOverlaidTasks::Stack, 5, 6>,
					ResourceToTaskAssociation<typename Config::SecondSimpleTask::Stack, 7>>),
				equal_to(true));
		});
	});
}
