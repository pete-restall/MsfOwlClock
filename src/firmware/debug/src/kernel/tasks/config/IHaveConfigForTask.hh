#ifndef __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASK_HH
#define __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASK_HH
#include <array>
#include <concepts>
#include <cstddef>
#include <tuple>

#include "../ITask.hh"
#include "IHaveConfigForTaskStack.hh"

namespace smeg::kernel::tasks::config
{
	template <typename T>
	concept IHaveConfigForSimpleTask = ITask<typename T::Type> && IHaveConfigForTaskStack<typename T::Stack>;

	template <typename T>
	concept IHaveConfigForOverlaidTask = ITask<typename T::Type>;

	template <typename... T>
	struct _IsTupleOfTasks
	{
		static constexpr bool value = false;
	};

	template <ITask T, std::size_t N>
	struct _IsTupleOfTasks<std::array<T, N>>
	{
		static constexpr bool value = N > 0;
	};

	template <ITask... T>
	struct _IsTupleOfTasks<std::tuple<T...>>
	{
		static constexpr bool value = std::tuple_size_v<std::tuple<T...>> > 0;
	};

	template <typename T>
	concept _IHaveTypes = std::tuple_size_v<typename T::Types> > 0;

	template <typename T>
	struct _ContainsTupleOfTasks
	{
		static constexpr bool value = false;
	};

	template <_IHaveTypes T>
	struct _ContainsTupleOfTasks<T>
	{
		static constexpr bool value = _IsTupleOfTasks<typename T::Types>::value;
	};

	template <typename... T>
	struct _IsTupleOfOverlaidTaskConfigs
	{
		static constexpr bool value = false;
	};

	template <IHaveConfigForOverlaidTask T, std::size_t N>
	struct _IsTupleOfOverlaidTaskConfigs<std::array<T, N>>
	{
		static constexpr bool value = N > 0;
	};

	template <IHaveConfigForOverlaidTask... T>
	struct _IsTupleOfOverlaidTaskConfigs<std::tuple<T...>>
	{
		static constexpr bool value = std::tuple_size_v<std::tuple<T...>> > 0;
	};

	template <typename T>
	concept _IHaveConfigs = std::tuple_size_v<typename T::Configs> > 0;

	template <typename T>
	struct _ContainsTupleOfOverlaidTaskConfigs
	{
		static constexpr bool value = false;
	};

	template <_IHaveConfigs T>
	struct _ContainsTupleOfOverlaidTaskConfigs<T>
	{
		static constexpr bool value = _IsTupleOfOverlaidTaskConfigs<typename T::Configs>::value;
	};

	template <typename T>
	concept IHaveConfigForSimpleOverlaidTasks =
		IHaveConfigForTaskStack<typename T::Stack> &&
		_ContainsTupleOfTasks<T>::value &&
		!_ContainsTupleOfOverlaidTaskConfigs<T>::value;

	template <typename T>
	concept IHaveConfigForConfiguredOverlaidTasks =
		IHaveConfigForTaskStack<typename T::Stack> &&
			!_ContainsTupleOfTasks<T>::value &&
			_ContainsTupleOfOverlaidTaskConfigs<T>::value;

	template <typename T>
	concept IHaveConfigForOverlaidTasks = IHaveConfigForSimpleOverlaidTasks<T> || IHaveConfigForConfiguredOverlaidTasks<T>;

	template <typename T>
	concept IHaveConfigForTask =
		(IHaveConfigForSimpleTask<T> && !IHaveConfigForOverlaidTasks<T>) ||
		(!IHaveConfigForSimpleTask<T> && IHaveConfigForOverlaidTasks<T>);
}

#endif
