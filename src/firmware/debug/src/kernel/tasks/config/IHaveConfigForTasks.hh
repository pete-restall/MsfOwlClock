#ifndef __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASKS_HH
#define __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASKS_HH
#include <tuple>
#include "IHaveConfigForTask.hh"

namespace smeg::kernel::tasks::config
{
	template <typename... T>
	struct IsTupleOfTaskConfigs
	{
		static constexpr bool value = false;
	};

	template <IHaveConfigForTask... T>
	struct IsTupleOfTaskConfigs<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept IHaveConfigForTasks = IsTupleOfTaskConfigs<typename T::Tasks>::value;
}

#endif