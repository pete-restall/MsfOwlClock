#ifndef __SMEG_KERNEL_TASKS_ITASK_HH
#define __SMEG_KERNEL_TASKS_ITASK_HH
#include <concepts>
#include <type_traits>
#include <utility>

namespace smeg::kernel::tasks
{
	// TODO: These can be generalised to leverage the new IHaveRequiredApis concept, but we need to put some tests around it, too...
	template <template <typename...> typename TOpenRequired, typename TClosedRequired, typename... TApis>
	struct _$IsTaskRequiredApis
	{
		static constexpr bool value = false;
	};

	template <template <typename...> typename TOpenRequired, typename... TApis>
	struct _$IsTaskRequiredApis<TOpenRequired, TOpenRequired<TApis...>>
	{
		static constexpr bool value = true;
	};

	template <typename TTask>
	concept _$IHaveTaskConstructorRequiringAnyApiInjection =
		!std::is_default_constructible_v<TTask> &&
		requires(std::remove_cvref_t<typename TTask::RequiredApis> &apis)
		{
			{ TTask(std::move(apis)) } -> std::same_as<TTask>;
		};

	template <typename TTask, template <typename...> typename TRequiredApis>
	concept _$IHaveTaskConstructorRequiringApiInjection =
		_$IHaveTaskConstructorRequiringAnyApiInjection<TTask> &&
		_$IsTaskRequiredApis<TRequiredApis, typename TTask::RequiredApis>::value;

	template <typename TTask>
	concept _$IHaveRequiredApisTypedef = std::same_as<typename TTask::RequiredApis, typename TTask::RequiredApis>;

	template <typename TTask>
	concept _$IHaveDefaultTaskConstructor =
		std::is_default_constructible_v<TTask> &&
		!_$IHaveTaskConstructorRequiringAnyApiInjection<TTask> &&
		!_$IHaveRequiredApisTypedef<TTask>;

	template <typename TTask>
	concept _$IHaveAnyTaskConstructor = _$IHaveDefaultTaskConstructor<TTask> || _$IHaveTaskConstructorRequiringAnyApiInjection<TTask>;

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
		!_$IHaveDefaultTaskConstructor<TTask> &&
		_$IHaveTaskConstructorRequiringApiInjection<TTask, TRequiredApis> &&
		IRunAnyTask<TTask>;

	template <typename TTask>
	concept ITaskWithAnyRequiredApis =
		!_$IHaveDefaultTaskConstructor<TTask> &&
		_$IHaveTaskConstructorRequiringAnyApiInjection<TTask> &&
		IRunAnyTask<TTask>;

	template <typename TTask, template <typename...> typename TNotRequiredApis>
	concept ITaskWithAnyRequiredApisExcept = ITaskWithAnyRequiredApis<TTask> && !ITaskWithRequiredApis<TTask, TNotRequiredApis>;

	template <typename TTask>
	concept ITaskWithoutRequiredApis =
		_$IHaveDefaultTaskConstructor<TTask> &&
		!_$IHaveTaskConstructorRequiringAnyApiInjection<TTask> &&
		IRunAnyTask<TTask>;

	template <typename TTask>
	concept ITask = _$IHaveAnyTaskConstructor<TTask> && IRunAnyTask<TTask>;

	template <typename TTask, template <typename...> typename TRequiredApis>
	concept ITaskWithDefaultConstructorOrRequiringApiInjection = ITask<TTask> && (
		ITaskWithRequiredApis<TTask, TRequiredApis> ||
		_$IHaveDefaultTaskConstructor<TTask>);
}

#endif
