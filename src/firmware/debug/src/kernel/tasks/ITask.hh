#ifndef __SMEG_KERNEL_TASKS_ITASK_HH
#define __SMEG_KERNEL_TASKS_ITASK_HH
#include <concepts>
#include <type_traits>
#include <utility>

#include "AppTaskApis.hh"
#include "DriverToDriverApis.hh"
#include "DriverToKernelApis.hh"

namespace smeg::kernel::tasks
{
	template <template <typename...> typename TOpenRequired, typename TClosedRequired, typename... TApis>
	struct _IsTaskRequiredApis
	{
		static constexpr bool value = false;
	};

	template <template <typename...> typename TOpenRequired, typename... TApis>
	struct _IsTaskRequiredApis<TOpenRequired, TOpenRequired<TApis...>>
	{
		static constexpr bool value = true;
	};

	template <typename TTask>
	concept _IHaveTaskConstructorRequiringAnyApiInjection =
		!std::is_default_constructible_v<TTask> &&
		requires(std::remove_cvref_t<typename TTask::RequiredApis> &apis)
		{
			{ TTask(std::move(apis)) } -> std::same_as<TTask>;
		};

	template <typename TTask, template <typename...> typename TRequiredApis>
	concept _IHaveTaskConstructorRequiringApiInjection =
		_IHaveTaskConstructorRequiringAnyApiInjection<TTask> &&
		_IsTaskRequiredApis<TRequiredApis, typename TTask::RequiredApis>::value;

	template <typename TTask>
	concept _IHaveRequiredApisTypedef = std::same_as<typename TTask::RequiredApis, typename TTask::RequiredApis>;

	template <typename TTask>
	concept _IHaveDefaultTaskConstructor =
		std::is_default_constructible_v<TTask> &&
		!_IHaveTaskConstructorRequiringAnyApiInjection<TTask> &&
		!_IHaveRequiredApisTypedef<TTask>;

	template <typename TTask>
	concept _IHaveAnyTaskConstructor = _IHaveDefaultTaskConstructor<TTask> || _IHaveTaskConstructorRequiringAnyApiInjection<TTask>;

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

	template <typename TTask>
	concept IRunAnyTask = IRunVoidTask<TTask> || IRunBooleanTask<TTask>;

	template <typename TTask, template <typename...> typename TRequiredApis>
	concept ITaskWithRequiredApis =
		!_IHaveDefaultTaskConstructor<TTask> &&
		_IHaveTaskConstructorRequiringApiInjection<TTask, TRequiredApis> &&
		IRunAnyTask<TTask>;

	template <typename TTask>
	concept ITaskWithAnyRequiredApis =
		!_IHaveDefaultTaskConstructor<TTask> &&
		_IHaveTaskConstructorRequiringAnyApiInjection<TTask> &&
		IRunAnyTask<TTask>;

	template <typename TTask, template <typename...> typename TNotRequiredApis>
	concept ITaskWithAnyRequiredApisExcept = ITaskWithAnyRequiredApis<TTask> && !ITaskWithRequiredApis<TTask, TNotRequiredApis>;

	template <typename TTask>
	concept ITaskWithoutRequiredApis =
		_IHaveDefaultTaskConstructor<TTask> &&
		!_IHaveTaskConstructorRequiringAnyApiInjection<TTask> &&
		IRunAnyTask<TTask>;

	template <typename TTask>
	concept ITask = _IHaveAnyTaskConstructor<TTask> && IRunAnyTask<TTask>;

	template <typename TTask, template <typename...> typename TRequiredApis>
	concept ITaskWithDefaultConstructorOrRequiringApiInjection = ITask<TTask> && (
		ITaskWithRequiredApis<TTask, TRequiredApis> ||
		_IHaveDefaultTaskConstructor<TTask>);

	template <typename TTask>
	concept IAppTask = ITaskWithDefaultConstructorOrRequiringApiInjection<TTask, AppTaskApis>;

	template <typename TTask>
	concept IDriverTask =
		ITaskWithDefaultConstructorOrRequiringApiInjection<TTask, DriverToDriverApis> ||
		ITaskWithDefaultConstructorOrRequiringApiInjection<TTask, DriverToKernelApis>;
}

#endif
