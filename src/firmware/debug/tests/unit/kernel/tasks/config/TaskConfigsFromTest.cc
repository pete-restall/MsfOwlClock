#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/config/ResourceToTaskAssociation.hh"
#include "kernel/tasks/config/TaskConfigsFrom.hh"

#include "DummyTask.hh"

using namespace mettle;

using namespace smeg::kernel::tasks::config;

namespace smeg::tests::unit::kernel::tasks::config
{
	suite<> taskConfigsFromTest("TaskConfigsFrom Test Suite", [](auto &unit)
	{
		struct EmptyConfig
		{
			using Tasks = std::tuple<>;
		};

		struct ConfigWithMixOfSimpleAndOverlaidTasks
		{
			struct TaskConfig1
			{
				using Types = std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>>;
			};

			struct TaskConfig2
			{
				using Type = DummyTask<4>;
			};

			struct TaskConfig3
			{
				using Types = std::tuple<DummyTask<5>>;
			};

			struct TaskConfig4
			{
				using Type = DummyTask<6>;
			};

			struct TaskConfig5
			{
				using Types = std::tuple<DummyTask<7>, DummyTask<8>>;
			};

			using Tasks = std::tuple<TaskConfig1, TaskConfig2, TaskConfig3, TaskConfig4, TaskConfig5>;
		};

		unit.test("PerConfig_getWhenPassedConfigWithEmptyTasks_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<typename TaskConfigsFrom<EmptyConfig>::PerConfig>, equal_to(0));
		});

		unit.test("PerConfig_getWhenPassedConfigWithSingleSimpleTask_expectSameConfig", []()
		{
			struct Config
			{
				struct SimpleTask
				{
					using Type = DummyTask<99>;
				};

				using Tasks = std::tuple<SimpleTask>;
			};

			expect(
				typeid(typename TaskConfigsFrom<Config>::PerConfig) == typeid(std::tuple<ResourceToTaskAssociation<typename Config::SimpleTask, 0>>),
				equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedConfigWithMultipleSimpleTasks_expectConfigForEachTaskId", []()
		{
			struct Config
			{
				struct SimpleTask
				{
					using Type = DummyTask<23>;
				};

				struct AnotherSimpleTask
				{
					using Type = DummyTask<867>;
				};

				using Tasks = std::tuple<SimpleTask, AnotherSimpleTask, SimpleTask>;
			};

			expect(
				typeid(typename TaskConfigsFrom<Config>::PerConfig) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::SimpleTask, 0>,
					ResourceToTaskAssociation<typename Config::AnotherSimpleTask, 1>,
					ResourceToTaskAssociation<typename Config::SimpleTask, 2>>),
				equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedConfigWithSingleOverlaidTask_expectSameConfigWithSingleTaskId", []()
		{
			struct Config
			{
				struct SingleOverlaidTask
				{
					using Types = std::tuple<DummyTask<6>>;
				};

				using Tasks = std::tuple<SingleOverlaidTask>;
			};

			expect(
				typeid(typename TaskConfigsFrom<Config>::PerConfig) == typeid(std::tuple<ResourceToTaskAssociation<typename Config::SingleOverlaidTask, 0>>),
				equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedConfigWithSingleOverlaidTasks_expectSameConfigWithEachTaskId", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(
				typeid(typename TaskConfigsFrom<Config>::PerConfig) == typeid(std::tuple<ResourceToTaskAssociation<typename Config::OverlaidTasks, 0, 1, 2>>),
				equal_to(true));
		});

		unit.test("PerConfig_getWhenPassedConfigWithMixOfSimpleAndOverlaidTasks_expectConfigsCorrespondingToEachTaskId", []()
		{
			using Config = ConfigWithMixOfSimpleAndOverlaidTasks;
			expect(
				typeid(typename TaskConfigsFrom<Config>::PerConfig) == typeid(std::tuple<
					ResourceToTaskAssociation<typename ConfigWithMixOfSimpleAndOverlaidTasks::TaskConfig1, 0, 1, 2>,
					ResourceToTaskAssociation<typename Config::TaskConfig2, 3>,
					ResourceToTaskAssociation<typename Config::TaskConfig3, 4>,
					ResourceToTaskAssociation<typename Config::TaskConfig4, 5>,
					ResourceToTaskAssociation<typename Config::TaskConfig5, 6, 7>>),
				equal_to(true));
		});

		unit.test("PerTask_getWhenPassedConfigWithEmptyTasks_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<typename TaskConfigsFrom<EmptyConfig>::PerTask>, equal_to(0));
		});

		unit.test("PerTask_getWhenPassedConfigWithSingleSimpleTask_expectSameConfig", []()
		{
			struct Config
			{
				struct SimpleTask
				{
					using Type = DummyTask<99>;
				};

				using Tasks = std::tuple<SimpleTask>;
			};

			expect(
				typeid(typename TaskConfigsFrom<Config>::PerTask) == typeid(std::tuple<ResourceToTaskAssociation<typename Config::SimpleTask, 0>>),
				equal_to(true));
		});

		unit.test("PerTask_getWhenPassedConfigWithMultipleSimpleTasks_expectConfigForEachTaskId", []()
		{
			struct Config
			{
				struct SimpleTask
				{
					using Type = DummyTask<99>;
				};

				struct AnotherSimpleTask
				{
					using Type = DummyTask<14>;
				};

				using Tasks = std::tuple<SimpleTask, SimpleTask, AnotherSimpleTask>;
			};

			expect(
				typeid(typename TaskConfigsFrom<Config>::PerTask) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::SimpleTask, 0>,
					ResourceToTaskAssociation<typename Config::SimpleTask, 1>,
					ResourceToTaskAssociation<typename Config::AnotherSimpleTask, 2>>),
				equal_to(true));
		});

		unit.test("PerTask_getWhenPassedConfigWithSingleOverlaidTask_expectSameConfigRepeatedOnce", []()
		{
			struct Config
			{
				struct SingleOverlaidTask
				{
					using Types = std::tuple<DummyTask<1>>;
				};

				using Tasks = std::tuple<SingleOverlaidTask>;
			};

			expect(
				typeid(typename TaskConfigsFrom<Config>::PerTask) == typeid(std::tuple<ResourceToTaskAssociation<typename Config::SingleOverlaidTask, 0>>),
				equal_to(true));
		});

		unit.test("PerTask_getWhenPassedConfigWithSingleOverlaidTasks_expectSameConfigRepeatedForEachOverlaidTask", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<4>, DummyTask<3>, DummyTask<2>>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(
				typeid(typename TaskConfigsFrom<Config>::PerTask) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::OverlaidTasks, 0>,
					ResourceToTaskAssociation<typename Config::OverlaidTasks, 1>,
					ResourceToTaskAssociation<typename Config::OverlaidTasks, 2>>),
				equal_to(true));
		});

		unit.test("PerTask_getWhenPassedConfigWithMixOfSimpleAndOverlaidTasks_expectConfigsCorrespondingToEachTaskId", []()
		{
			using Config = ConfigWithMixOfSimpleAndOverlaidTasks;
			expect(
				typeid(typename TaskConfigsFrom<Config>::PerTask) == typeid(std::tuple<
					ResourceToTaskAssociation<typename Config::TaskConfig1, 0>,
					ResourceToTaskAssociation<typename Config::TaskConfig1, 1>,
					ResourceToTaskAssociation<typename Config::TaskConfig1, 2>,
					ResourceToTaskAssociation<typename Config::TaskConfig2, 3>,
					ResourceToTaskAssociation<typename Config::TaskConfig3, 4>,
					ResourceToTaskAssociation<typename Config::TaskConfig4, 5>,
					ResourceToTaskAssociation<typename Config::TaskConfig5, 6>,
					ResourceToTaskAssociation<typename Config::TaskConfig5, 7>>),
				equal_to(true));
		});
	});
}
