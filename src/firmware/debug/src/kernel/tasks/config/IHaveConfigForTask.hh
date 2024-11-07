#ifndef __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASK_HH
#define __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASK_HH
#include <array>
#include <concepts>
#include <cstdint>
#include <tuple>
#include "../ITask.hh"

namespace smeg::kernel::tasks::config
{
	template <typename... T>
	class _IsTupleOfTasks
	{
	public:
		static constexpr bool value = false;
	};

	template <ITask T, std::size_t N>
	class _IsTupleOfTasks<std::array<T, N>>
	{
	public:
		static constexpr bool value = N > 0;
	};

	template <ITask... T>
	class _IsTupleOfTasks<std::tuple<T...>>
	{
	private:
		template <ITask... TNoTasks>
		struct HasOneOrMoreTasks
		{
			static constexpr bool value = false;
		};

		template <ITask THead, ITask... TTail>
		struct HasOneOrMoreTasks<THead, TTail...>
		{
			static constexpr bool value = true;
		};

	public:
		static constexpr bool value = HasOneOrMoreTasks<T...>::value;
	};

	template <typename T>
	concept IHaveConfigForSimpleTask = ITask<typename T::Type>;

	template <typename T>
	concept IHaveConfigForOverlaidTasks = _IsTupleOfTasks<typename T::Types>::value;

	template <typename T>
	concept IHaveConfigForTask =
		(IHaveConfigForSimpleTask<T> && !IHaveConfigForOverlaidTasks<T>) ||
		(!IHaveConfigForSimpleTask<T> && IHaveConfigForOverlaidTasks<T>);
}

#endif
