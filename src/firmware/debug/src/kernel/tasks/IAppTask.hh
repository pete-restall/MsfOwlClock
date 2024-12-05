#ifndef __SMEG_KERNEL_TASKS_IAPPTASK_HH
#define __SMEG_KERNEL_TASKS_IAPPTASK_HH
#include "AppTaskApis.hh"
#include "ITask.hh"

namespace smeg::kernel::tasks
{
	template <typename TTask>
	concept IAppTask = ITaskWithDefaultConstructorOrRequiringApiInjection<TTask, AppTaskApis>;
}

#endif
