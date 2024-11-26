#ifndef __SMEG_KERNEL_TASKS_CONFIG_ITASKCONFIG_HH
#define __SMEG_KERNEL_TASKS_CONFIG_ITASKCONFIG_HH
#include <array>
#include <concepts>
#include <cstddef>
#include <tuple>

#include "../ITask.hh"
#include "IHaveConfigForTaskStack.hh"

namespace smeg::kernel::tasks::config
{
	template <typename T>
	concept ISimpleTaskConfig = ITask<typename T::Type> && IHaveConfigForTaskStack<typename T::Stack>;

	template <typename T>
	concept IOverlaidTaskConfig = ITask<typename T::Type>;

	template <typename... T>
	struct _$IsTupleOfTasks
	{
		static constexpr bool value = false;
	};

	template <ITask T, std::size_t N>
	struct _$IsTupleOfTasks<std::array<T, N>>
	{
		static constexpr bool value = N > 0;
	};

	template <ITask... T>
	struct _$IsTupleOfTasks<std::tuple<T...>>
	{
		static constexpr bool value = std::tuple_size_v<std::tuple<T...>> > 0;
	};

	template <typename T>
	concept _$IHaveTypes = std::tuple_size_v<typename T::Types> > 0;

	template <typename T>
	struct _$ContainsTupleOfTasks
	{
		static constexpr bool value = false;
	};

	template <_$IHaveTypes T>
	struct _$ContainsTupleOfTasks<T>
	{
		static constexpr bool value = _$IsTupleOfTasks<typename T::Types>::value;
	};

	template <typename... T>
	struct _$IsTupleOfOverlaidTaskConfigs
	{
		static constexpr bool value = false;
	};

	template <IOverlaidTaskConfig T, std::size_t N>
	struct _$IsTupleOfOverlaidTaskConfigs<std::array<T, N>>
	{
		static constexpr bool value = N > 0;
	};

	template <IOverlaidTaskConfig... T>
	struct _$IsTupleOfOverlaidTaskConfigs<std::tuple<T...>>
	{
		static constexpr bool value = std::tuple_size_v<std::tuple<T...>> > 0;
	};

	template <typename T>
	concept _$IHaveConfigs = std::tuple_size_v<typename T::Configs> > 0;

	template <typename T>
	struct _$ContainsTupleOfOverlaidTaskConfigs
	{
		static constexpr bool value = false;
	};

	template <_$IHaveConfigs T>
	struct _$ContainsTupleOfOverlaidTaskConfigs<T>
	{
		static constexpr bool value = _$IsTupleOfOverlaidTaskConfigs<typename T::Configs>::value;
	};

	template <typename T>
	concept ISimpleOverlaidTasksConfig =
		IHaveConfigForTaskStack<typename T::Stack> &&
		_$ContainsTupleOfTasks<T>::value &&
		!_$ContainsTupleOfOverlaidTaskConfigs<T>::value;

	template <typename T>
	concept IConfiguredOverlaidTasksConfig =
		IHaveConfigForTaskStack<typename T::Stack> &&
			!_$ContainsTupleOfTasks<T>::value &&
			_$ContainsTupleOfOverlaidTaskConfigs<T>::value;

	template <typename T>
	concept IOverlaidTasksConfig = ISimpleOverlaidTasksConfig<T> || IConfiguredOverlaidTasksConfig<T>;

	template <typename T>
	concept ITaskConfig =
		(ISimpleTaskConfig<T> && !IOverlaidTasksConfig<T>) ||
		(!ISimpleTaskConfig<T> && IOverlaidTasksConfig<T>);
}

#endif
