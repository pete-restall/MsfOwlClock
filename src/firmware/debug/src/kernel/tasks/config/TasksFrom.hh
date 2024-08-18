#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSFROM_HH
#include <tuple>
#include "IHaveConfigForTasks.hh"

namespace smeg::kernel::tasks::config
{
	template <IHaveConfigForTasks TConfig>
	class TasksFrom
	{
	private:
		template <typename T>
		struct AsTuple;

		template <IHaveConfigForSimpleTask T>
		struct AsTuple<T>
		{
			using Types = std::tuple<typename T::Type>;
		};

		template <IHaveConfigForOverlaidTasks T>
		struct AsTuple<T>
		{
			using Types = T::Types;
		};

		template <typename... TTaskConfigs>
		static constexpr auto tasksFrom(std::tuple<TTaskConfigs...>)
		{
			return std::tuple_cat((typename AsTuple<TTaskConfigs>::Types{}) ...);
		}

	public:
		using Types = decltype(tasksFrom(typename TConfig::Tasks{}));
	};
}

#endif
