#ifndef __SMEG_KERNEL_TASKS_ITASK_HH
#define __SMEG_KERNEL_TASKS_ITASK_HH
#include <concepts>
#include <type_traits>
#include "AppToDriverApis.hh"
#include "DriverToDriverApis.hh"
#include "DriverToKernelApis.hh"

namespace smeg::kernel::tasks
{
	template <typename... T>
	struct _IsTaskRequiredApis { static constexpr bool value = false; };

	template <typename... T>
	struct _IsTaskRequiredApis<AppToDriverApis<T...>> { static constexpr bool value = true; };

	template <typename... T>
	struct _IsTaskRequiredApis<DriverToDriverApis<T...>> { static constexpr bool value = true; };

	template <typename... T>
	struct _IsTaskRequiredApis<DriverToKernelApis<T...>> { static constexpr bool value = true; };

	template <typename TTask, typename TRequiredApis>
	concept IHaveTaskConstructorRequiringApiInjection =
		std::same_as<std::remove_cvref_t<TRequiredApis>, typename TTask::RequiredApis> &&
		std::constructible_from<TTask, std::remove_cvref_t<TRequiredApis> &&>;

	template <typename TTask>
	concept IHaveTaskConstructorRequiringAnyApiInjection =
		_IsTaskRequiredApis<std::remove_cvref_t<typename TTask::RequiredApis>>::value &&
		IHaveTaskConstructorRequiringApiInjection<TTask, typename TTask::RequiredApis>;

	template <typename TTask>
	concept IHaveDefaultTaskConstructor = std::constructible_from<TTask>;

	template <typename TTask>
	concept IHaveAnyTaskConstructor = IHaveDefaultTaskConstructor<TTask> || IHaveTaskConstructorRequiringAnyApiInjection<TTask>;

	template <typename TTask>
	concept IRunVoidTask = requires(TTask &task)
	{
		{ task.run() } -> std::same_as<void>;
	};

	template <typename TTask>
	concept IRunBooleanTask = requires(TTask &task)
	{
		{ task.run() } -> std::convertible_to<bool>;
	};

	template <typename TTask, typename TRequiredApis>
	concept ITaskRequiringApiInjection = IHaveTaskConstructorRequiringApiInjection<TTask, TRequiredApis> && (IRunVoidTask<TTask> || IRunBooleanTask<TTask>);

	template <typename TTask>
	concept ITask = IHaveAnyTaskConstructor<TTask> && (IRunVoidTask<TTask> || IRunBooleanTask<TTask>);
}

#endif
