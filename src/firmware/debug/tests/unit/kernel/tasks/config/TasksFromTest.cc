#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/config/TasksFrom.hh"
#include "kernel/tasks/config/dsl/DefaultTaskStack.hh"

using namespace mettle;

using namespace smeg::kernel::tasks::config;

namespace smeg::tests::unit::kernel::tasks::config
{
	template <auto T>
	struct DummyTask
	{
		DummyTask(void)
		{
		}

		void run(void)
		{
		}
	};

	suite<> tasksFromTest("TasksFrom Test Suite", [](auto &unit)
	{
		unit.test("Types_getWhenPassedConfigWithEmptyTasks_expectEmptyTuple", []()
		{
			struct EmptyConfig
			{
				using Tasks = std::tuple<>;
			};

			expect(std::tuple_size_v<typename TasksFrom<EmptyConfig>::Types>, equal_to(0));
		});

		unit.test("Types_getWhenPassedConfigWithSingleTask_expectTupleOfSameType", []()
		{
			struct Config
			{
				struct LonelyTask
				{
					using Type = DummyTask<1>;
				};

				using Tasks = std::tuple<LonelyTask>;
			};

			expect(typeid(typename TasksFrom<Config>::Types) == typeid(std::tuple<DummyTask<1>>), equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithMultipleTasks_expectTupleOfSameTypes", []()
		{
			struct Config
			{
				struct FirstTask
				{
					using Type = DummyTask<1>;
				};

				struct RepeatedTask
				{
					using Type = DummyTask<2>;
				};

				struct ThirdTask
				{
					using Type = DummyTask<3>;
				};

				using Tasks = std::tuple<FirstTask, RepeatedTask, ThirdTask, RepeatedTask, RepeatedTask>;
			};

			expect(typeid(typename TasksFrom<Config>::Types) == typeid(
				std::tuple<
					DummyTask<1>,
					DummyTask<2>,
					DummyTask<3>,
					DummyTask<2>,
					DummyTask<2>>),
				equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithOverlaidTasks_expectTupleOfFlattenedTypes", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(typeid(typename TasksFrom<Config>::Types) == typeid(std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>>), equal_to(true));
		});
	});
}
