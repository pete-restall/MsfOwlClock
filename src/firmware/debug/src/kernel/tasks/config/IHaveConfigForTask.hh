#ifndef __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASK_HH
#define __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASK_HH
#include <tuple>
#include "../ITask.hh"

namespace smeg::kernel::tasks::config
{
	// TODO: Really we want to test for ITask<T> but that needs a Kernel API; figure out how we test for a valid Kernel API, bearing in mind that
	// it will be different based on which drivers are requested and whether the Task is going to be executing in Kernel- or User-space...
	template <typename T>
	concept ITasklike = IRunVoidTask<T> || IRunBooleanTask<T>;

	template <typename... T>
	struct IsTupleOfTasks
	{
		static constexpr bool value = false;
	};

	template <ITasklike... T>
	struct IsTupleOfTasks<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept IHaveConfigForSimpleTask = ITasklike<typename T::Type>;

	template <typename T>
	concept IHaveConfigForOverlaidTasks = std::tuple_size_v<typename T::Types> > 0 && IsTupleOfTasks<typename T::Types>::value;

	template <typename T>
	concept IHaveConfigForTask = IHaveConfigForSimpleTask<T> || IHaveConfigForOverlaidTasks<T>;
}

#endif
