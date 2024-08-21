#ifndef __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASK_HH
#define __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASK_HH
#include <tuple>
#include "../ITask.hh"

namespace smeg::kernel::tasks::config
{
	// TODO: Really we want to test for ITask<T> but that needs a Kernel API; figure out how we test for a valid Kernel API, bearing in mind that
	// it will be different based on which drivers are requested and whether the Task is going to be executing in Kernel- or User-space...
	template <typename T>
	concept _ITasklike = IRunVoidTask<T> || IRunBooleanTask<T>;

	template <typename... T>
	class _IsTupleOfTasks
	{
	public:
		static constexpr bool value = false;
	};

	template <_ITasklike... T>
	class _IsTupleOfTasks<std::tuple<T...>>
	{
	private:
		template <_ITasklike... TNoTasks>
		struct HasOneOrMoreTasks
		{
			static constexpr bool value = false;
		};

		template <_ITasklike THead, _ITasklike... TTail>
		struct HasOneOrMoreTasks<THead, TTail...>
		{
			static constexpr bool value = true;
		};

	public:
		static constexpr bool value = HasOneOrMoreTasks<T...>::value;
	};

	template <typename T>
	concept IHaveConfigForSimpleTask = _ITasklike<typename T::Type>;

	template <typename T>
	concept IHaveConfigForOverlaidTasks = _IsTupleOfTasks<typename T::Types>::value;

	template <typename T>
	concept IHaveConfigForTask =
		(IHaveConfigForSimpleTask<T> && !IHaveConfigForOverlaidTasks<T>) ||
		(!IHaveConfigForSimpleTask<T> && IHaveConfigForOverlaidTasks<T>);
}

#endif
