#ifndef __SMEG_KERNEL_DRIVERS_IDRIVERTASK_HH
#define __SMEG_KERNEL_DRIVERS_IDRIVERTASK_HH
#include "../tasks/ITask.hh"
#include "DriverTaskApis.hh"

namespace smeg::kernel::drivers
{
	using namespace smeg::kernel::tasks;

	template <typename TTask>
	concept IDriverTask = ITaskWithDefaultConstructorOrRequiringApiInjection<TTask, DriverTaskApis>;
}

#endif
