#ifndef __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASKS_HH
#define __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASKS_HH
#include "ITupleOfTaskConfigs.hh"

namespace smeg::kernel::tasks::config
{
	template <typename T>
	concept IHaveConfigForTasks = ITupleOfTaskConfigs<typename T::Tasks>;
}

#endif
