#ifndef __SMEG_KERNEL_TASKS_DEFAULTTASKFACTORY_HH
#define __SMEG_KERNEL_TASKS_DEFAULTTASKFACTORY_HH
#include "ITask.hh"

namespace smeg::kernel::tasks
{
	template <typename TTask, typename TKernelApi = void>
	class DefaultTaskFactory
	{
	public:
		static_assert(ITask<TTask, TKernelApi>, "TTask and TKernelApi do not match the ITask concept");

		static constexpr TTask createTask(void)
		{
			if constexpr (IHaveKernelApiTaskConstructor<TTask, TKernelApi>)
				return TTask((TKernelApi()));
			else
				return TTask();
		}
	};
}

#endif
