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
	struct _$DummyRequiredApis
	{
	};

	using DummyRequiredApis = _$DummyRequiredApis<>;

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
}
