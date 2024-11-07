#ifndef __SMEG_KERNEL_TASKS_DEFAULTTASKFACTORY_HH
#define __SMEG_KERNEL_TASKS_DEFAULTTASKFACTORY_HH
#include "ITask.hh"

namespace smeg::kernel::tasks
{
	template <ITask TTask>
	class DefaultTaskFactory
	{
	public:
		static constexpr TTask createTask(void)
		{
			if constexpr (IHaveTaskConstructorRequiringAnyApiInjection<TTask>)
				return TTask((typename TTask::RequiredApis()));
			else
				return TTask();
		}
	};
}

#endif
