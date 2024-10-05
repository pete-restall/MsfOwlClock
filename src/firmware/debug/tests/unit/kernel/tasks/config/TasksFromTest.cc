#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/config/TasksFrom.hh"
#include "kernel/tasks/config/ResourceToTaskAssociation.hh"
#include "kernel/tasks/config/dsl/DefaultTaskStack.hh"

#include "DummyTask.hh"

using namespace mettle;

using namespace smeg::kernel::tasks::config;

namespace smeg::tests::unit::kernel::tasks::config
{
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

		unit.test("Types_getWhenPassedConfigWithMixOfSimpleAndOverlaidTasks_expectTupleOfFlattenedTypes", []()
		{
			struct Config
			{
				struct FirstSimpleTask
				{
					using Type = DummyTask<10>;
				};

				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<9>, DummyTask<8>, DummyTask<7>>;
				};

				struct SecondSimpleTask
				{
					using Type = DummyTask<6>;
				};

				struct ThirdSimpleTask
				{
					using Type = DummyTask<5>;
				};

				using Tasks = std::tuple<FirstSimpleTask, OverlaidTasks, SecondSimpleTask, ThirdSimpleTask, OverlaidTasks, SecondSimpleTask>;
			};

			expect(typeid(typename TasksFrom<Config>::Types) == typeid(
				std::tuple<
					DummyTask<10>,
					DummyTask<9>,
					DummyTask<8>,
					DummyTask<7>,
					DummyTask<6>,
					DummyTask<5>,
					DummyTask<9>,
					DummyTask<8>,
					DummyTask<7>,
					DummyTask<6>>),
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithEmptyTasks_expectEmptyTuple", []()
		{
			struct EmptyConfig
			{
				using Tasks = std::tuple<>;
			};

			expect(std::tuple_size_v<typename TasksFrom<EmptyConfig>::Associations>, equal_to(0));
		});

		unit.test("Associations_getWhenPassedConfigWithSingleTask_expectTupleOfSameTypeWithIndex0", []()
		{
			struct Config
			{
				struct LonelyTask
				{
					using Type = DummyTask<14>;
				};

				using Tasks = std::tuple<LonelyTask>;
			};

			expect(typeid(typename TasksFrom<Config>::Associations) == typeid(std::tuple<ResourceToTaskAssociation<DummyTask<14>, 0>>), equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithMultipleTasks_expectTupleOfSameTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct FirstTask
				{
					using Type = DummyTask<5>;
				};

				struct RepeatedTask
				{
					using Type = DummyTask<-12>;
				};

				struct ThirdTask
				{
					using Type = DummyTask<3>;
				};

				using Tasks = std::tuple<FirstTask, RepeatedTask, ThirdTask, RepeatedTask, RepeatedTask>;
			};

			expect(typeid(typename TasksFrom<Config>::Associations) == typeid(
				std::tuple<
					ResourceToTaskAssociation<DummyTask<5>, 0>,
					ResourceToTaskAssociation<DummyTask<-12>, 1>,
					ResourceToTaskAssociation<DummyTask<3>, 2>,
					ResourceToTaskAssociation<DummyTask<-12>, 3>,
					ResourceToTaskAssociation<DummyTask<-12>, 4>>),
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithOverlaidTasks_expectTupleOfFlattenedTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<2>, DummyTask<5>, DummyTask<7>>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(typeid(typename TasksFrom<Config>::Associations) == typeid(
				std::tuple<
					ResourceToTaskAssociation<DummyTask<2>, 0>,
					ResourceToTaskAssociation<DummyTask<5>, 1>,
					ResourceToTaskAssociation<DummyTask<7>, 2>>),
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithMixOfSimpleAndOverlaidTasks_expectTupleOfFlattenedTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct FirstSimpleTask
				{
					using Type = DummyTask<101>;
				};

				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<493>, DummyTask<88>, DummyTask<173789>>;
				};

				struct SecondSimpleTask
				{
					using Type = DummyTask<0>;
				};

				struct ThirdSimpleTask
				{
					using Type = DummyTask<-1>;
				};

				using Tasks = std::tuple<FirstSimpleTask, OverlaidTasks, SecondSimpleTask, ThirdSimpleTask, OverlaidTasks, SecondSimpleTask>;
			};

			expect(typeid(typename TasksFrom<Config>::Associations) == typeid(
				std::tuple<
					ResourceToTaskAssociation<DummyTask<101>, 0>,
					ResourceToTaskAssociation<DummyTask<493>, 1>,
					ResourceToTaskAssociation<DummyTask<88>, 2>,
					ResourceToTaskAssociation<DummyTask<173789>, 3>,
					ResourceToTaskAssociation<DummyTask<0>, 4>,
					ResourceToTaskAssociation<DummyTask<-1>, 5>,
					ResourceToTaskAssociation<DummyTask<493>, 6>,
					ResourceToTaskAssociation<DummyTask<88>, 7>,
					ResourceToTaskAssociation<DummyTask<173789>, 8>,
					ResourceToTaskAssociation<DummyTask<0>, 9>>),
				equal_to(true));
		});
	});
}
