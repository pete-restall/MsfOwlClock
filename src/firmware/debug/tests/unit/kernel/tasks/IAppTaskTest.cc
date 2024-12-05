#include <stdexcept>
#include <type_traits>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/AppTaskApis.hh"
#include "kernel/tasks/IAppTask.hh"

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

	template <typename... TApis>
	class UnknownApis
	{
		using AsTuple = std::tuple<TApis...>;

		template <typename TConfig, template <typename, typename...> typename TApiFactory>
		UnknownApis(TApiFactory<TConfig, TApis...>)
		{
		}

		template <typename TApi>
		auto &get(void)
		{
			throw std::runtime_error("The dummy UnknownApis.get() should never be called");
		}
	};

	suite<
		IsTask<StubTaskWithDefaultConstructor>,
		IsTask<StubTaskWithBooleanReturn>,
		IsNotTask<StubTaskWithRequiredApisAndDefaultConstructor<AppTaskApis<DummyApi>>>,
		IsTask<StubTaskWithRequiredApisConstructor<AppTaskApis<DummyApi>>>,
		IsNotTask<StubTaskWithRequiredApisConstructor<DummyRequiredApis>>,
		IsNotTask<StubTaskWithRequiredApisConstructor<UnknownApis<DummyApi>>>,
		IsNotTask<StubTaskWithBothRequiredApisConstructorAndDefaultConstructor<AppTaskApis<DummyApi>>>> iAppTaskTest("IAppTask Test Suite", [](auto &unit)
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
}
