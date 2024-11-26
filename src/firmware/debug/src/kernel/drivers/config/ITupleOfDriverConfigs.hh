#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_ITUPLEOFDRIVERCONFIGS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_ITUPLEOFDRIVERCONFIGS_HH
#include <tuple>

#include "IDriverConfig.hh"

namespace smeg::kernel::drivers::config
{
	template <typename... T>
	struct _$IsTupleOfDriverConfigs
	{
		static constexpr bool value = false;
	};

	template <IDriverConfig... T>
	struct _$IsTupleOfDriverConfigs<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept ITupleOfDriverConfigs = _$IsTupleOfDriverConfigs<T>::value;
}

#endif
