#ifndef __SMEG_KERNEL_TASKS_ITASK_HH
#define __SMEG_KERNEL_TASKS_ITASK_HH
#include <concepts>

namespace smeg::kernel::tasks
{
	template <typename TTask, typename TKernelApi>
	concept IHaveKernelApiTaskConstructor = requires { { TTask((TKernelApi())) } -> std::same_as<TTask>; };

	template <typename TTask>
	concept IHaveDefaultTaskConstructor = requires { { TTask() } -> std::same_as<TTask>; };

	template <typename TTask, typename TKernelApi>
	concept IHaveTaskConstructor = IHaveDefaultTaskConstructor<TTask> || IHaveKernelApiTaskConstructor<TTask, TKernelApi>;

	template <typename TTask>
	concept IRunVoidTasks = requires(TTask &task)
	{
		{ task.run() } -> std::same_as<void>;
	};

	template <typename TTask>
	concept IRunBooleanTasks = requires(TTask &task)
	{
		{ task.run() } -> std::convertible_to<bool>;
	};

	template <typename TTask, typename TKernelApi>
	concept ITask = IHaveTaskConstructor<TTask, TKernelApi> && (IRunVoidTasks<TTask> || IRunBooleanTasks<TTask>);
}

#endif
