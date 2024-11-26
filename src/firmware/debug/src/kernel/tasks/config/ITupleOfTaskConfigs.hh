#ifndef __SMEG_KERNEL_TASKS_CONFIG_ITUPLEOFTASKCONFIGS_HH
#define __SMEG_KERNEL_TASKS_CONFIG_ITUPLEOFTASKCONFIGS_HH
#include <array>
#include <cstddef>
#include <tuple>

#include "ITaskConfig.hh"

namespace smeg::kernel::tasks::config
{
	template <typename... T>
	struct _$IsTupleOfTaskConfigs
	{
		static constexpr bool value = false;
	};

	template <ITaskConfig... T>
	struct _$IsTupleOfTaskConfigs<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <ITaskConfig T, std::size_t N>
	struct _$IsTupleOfTaskConfigs<std::array<T, N>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept ITupleOfTaskConfigs = _$IsTupleOfTaskConfigs<T>::value;
}

#endif
