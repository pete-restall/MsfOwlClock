#include <array>
#include <concepts>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/AppToDriverApis.hh"
#include "kernel/tasks/DriverToDriverApis.hh"
#include "kernel/tasks/DriverToKernelApis.hh"
#include "kernel/tasks/ITask.hh"
#include "kernel/tasks/config/RequiredApisFrom.hh"
#include "kernel/tasks/config/IHaveConfigForTask.hh"

#include "../../../TupleUtilities.hh"
#include "../TaskTestDoubles.hh"
#include "DummyTask.hh"

using namespace mettle;

using namespace smeg::kernel::tasks;
using namespace smeg::kernel::tasks::config;

namespace smeg::tests::unit::kernel::tasks::config
{
	template <typename... TApis>
	struct StubRequiredApis
	{
	};

	template <typename... TApis>
	struct StubOtherRequiredApis
	{
	};

	template <auto X>
	struct DummyApi
	{
	};

	suite<> requiredApisFromITaskTest("RequiredApisFrom (ITask) Test Suite", [](auto &unit)
	{
		unit.test("RequiredAppToDriverApisFrom_get_expectAliasWithBoundAppToDriverApisArgument", []()
		{
			expect(std::same_as<RequiredAppToDriverApisFrom<DummyTask<1>>, RequiredApisFrom<AppToDriverApis, DummyTask<1>>>, equal_to(true));
		});

		unit.test("RequiredDriverToDriverApisFrom_get_expectAliasWithBoundDriverToDriverApisArgument", []()
		{
			expect(std::same_as<RequiredDriverToDriverApisFrom<DummyTask<2>>, RequiredApisFrom<DriverToDriverApis, DummyTask<2>>>, equal_to(true));
		});

		unit.test("RequiredDriverToKernelApisFrom_get_expectAliasWithBoundDriverToKernelApisArgument", []()
		{
			expect(std::same_as<RequiredDriverToKernelApisFrom<DummyTask<3>>, RequiredApisFrom<DriverToKernelApis, DummyTask<3>>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedTaskWithDefaultConstructor_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<typename RequiredApisFrom<StubRequiredApis, StubTaskWithDefaultConstructor>::Types>, equal_to(0));
		});

		unit.test("Types_getWhenPassedTaskWithConstructorRequiringOtherApis_expectEmptyTuple", []()
		{
			using OtherRequiredApis = StubOtherRequiredApis<DummyApi<1>>;
			using Task = StubTaskWithRequiredApisConstructor<OtherRequiredApis>;
			expect(std::tuple_size_v<typename RequiredApisFrom<StubRequiredApis, Task>::Types>, equal_to(0));
		});

		unit.test("Types_getWhenPassedTaskWithConstructorRequiringSingleApi_expectTupleWithSameType", []()
		{
			using RequiredApis = StubRequiredApis<DummyApi<1>>;
			using Task = StubTaskWithRequiredApisConstructor<RequiredApis>;
			expect(std::same_as<typename RequiredApisFrom<StubRequiredApis, Task>::Types, std::tuple<DummyApi<1>>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedTaskWithConstructorRequiringMultipleApis_expectTupleWithSameTypesInNoParticularOrder", []()
		{
			using RequiredApis = StubRequiredApis<DummyApi<3>, DummyApi<2>, DummyApi<1>>;
			using Task = StubTaskWithRequiredApisConstructor<RequiredApis>;
			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Task>::Types,
					std::tuple<
						DummyApi<3>,
						DummyApi<2>,
						DummyApi<1>>
				>::inAnyOrder,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedTaskWithConstructorRequiringDuplicatedApis_expectTupleWithoutDuplicatesInNoParticularOrder", []()
		{
			using RequiredApis = StubRequiredApis<DummyApi<3>, DummyApi<2>, DummyApi<1>, DummyApi<2>, DummyApi<4>, DummyApi<3>>;
			using Task = StubTaskWithRequiredApisConstructor<RequiredApis>;
			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Task>::Types,
					std::tuple<
						DummyApi<3>,
						DummyApi<2>,
						DummyApi<1>,
						DummyApi<4>>
				>::inAnyOrder,
				equal_to(true));
		});
	});

	template <ITask TTask>
	struct StubSimpleTaskConfig
	{
		using Type = TTask;
		struct Stack
		{
			static constexpr auto numberOfSlots = 1;
		};
	};

	suite<> requiredApisFromIHaveConfigForSimpleTaskTest("RequiredApisFrom (IHaveConfigForSimpleTask) Test Suite", [](auto &unit)
	{
		unit.test("RequiredAppToDriverApisFrom_get_expectAliasWithBoundAppToDriverApisArgument", []()
		{
			using TaskConfig = StubSimpleTaskConfig<DummyTask<1>>;
			expect(std::same_as<RequiredAppToDriverApisFrom<TaskConfig>, RequiredApisFrom<AppToDriverApis, TaskConfig>>, equal_to(true));
		});

		unit.test("RequiredDriverToDriverApisFrom_get_expectAliasWithBoundDriverToDriverApisArgument", []()
		{
			using TaskConfig = StubSimpleTaskConfig<DummyTask<2>>;
			expect(std::same_as<RequiredDriverToDriverApisFrom<TaskConfig>, RequiredApisFrom<DriverToDriverApis, TaskConfig>>, equal_to(true));
		});

		unit.test("RequiredDriverToKernelApisFrom_get_expectAliasWithBoundDriverToKernelApisArgument", []()
		{
			using TaskConfig = StubSimpleTaskConfig<DummyTask<3>>;
			expect(std::same_as<RequiredDriverToKernelApisFrom<TaskConfig>, RequiredApisFrom<DriverToKernelApis, TaskConfig>>, equal_to(true));
		});

		unit.test("RequiredApisFrom_get_expectAliasToITaskSpecialisationUsingTypeFromSimpleTaskConfig", []()
		{
			using Task = StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<1>>>;
			expect(std::same_as<
				typename RequiredApisFrom<StubRequiredApis, StubSimpleTaskConfig<Task>>::Types,
				typename RequiredApisFrom<StubRequiredApis, Task>::Types>,
				equal_to(true));
		});
	});

	template <ITask... TTasks>
	struct StubOverlaidSimpleTupleOfTasksConfig
	{
		using Types = std::tuple<TTasks...>;
		struct Stack
		{
			static constexpr auto numberOfSlots = 1;
		};

		static_assert(
			IHaveConfigForOverlaidTasks<StubOverlaidSimpleTupleOfTasksConfig<TTasks...>>,
			"StubOverlaidSimpleTupleOfTasksConfig must be an IHaveConfigForOverlaidTasks");
	};

	template <ITask TTask, auto NumberOfTasks>
	struct StubOverlaidSimpleArrayOfTasksConfig
	{
		using Types = std::array<TTask, NumberOfTasks>;
		struct Stack
		{
			static constexpr auto numberOfSlots = 1;
		};

		static_assert(
			IHaveConfigForOverlaidTasks<StubOverlaidSimpleArrayOfTasksConfig<TTask, NumberOfTasks>>,
			"StubOverlaidSimpleArrayOfTasksConfig must be an IHaveConfigForOverlaidTasks");
	};

	template <IHaveConfigForOverlaidTask... TTaskConfigs>
	struct StubOverlaidConfiguredTasksConfig
	{
		using Configs = std::tuple<TTaskConfigs...>;
		struct Stack
		{
			static constexpr auto numberOfSlots = 1;
		};

		static_assert(
			IHaveConfigForOverlaidTasks<StubOverlaidConfiguredTasksConfig<TTaskConfigs...>>,
			"StubOverlaidConfiguredTasksConfig must be an IHaveConfigForOverlaidTasks");
	};

	template <typename TTask>
	struct StubOverlaidTaskConfig
	{
		using Type = TTask;
	};

	suite<> requiredApisFromIHaveConfigForOverlaidTasksTest("RequiredApisFrom (IHaveConfigForOverlaidTasks) Test Suite", [](auto &unit)
	{
		unit.test("RequiredAppToDriverApisFrom_getForOverlaidSimpleTasks_expectAliasWithBoundAppToDriverApisArgument", []()
		{
			using TaskConfig = StubOverlaidSimpleTupleOfTasksConfig<DummyTask<1>, DummyTask<2>>;
			expect(std::same_as<RequiredAppToDriverApisFrom<TaskConfig>, RequiredApisFrom<AppToDriverApis, TaskConfig>>, equal_to(true));
		});

		unit.test("RequiredAppToDriverApisFrom_getForOverlaidConfiguredTasks_expectAliasWithBoundAppToDriverApisArgument", []()
		{
			using TaskConfig = StubOverlaidConfiguredTasksConfig<StubOverlaidTaskConfig<DummyTask<1>>, StubOverlaidTaskConfig<DummyTask<2>>>;
			expect(std::same_as<RequiredAppToDriverApisFrom<TaskConfig>, RequiredApisFrom<AppToDriverApis, TaskConfig>>, equal_to(true));
		});

		unit.test("RequiredDriverToDriverApisFrom_getForOverlaidSimpleTasks_expectAliasWithBoundDriverToDriverApisArgument", []()
		{
			using TaskConfig = StubOverlaidSimpleTupleOfTasksConfig<DummyTask<3>, DummyTask<4>>;
			expect(std::same_as<RequiredDriverToDriverApisFrom<TaskConfig>, RequiredApisFrom<DriverToDriverApis, TaskConfig>>, equal_to(true));
		});

		unit.test("RequiredDriverToDriverApisFrom_getForOverlaidConfiguredTasks_expectAliasWithBoundDriverToDriverApisArgument", []()
		{
			using TaskConfig = StubOverlaidConfiguredTasksConfig<StubOverlaidTaskConfig<DummyTask<3>>, StubOverlaidTaskConfig<DummyTask<4>>>;
			expect(std::same_as<RequiredDriverToDriverApisFrom<TaskConfig>, RequiredApisFrom<DriverToDriverApis, TaskConfig>>, equal_to(true));
		});

		unit.test("RequiredDriverToKernelApisFrom_getForOverlaidTupleOfSimpleTasks_expectAliasWithBoundDriverToKernelApisArgument", []()
		{
			using TaskConfig = StubOverlaidSimpleTupleOfTasksConfig<DummyTask<5>, DummyTask<6>>;
			expect(std::same_as<RequiredDriverToKernelApisFrom<TaskConfig>, RequiredApisFrom<DriverToKernelApis, TaskConfig>>, equal_to(true));
		});

		unit.test("RequiredDriverToKernelApisFrom_getForOverlaidConfiguredTasks_expectAliasWithBoundDriverToKernelApisArgument", []()
		{
			using TaskConfig = StubOverlaidConfiguredTasksConfig<StubOverlaidTaskConfig<DummyTask<5>>, StubOverlaidTaskConfig<DummyTask<6>>>;
			expect(std::same_as<RequiredDriverToKernelApisFrom<TaskConfig>, RequiredApisFrom<DriverToKernelApis, TaskConfig>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedSimpleOverlayWithTupleOfTasksRequiringSpecifiedAndUnspecifiedApis_expectTupleOfSpecifiedApisInNoParticularOrder", []()
		{
			using Config = StubOverlaidSimpleTupleOfTasksConfig<
				StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<2>, DummyApi<4>>>,
				StubTaskWithDefaultConstructor,
				StubTaskWithRequiredApisConstructor<StubOtherRequiredApis<DummyApi<6>>>,
				StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<8>, DummyApi<10>>>,
				StubTaskWithRequiredApisConstructor<StubOtherRequiredApis<DummyApi<12>>>>;

			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Config>::Types,
					std::tuple<
						DummyApi<2>,
						DummyApi<4>,
						DummyApi<8>,
						DummyApi<10>>
				>::inAnyOrder,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedSimpleOverlayWithTupleOfTasksRequiringDuplicateApis_expectTupleWithoutDuplicatesInNoParticularOrder", []()
		{
			using Config = StubOverlaidSimpleTupleOfTasksConfig<
				StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<3>, DummyApi<5>, DummyApi<7>, DummyApi<5>>>,
				StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<5>, DummyApi<7>, DummyApi<3>, DummyApi<5>>>,
				StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<7>, DummyApi<5>, DummyApi<3>, DummyApi<1>>>>;

			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Config>::Types,
					std::tuple<
						DummyApi<3>,
						DummyApi<5>,
						DummyApi<7>,
						DummyApi<1>>
				>::inAnyOrder,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedSimpleOverlayWithArrayOfTasksRequiringSpecifiedApis_expectTupleOfSpecifiedApisWithoutDuplicatesInNoParticularOrder", []()
		{
			using Config = StubOverlaidSimpleArrayOfTasksConfig<
				StubTaskWithRequiredApisConstructor<
					StubRequiredApis<DummyApi<-1>, DummyApi<0>, DummyApi<1>, DummyApi<2>, DummyApi<1>, DummyApi<0>, DummyApi<-1>>>,
				10>;

			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Config>::Types,
					std::tuple<
						DummyApi<-1>,
						DummyApi<0>,
						DummyApi<1>,
						DummyApi<2>>
				>::inAnyOrder,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedSimpleOverlayWithArrayOfTasksRequiringUnspecifiedApis_expectEmptyTuple", []()
		{
			using Config = StubOverlaidSimpleArrayOfTasksConfig<
				StubTaskWithRequiredApisConstructor<
					StubOtherRequiredApis<DummyApi<-1>, DummyApi<0>, DummyApi<1>, DummyApi<2>, DummyApi<1>, DummyApi<0>, DummyApi<-1>>>,
				10>;

			expect(std::same_as<typename RequiredApisFrom<StubRequiredApis, Config>::Types, std::tuple<>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfiguredOverlayWithTasksRequiringSpecifiedAndUnspecifiedApis_expectTupleOfSpecifiedApisInNoParticularOrder", []()
		{
			struct TaskConfigWithSpecifiedApis
			{
				using Type = StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<1>, DummyApi<11>>>;
			};

			struct TaskConfigWithNoApis
			{
				using Type = StubTaskWithDefaultConstructor;
			};

			struct TaskConfigWithUnspecifiedApis
			{
				using Type = StubTaskWithRequiredApisConstructor<StubOtherRequiredApis<DummyApi<3>>>;
			};

			using Config = StubOverlaidConfiguredTasksConfig<
				TaskConfigWithSpecifiedApis,
				TaskConfigWithNoApis,
				TaskConfigWithSpecifiedApis,
				TaskConfigWithUnspecifiedApis>;

			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Config>::Types,
					std::tuple<
						DummyApi<1>,
						DummyApi<11>>
				>::inAnyOrder,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedConfiguredOverlayWithTasksRequiringDuplicateApis_expectTupleWithoutDuplicatesInNoParticularOrder", []()
		{
			struct TaskConfig1
			{
				using Type = StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<7>, DummyApi<-98>, DummyApi<7>>>;
			};

			struct TaskConfig2
			{
				using Type = StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<-127>, DummyApi<23971>, DummyApi<-98>, DummyApi<173>>>;
			};

			struct TaskConfig3
			{
				using Type = StubTaskWithRequiredApisConstructor<StubRequiredApis<DummyApi<23971>>>;
			};

			using Config = StubOverlaidConfiguredTasksConfig<
				TaskConfig1,
				TaskConfig2,
				TaskConfig3>;

			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Config>::Types,
					std::tuple<
						DummyApi<7>,
						DummyApi<-98>,
						DummyApi<-127>,
						DummyApi<23971>,
						DummyApi<173>>
				>::inAnyOrder,
				equal_to(true));
		});
	});

	suite<> requiredApisFromIHaveConfigForTasksTest("RequiredApisFrom (IHaveConfigForTasks) Test Suite", [](auto &unit)
	{
		unit.test("RequiredAppToDriverApisFrom_getForTopLevelConfig_expectAliasWithBoundAppToDriverApisArgument", []()
		{
			struct Config
			{
				using Tasks = std::tuple<StubSimpleTaskConfig<DummyTask<1>>, StubSimpleTaskConfig<DummyTask<2>>>;
			};

			expect(std::same_as<RequiredAppToDriverApisFrom<Config>, RequiredApisFrom<AppToDriverApis, Config>>, equal_to(true));
		});

		unit.test("RequiredAppToDriverApisFrom_getForTopLevelConfig_expectAliasWithBoundAppToDriverApisArgument", []()
		{
			struct Config
			{
				using Tasks = std::tuple<StubSimpleTaskConfig<DummyTask<3>>, StubSimpleTaskConfig<DummyTask<4>>>;
			};

			expect(std::same_as<RequiredAppToDriverApisFrom<Config>, RequiredApisFrom<AppToDriverApis, Config>>, equal_to(true));
		});

		unit.test("RequiredDriverToDriverApisFrom_getForTopLevelConfig_expectAliasWithBoundDriverToDriverApisArgument", []()
		{
			struct Config
			{
				using Tasks = std::tuple<StubSimpleTaskConfig<DummyTask<5>>, StubSimpleTaskConfig<DummyTask<6>>>;
			};

			expect(std::same_as<RequiredDriverToDriverApisFrom<Config>, RequiredApisFrom<DriverToDriverApis, Config>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithEmptyTupleOfTasks_expectEmptyTuple", []()
		{
			struct Config
			{
				using Tasks = std::tuple<>;
			};

			expect(std::same_as<typename RequiredApisFrom<StubRequiredApis, Config>::Types, std::tuple<>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithTupleOfSingleSimpleTaskRequiringNoApis_expectEmptyTuple", []()
		{
			struct Config
			{
				using Tasks = std::tuple<StubSimpleTaskConfig<StubTaskWithDefaultConstructor>>;
			};

			expect(std::same_as<typename RequiredApisFrom<StubRequiredApis, Config>::Types, std::tuple<>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithTupleOfSingleSimpleTaskRequiringSpecifiedApis_expectTupleOfSpecifiedApisInNoParticularOrder", []()
		{
			struct Config
			{
				using TaskWithRequiredApis = StubSimpleTaskConfig<
					StubTaskWithRequiredApisConstructor<
						StubRequiredApis<
							DummyApi<123>,
							DummyApi<456>,
							DummyApi<789>>>>;

				using Tasks = std::tuple<TaskWithRequiredApis>;
			};

			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Config>::Types,
					std::tuple<
						DummyApi<123>,
						DummyApi<456>,
						DummyApi<789>>
				>::inAnyOrder,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithTupleOfSingleSimpleTaskRequiringUnspecifiedApis_expectEmptyTuple", []()
		{
			struct Config
			{
				using TasksWithOtherApis = StubSimpleTaskConfig<
					StubTaskWithRequiredApisConstructor<
						StubOtherRequiredApis<
							DummyApi<123>,
							DummyApi<456>>>>;

				using Tasks = std::tuple<TasksWithOtherApis>;
			};
			expect(std::same_as<typename RequiredApisFrom<StubRequiredApis, Config>::Types, std::tuple<>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithTupleOfComplicatedTaskConfigsRequiringSpecifiedAndUnspecifiedApis_expectTupleOfSpecifiedApisWithoutDuplicatesInNoParticularOrder", []()
		{
			struct Config
			{
				using TaskConfig1 = StubSimpleTaskConfig<
					StubTaskWithRequiredApisConstructor<
						StubRequiredApis<
							DummyApi<1>,
							DummyApi<2>,
							DummyApi<2>,
							DummyApi<3>>>>;

				using TaskConfig2 = StubOverlaidSimpleTupleOfTasksConfig<
					StubTaskWithRequiredApisConstructor<
						StubOtherRequiredApis<
							DummyApi<12>,
							DummyApi<37>>>,

					StubTaskWithRequiredApisConstructor<
						StubRequiredApis<
							DummyApi<1>,
							DummyApi<5>,
							DummyApi<4>,
							DummyApi<6>,
							DummyApi<6>>>,

					StubTaskWithDefaultConstructor>;

				using TaskConfig3 = StubOverlaidSimpleArrayOfTasksConfig<
					StubTaskWithRequiredApisConstructor<
						StubRequiredApis<
							DummyApi<7>>>,
					7>;

				using TaskConfig4 = StubOverlaidConfiguredTasksConfig<
					StubOverlaidTaskConfig<StubTaskWithDefaultConstructor>,

					StubOverlaidTaskConfig<
						StubTaskWithRequiredApisConstructor<
							StubOtherRequiredApis<
								DummyApi<867>>>>,

					StubOverlaidTaskConfig<
						StubTaskWithRequiredApisConstructor<
							StubOtherRequiredApis<
								DummyApi<-19>,
								DummyApi<18>>>>,

					StubOverlaidTaskConfig<
						StubTaskWithRequiredApisConstructor<
							StubRequiredApis<
								DummyApi<3>,
								DummyApi<8>,
								DummyApi<9>,
								DummyApi<9>>>>,

					StubOverlaidTaskConfig<
						StubTaskWithRequiredApisConstructor<
							StubRequiredApis<
								DummyApi<9>>>>>;

				using Tasks = std::tuple<TaskConfig1, TaskConfig2, TaskConfig3, TaskConfig4>;
			};

			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Config>::Types,
					std::tuple<
						DummyApi<1>,
						DummyApi<2>,
						DummyApi<3>,
						DummyApi<4>,
						DummyApi<5>,
						DummyApi<6>,
						DummyApi<7>,
						DummyApi<8>,
						DummyApi<9>>
				>::inAnyOrder,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithEmptyArrayOfTasks_expectEmptyTuple", []()
		{
			struct Config
			{
				using TaskWithRequiredApis = StubSimpleTaskConfig<
					StubTaskWithRequiredApisConstructor<
						StubRequiredApis<
							DummyApi<123>>>>;

				using Tasks = std::array<TaskWithRequiredApis, 0>;
			};

			expect(std::same_as<typename RequiredApisFrom<StubRequiredApis, Config>::Types, std::tuple<>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithArrayOfSingleSimpleTaskRequiringNoApis_expectEmptyTuple", []()
		{
			struct Config
			{
				using Tasks = std::array<StubSimpleTaskConfig<StubTaskWithDefaultConstructor>, 1>;
			};

			expect(std::same_as<typename RequiredApisFrom<StubRequiredApis, Config>::Types, std::tuple<>>, equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithArrayOfSingleSimpleTaskRequiringSpecifiedApis_expectTupleOfSpecifiedApisInNoParticularOrder", []()
		{
			struct Config
			{
				using TaskWithRequiredApis = StubSimpleTaskConfig<
					StubTaskWithRequiredApisConstructor<
						StubRequiredApis<
							DummyApi<123>,
							DummyApi<456>,
							DummyApi<789>>>>;

				using Tasks = std::array<TaskWithRequiredApis, 1>;
			};

			expect(
				TuplesContainSameElements<
					typename RequiredApisFrom<StubRequiredApis, Config>::Types,
					std::tuple<
						DummyApi<123>,
						DummyApi<456>,
						DummyApi<789>>
				>::inAnyOrder,
				equal_to(true));
		});

		unit.test("Types_getWhenPassedConfigWithArrayOfSingleSimpleTaskRequiringUnspecifiedApis_expectEmptyTuple", []()
		{
			struct Config
			{
				using TasksWithOtherApis = StubSimpleTaskConfig<
					StubTaskWithRequiredApisConstructor<
						StubOtherRequiredApis<
							DummyApi<123>,
							DummyApi<456>>>>;

				using Tasks = std::array<TasksWithOtherApis, 1>;
			};
			expect(std::same_as<typename RequiredApisFrom<StubRequiredApis, Config>::Types, std::tuple<>>, equal_to(true));
		});
	});
}
