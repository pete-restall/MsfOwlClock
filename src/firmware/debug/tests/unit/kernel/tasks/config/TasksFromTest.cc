#include <array>
#include <concepts>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/config/TasksFrom.hh"
#include "kernel/tasks/config/ResourceToTaskAssociation.hh"

#include "DummyTask.hh"
#include "DummyTaskConfig.hh"
#include "DummyTaskStackConfig.hh"

using namespace mettle;

using namespace smeg::kernel::tasks::config;

namespace smeg::tests::unit::kernel::tasks::config
{
	suite<> tasksFromTest("TasksFrom Test Suite", [](auto &unit)
	{
		unit.test("Types_getWhenPassedConfigWithEmptyTupleOfTasks_expectEmptyTuple", []()
		{
			struct EmptyConfig
			{
				using Tasks = std::tuple<>;
			};

			expect(std::tuple_size_v<typename TasksFrom<EmptyConfig>::Types>, equal_to(0));
		});

		unit.test("Types_getWhenPassedConfigWithEmptyArrayOfTasks_expectEmptyTuple", []()
		{
			struct EmptyConfig
			{
				using Tasks = std::array<DummyTaskConfig<1>, 0>;
			};

			expect(std::tuple_size_v<typename TasksFrom<EmptyConfig>::Types>, equal_to(0));
		});

		unit.test("Types_getWhenPassedConfigWithTupleOfSingleTask_expectTupleOfSameType", []()
		{
			struct Config
			{
				struct LonelyTask
				{
					using Type = DummyTask<1>;
					using Stack = DummyTaskStackConfig<1>;
				};

				using Tasks = std::tuple<LonelyTask>;
			};

			expect(std::same_as<typename TasksFrom<Config>::Types, std::tuple<DummyTask<1>>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithArrayOfSingleTask_expectTupleOfSameType", []()
		{
			struct Config
			{
				struct LonelyTask
				{
					using Type = DummyTask<1>;
					using Stack = DummyTaskStackConfig<2>;
				};

				using Tasks = std::array<LonelyTask, 1>;
			};

			expect(std::same_as<typename TasksFrom<Config>::Types, std::tuple<DummyTask<1>>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithArrayOfMultipleTasks_expectTupleOfSameTypeRepeated", []()
		{
			struct Config
			{
				struct LonelyTask
				{
					using Type = DummyTask<1>;
					using Stack = DummyTaskStackConfig<3>;
				};

				using Tasks = std::array<LonelyTask, 3>;
			};

			expect(std::same_as<typename TasksFrom<Config>::Types, std::tuple<DummyTask<1>, DummyTask<1>, DummyTask<1>>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithMultipleTasks_expectTupleOfSameTypes", []()
		{
			struct Config
			{
				struct FirstTask
				{
					using Type = DummyTask<1>;
					using Stack = DummyTaskStackConfig<4>;
				};

				struct RepeatedTask
				{
					using Type = DummyTask<2>;
					using Stack = DummyTaskStackConfig<5>;
				};

				struct ThirdTask
				{
					using Type = DummyTask<3>;
					using Stack = DummyTaskStackConfig<6>;
				};

				using Tasks = std::tuple<FirstTask, RepeatedTask, ThirdTask, RepeatedTask, RepeatedTask>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Types,
				std::tuple<
					DummyTask<1>,
					DummyTask<2>,
					DummyTask<3>,
					DummyTask<2>,
					DummyTask<2>>>,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithTupleOfSimpleOverlaidTasks_expectTupleOfFlattenedTypes", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>>;
					using Stack = DummyTaskStackConfig<7>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(std::same_as<typename TasksFrom<Config>::Types, std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithArrayOfSingleSimpleOverlaidTasks_expectTupleOfFlattenedTypes", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>>;
					using Stack = DummyTaskStackConfig<8>;
				};

				using Tasks = std::array<OverlaidTasks, 1>;
			};

			expect(std::same_as<typename TasksFrom<Config>::Types, std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithArrayOfMultipleSimpleOverlaidTasks_expectTupleOfFlattenedTypes", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>>;
					using Stack = DummyTaskStackConfig<9>;
				};

				using Tasks = std::array<OverlaidTasks, 2>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Types,
				std::tuple<
					DummyTask<1>, DummyTask<2>, DummyTask<3>,
					DummyTask<1>, DummyTask<2>, DummyTask<3>>>,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithTupleOfConfiguredOverlaidTasks_expectTupleOfFlattenedTypes", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					struct OverlaidTaskConfig1
					{
						using Type = DummyTask<9871>;
					};

					struct OverlaidTaskConfig2
					{
						using Type = DummyTask<-127>;
					};

					struct OverlaidTaskConfig3
					{
						using Type = DummyTask<-7621>;
					};

					using Configs = std::tuple<OverlaidTaskConfig1, OverlaidTaskConfig2, OverlaidTaskConfig3>;
					using Stack = DummyTaskStackConfig<3>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Types,
				std::tuple<
					DummyTask<9871>,
					DummyTask<-127>,
					DummyTask<-7621>>>,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithArrayOfConfiguredOverlaidTasks_expectTupleOfFlattenedTypes", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					struct OverlaidTaskConfig
					{
						using Type = DummyTask<91>;
					};

					using Configs = std::array<OverlaidTaskConfig, 4>;
					using Stack = DummyTaskStackConfig<18>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Types,
				std::tuple<
					DummyTask<91>,
					DummyTask<91>,
					DummyTask<91>,
					DummyTask<91>>>,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithMixOfSimpleAndSimpleOverlaidTasks_expectTupleOfFlattenedTypes", []()
		{
			struct Config
			{
				struct FirstSimpleTask
				{
					using Type = DummyTask<10>;
					using Stack = DummyTaskStackConfig<10>;
				};

				struct SimpleOverlaidTasks
				{
					using Types = std::tuple<DummyTask<9>, DummyTask<8>, DummyTask<7>>;
					using Stack = DummyTaskStackConfig<11>;
				};

				struct ConfiguredOverlaidArrayOfTasks
				{
					struct OverlaidTaskConfig
					{
						using Type = DummyTask<-76>;
					};

					using Configs = std::array<OverlaidTaskConfig, 3>;
					using Stack = DummyTaskStackConfig<19>;
				};

				struct SecondSimpleTask
				{
					using Type = DummyTask<6>;
					using Stack = DummyTaskStackConfig<12>;
				};

				struct ThirdSimpleTask
				{
					using Type = DummyTask<5>;
					using Stack = DummyTaskStackConfig<13>;
				};

				struct ConfiguredOverlaidTupleOfTasks
				{
					struct OverlaidTaskConfig1
					{
						using Type = DummyTask<-193>;
					};

					struct OverlaidTaskConfig2
					{
						using Type = DummyTask<-192>;
					};

					struct OverlaidTaskConfig3
					{
						using Type = DummyTask<-191>;
					};

					using Configs = std::tuple<OverlaidTaskConfig3, OverlaidTaskConfig2, OverlaidTaskConfig1>;
					using Stack = DummyTaskStackConfig<66>;
				};

				using Tasks = std::tuple<
					FirstSimpleTask,
					ConfiguredOverlaidArrayOfTasks,
					SimpleOverlaidTasks,
					SecondSimpleTask,
					ThirdSimpleTask,
					SimpleOverlaidTasks,
					SecondSimpleTask,
					ConfiguredOverlaidTupleOfTasks>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Types,
				std::tuple<
					DummyTask<10>,

					DummyTask<-76>,
					DummyTask<-76>,
					DummyTask<-76>,

					DummyTask<9>,
					DummyTask<8>,
					DummyTask<7>,

					DummyTask<6>,
					DummyTask<5>,

					DummyTask<9>,
					DummyTask<8>,
					DummyTask<7>,

					DummyTask<6>,

					DummyTask<-191>,
					DummyTask<-192>,
					DummyTask<-193>>>,
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithEmptyTupleOfTasks_expectEmptyTuple", []()
		{
			struct EmptyConfig
			{
				using Tasks = std::tuple<>;
			};

			expect(std::tuple_size_v<typename TasksFrom<EmptyConfig>::Associations>, equal_to(0));
		});

		unit.test("Associations_getWhenPassedConfigWithEmptyArrayOfTasks_expectEmptyTuple", []()
		{
			struct EmptyConfig
			{
				using Tasks = std::array<DummyTaskConfig<1>, 0>;
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
					using Stack = DummyTaskStackConfig<14>;
				};

				using Tasks = std::tuple<LonelyTask>;
			};

			expect(std::same_as<typename TasksFrom<Config>::Associations, std::tuple<ResourceToTaskAssociation<DummyTask<14>, 0>>>, equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithArrayOfSingleTask_expectTupleOfSameTypeWithIndex0", []()
		{
			struct Config
			{
				struct LonelyTask
				{
					using Type = DummyTask<14>;
					using Stack = DummyTaskStackConfig<15>;
				};

				using Tasks = std::array<LonelyTask, 1>;
			};

			expect(std::same_as<typename TasksFrom<Config>::Associations, std::tuple<ResourceToTaskAssociation<DummyTask<14>, 0>>>, equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithArrayOfMultipleTasks_expectTupleOfSameTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct SomeTask
				{
					using Type = DummyTask<14>;
					using Stack = DummyTaskStackConfig<16>;
				};

				using Tasks = std::array<SomeTask, 3>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Associations,
				std::tuple<
					ResourceToTaskAssociation<DummyTask<14>, 0>,
					ResourceToTaskAssociation<DummyTask<14>, 1>,
					ResourceToTaskAssociation<DummyTask<14>, 2>>>,
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithMultipleTasks_expectTupleOfSameTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct FirstTask
				{
					using Type = DummyTask<5>;
					using Stack = DummyTaskStackConfig<17>;
				};

				struct RepeatedTask
				{
					using Type = DummyTask<-12>;
					using Stack = DummyTaskStackConfig<18>;
				};

				struct ThirdTask
				{
					using Type = DummyTask<3>;
					using Stack = DummyTaskStackConfig<19>;
				};

				using Tasks = std::tuple<FirstTask, RepeatedTask, ThirdTask, RepeatedTask, RepeatedTask>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Associations,
				std::tuple<
					ResourceToTaskAssociation<DummyTask<5>, 0>,
					ResourceToTaskAssociation<DummyTask<-12>, 1>,
					ResourceToTaskAssociation<DummyTask<3>, 2>,
					ResourceToTaskAssociation<DummyTask<-12>, 3>,
					ResourceToTaskAssociation<DummyTask<-12>, 4>>>,
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithTupleOfSimpleOverlaidTasks_expectTupleOfFlattenedTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<2>, DummyTask<5>, DummyTask<7>>;
					using Stack = DummyTaskStackConfig<20>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Associations,
				std::tuple<
					ResourceToTaskAssociation<DummyTask<2>, 0>,
					ResourceToTaskAssociation<DummyTask<5>, 1>,
					ResourceToTaskAssociation<DummyTask<7>, 2>>>,
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithArrayOfSingleSimpleOverlaidTasks_expectTupleOfFlattenedTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<2>, DummyTask<5>, DummyTask<7>>;
					using Stack = DummyTaskStackConfig<21>;
				};

				using Tasks = std::array<OverlaidTasks, 1>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Associations,
				std::tuple<
					ResourceToTaskAssociation<DummyTask<2>, 0>,
					ResourceToTaskAssociation<DummyTask<5>, 1>,
					ResourceToTaskAssociation<DummyTask<7>, 2>>>,
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithArrayOfMultipleSimpleOverlaidTasks_expectTupleOfFlattenedTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					using Types = std::tuple<DummyTask<2>, DummyTask<5>, DummyTask<7>>;
					using Stack = DummyTaskStackConfig<22>;
				};

				using Tasks = std::array<OverlaidTasks, 2>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Associations,
				std::tuple<
					ResourceToTaskAssociation<DummyTask<2>, 0>,
					ResourceToTaskAssociation<DummyTask<5>, 1>,
					ResourceToTaskAssociation<DummyTask<7>, 2>,
					ResourceToTaskAssociation<DummyTask<2>, 3>,
					ResourceToTaskAssociation<DummyTask<5>, 4>,
					ResourceToTaskAssociation<DummyTask<7>, 5>>>,
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithTupleOfConfiguredOverlaidTasks_expectTupleOfFlattenedTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					struct OverlaidTaskConfig1
					{
						using Type = DummyTask<57>;
					};

					struct OverlaidTaskConfig2
					{
						using Type = DummyTask<-467>;
					};

					struct OverlaidTaskConfig3
					{
						using Type = DummyTask<218>;
					};

					using Configs = std::tuple<OverlaidTaskConfig1, OverlaidTaskConfig2, OverlaidTaskConfig3>;
					using Stack = DummyTaskStackConfig<2>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Associations,
				std::tuple<
					ResourceToTaskAssociation<DummyTask<57>, 0>,
					ResourceToTaskAssociation<DummyTask<-467>, 1>,
					ResourceToTaskAssociation<DummyTask<218>, 2>>>,
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithArrayOfConfiguredOverlaidTasks_expectTupleOfFlattenedTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct OverlaidTasks
				{
					struct OverlaidTaskConfig
					{
						using Type = DummyTask<88>;
					};

					using Configs = std::array<OverlaidTaskConfig, 5>;
					using Stack = DummyTaskStackConfig<0>;
				};

				using Tasks = std::tuple<OverlaidTasks>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Associations,
				std::tuple<
					ResourceToTaskAssociation<DummyTask<88>, 0>,
					ResourceToTaskAssociation<DummyTask<88>, 1>,
					ResourceToTaskAssociation<DummyTask<88>, 2>,
					ResourceToTaskAssociation<DummyTask<88>, 3>,
					ResourceToTaskAssociation<DummyTask<88>, 4>>>,
				equal_to(true));
		});

		unit.test("Associations_getWhenPassedConfigWithMixOfSimpleAndOverlaidTasks_expectTupleOfFlattenedTypesWithIncrementingIndices", []()
		{
			struct Config
			{
				struct ConfiguredOverlaidTupleOfTasks
				{
					struct OverlaidTaskConfig1
					{
						using Type = DummyTask<898>;
					};

					struct OverlaidTaskConfig2
					{
						using Type = DummyTask<902>;
					};

					struct OverlaidTaskConfig3
					{
						using Type = DummyTask<904>;
					};

					using Configs = std::tuple<OverlaidTaskConfig1, OverlaidTaskConfig2, OverlaidTaskConfig3>;
					using Stack = DummyTaskStackConfig<33>;
				};

				struct FirstSimpleTask
				{
					using Type = DummyTask<101>;
					using Stack = DummyTaskStackConfig<23>;
				};

				struct SimpleOverlaidTasks
				{
					using Types = std::tuple<DummyTask<493>, DummyTask<88>, DummyTask<173789>>;
					using Stack = DummyTaskStackConfig<24>;
				};

				struct SecondSimpleTask
				{
					using Type = DummyTask<0>;
					using Stack = DummyTaskStackConfig<25>;
				};

				struct ThirdSimpleTask
				{
					using Type = DummyTask<-1>;
					using Stack = DummyTaskStackConfig<26>;
				};

				struct ConfiguredOverlaidArrayOfTasks
				{
					struct OverlaidTaskConfig
					{
						using Type = DummyTask<-1877>;
					};

					using Configs = std::array<OverlaidTaskConfig, 2>;
					using Stack = DummyTaskStackConfig<18>;
				};

				using Tasks = std::tuple<
					ConfiguredOverlaidTupleOfTasks,
					FirstSimpleTask,
					SimpleOverlaidTasks,
					SecondSimpleTask,
					ThirdSimpleTask,
					SimpleOverlaidTasks,
					SecondSimpleTask,
					ConfiguredOverlaidArrayOfTasks>;
			};

			expect(std::same_as<
				typename TasksFrom<Config>::Associations,
				std::tuple<
					ResourceToTaskAssociation<DummyTask<898>, 0>,
					ResourceToTaskAssociation<DummyTask<902>, 1>,
					ResourceToTaskAssociation<DummyTask<904>, 2>,

					ResourceToTaskAssociation<DummyTask<101>, 3>,

					ResourceToTaskAssociation<DummyTask<493>, 4>,
					ResourceToTaskAssociation<DummyTask<88>, 5>,
					ResourceToTaskAssociation<DummyTask<173789>, 6>,

					ResourceToTaskAssociation<DummyTask<0>, 7>,

					ResourceToTaskAssociation<DummyTask<-1>, 8>,

					ResourceToTaskAssociation<DummyTask<493>, 9>,
					ResourceToTaskAssociation<DummyTask<88>, 10>,
					ResourceToTaskAssociation<DummyTask<173789>, 11>,

					ResourceToTaskAssociation<DummyTask<0>, 12>,

					ResourceToTaskAssociation<DummyTask<-1877>, 13>,
					ResourceToTaskAssociation<DummyTask<-1877>, 14>>>,
				equal_to(true));
		});
	});
}
