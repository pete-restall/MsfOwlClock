#ifndef __SMEG_KERNEL_TASKS_CONFIG_DSL_DEFAULTMEMORYSECTION_HH
#define __SMEG_KERNEL_TASKS_CONFIG_DSL_DEFAULTMEMORYSECTION_HH
#include <cstdint>

namespace smeg::kernel::tasks::config::dsl
{
	struct DefaultMemorySection
	{
	};

/*
// We need a way to figure out the minimum number of slots required for context saving.  Context saving comes in two parts:
//   - Architecture-specific (ie. registers); changes with the microcontroller but otherwise common to all tasks
//   - Configuration-specific (eg. driver state); depends on the drivers used, which differs on a per-task basis
//
// This task-specific minimum value then needs adding to each stack's NumberOfSlots.  It is also complicated by task overlays because
// each task can have different drivers; in this case we need the maximum number of slots of all of the tasks.  The number is
// calculated by 'TaskContextSwitchingConfigFrom<TConfig>::For<TTaskConfig>::NumberOfSlots'. ***** GET BY TaskConfig, BUT NEED TO FIGURE OUT HOW (IN THE BELOW SPECIALISATIONS) TO GO FROM A LIST OF TASK IDS TO A TaskConfig

The stacks will also require a 'stack control block', which, as a minimum, points to the raw array; stacks for
overlaid tasks may require a mutex and / or task index or some other supplementary information.  It might be
tempting to use a single 'Stack' class and a richly encapsulated model but it is important to separate the kernel
structures (ie. the mutex / owner for stacks used by overlaid tasks) from the raw storage as that can be corrupted
by userspace applications, which is the reason for the 'std::tuple<std::array<N>, ...> kernelStacks' approach.
*/
}

#endif
