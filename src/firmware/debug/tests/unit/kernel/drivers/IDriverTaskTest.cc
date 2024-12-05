#include <stdexcept>
#include <type_traits>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/DriverTaskApis.hh"
#include "kernel/drivers/IDriverTask.hh"

#include "../tasks/TaskTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel::drivers;
using namespace smeg::tests::unit::kernel::tasks;

namespace smeg::tests::unit::kernel::drivers
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
		IsNotTask<StubTaskWithRequiredApisAndDefaultConstructor<DriverTaskApis<DummyApi>>>,
		IsTask<StubTaskWithRequiredApisConstructor<DriverTaskApis<DummyApi>>>,
		IsNotTask<StubTaskWithRequiredApisConstructor<DummyRequiredApis>>,
		IsNotTask<StubTaskWithRequiredApisConstructor<UnknownApis<DummyApi>>>,
		IsNotTask<StubTaskWithBothRequiredApisConstructorAndDefaultConstructor<DriverTaskApis<DummyApi>>>> iDriverTaskTest("IDriverTask Test Suite", [](auto &unit)
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
