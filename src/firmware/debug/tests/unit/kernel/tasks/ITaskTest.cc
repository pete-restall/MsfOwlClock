#include <type_traits>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/ITask.hh"

#include "TaskTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel::tasks;

namespace smeg::tests::unit::kernel::tasks
{
	template <typename T>
	struct IsTask
	{
		using Type = T;
		static constexpr bool isTask = true;
	};

	template <typename T>
	struct IsNotTask
	{
		using Type = T;
		static constexpr bool isTask = false;
	};

	template <typename... TApis>
	struct _DummyRequiredApis
	{
	};

	using DummyRequiredApis = _DummyRequiredApis<>;

	struct DummyApi
	{
	};

	struct StubTaskWithBooleanReturn
	{
		bool run(void)
		{
			return true;
		}
	};

	template <typename TRequiredApis>
	struct StubTaskWithBothRequiredApisConstructorAndDefaultConstructor
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		StubTaskWithBothRequiredApisConstructorAndDefaultConstructor(void)
		{
		}

		StubTaskWithBothRequiredApisConstructorAndDefaultConstructor(RequiredApis &&)
		{
		}

		void run(void)
		{
		}
	};

	suite<
		IsTask<StubTaskWithDefaultConstructor>,
		IsTask<StubTaskWithBooleanReturn>,
		IsNotTask<StubTaskWithRequiredApisAndDefaultConstructor<DummyRequiredApis>>,
		IsTask<StubTaskWithRequiredApisConstructor<DummyRequiredApis>>,
		IsNotTask<StubTaskWithBothRequiredApisConstructorAndDefaultConstructor<DummyRequiredApis>>> iTaskTest("ITask Test Suite", [](auto &unit)
	{
		unit.test("ITask_conceptPassedTasklikeType_expectTrueIsReturned", [](auto potentialTask)
		{
			using Task = decltype(potentialTask);
			if constexpr (Task::isTask)
				expect(typeid(typename Task::Type).name(), ITask<typename Task::Type>, equal_to(true));
		});

		unit.test("ITask_conceptPassedNonTasklikeType_expectFalseIsReturned", [](auto potentialTask)
		{
			using Task = decltype(potentialTask);
			if constexpr (!Task::isTask)
				expect(typeid(typename Task::Type).name(), ITask<typename Task::Type>, equal_to(false));
		});
	});

	suite<
		IsTask<StubTaskWithDefaultConstructor>,
		IsTask<StubTaskWithBooleanReturn>,
		IsNotTask<StubTaskWithRequiredApisAndDefaultConstructor<AppToDriverApis<DummyApi>>>,
		IsTask<StubTaskWithRequiredApisConstructor<AppToDriverApis<DummyApi>>>,
		IsNotTask<StubTaskWithRequiredApisConstructor<DummyRequiredApis>>,
		IsNotTask<StubTaskWithRequiredApisConstructor<DriverToDriverApis<DummyApi>>>,
		IsNotTask<StubTaskWithRequiredApisConstructor<DriverToKernelApis<DummyApi>>>,
		IsNotTask<StubTaskWithBothRequiredApisConstructorAndDefaultConstructor<AppToDriverApis<DummyApi>>>> iAppTaskTest("IAppTask Test Suite", [](auto &unit)
	{
		unit.test("IAppTask_conceptPassedAppTasklikeType_expectTrueIsReturned", [](auto potentialTask)
		{
			using Task = decltype(potentialTask);
			if constexpr (Task::isTask)
				expect(typeid(typename Task::Type).name(), IAppTask<typename Task::Type>, equal_to(true));
		});

		unit.test("IAppTask_conceptPassedNonAppTasklikeType_expectFalseIsReturned", [](auto potentialTask)
		{
			using Task = decltype(potentialTask);
			if constexpr (!Task::isTask)
				expect(typeid(typename Task::Type).name(), IAppTask<typename Task::Type>, equal_to(false));
		});
	});

	suite<
		IsTask<StubTaskWithDefaultConstructor>,
		IsTask<StubTaskWithBooleanReturn>,
		IsNotTask<StubTaskWithRequiredApisAndDefaultConstructor<AppToDriverApis<DummyApi>>>,
		IsTask<StubTaskWithRequiredApisConstructor<DriverToDriverApis<DummyApi>>>,
		IsTask<StubTaskWithRequiredApisConstructor<DriverToKernelApis<DummyApi>>>,
		IsNotTask<StubTaskWithRequiredApisConstructor<DummyRequiredApis>>,
		IsNotTask<StubTaskWithRequiredApisConstructor<AppToDriverApis<DummyApi>>>,
		IsNotTask<StubTaskWithBothRequiredApisConstructorAndDefaultConstructor<DriverToDriverApis<DummyApi>>>,
		IsNotTask<StubTaskWithBothRequiredApisConstructorAndDefaultConstructor<DriverToKernelApis<DummyApi>>>> iDriverTaskTest("IDriverTask Test Suite", [](auto &unit)
	{
		unit.test("IDriverTask_conceptPassedDriverTasklikeType_expectTrueIsReturned", [](auto potentialTask)
		{
			using Task = decltype(potentialTask);
			if constexpr (Task::isTask)
				expect(typeid(typename Task::Type).name(), IDriverTask<typename Task::Type>, equal_to(true));
		});

		unit.test("IDriverTask_conceptPassedNonDriverTasklikeType_expectFalseIsReturned", [](auto potentialTask)
		{
			using Task = decltype(potentialTask);
			if constexpr (!Task::isTask)
				expect(typeid(typename Task::Type).name(), IDriverTask<typename Task::Type>, equal_to(false));
		});
	});
}
