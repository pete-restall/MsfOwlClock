#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_ITUPLEOFPROVIDEDSYSCALLCONFIGS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_ITUPLEOFPROVIDEDSYSCALLCONFIGS_HH
#include <tuple>

#include "IProvidedSyscallConfig.hh"

namespace smeg::kernel::drivers::config
{
	template <typename... T>
	struct _$IsTupleOfProvidedSyscallConfigs
	{
		static constexpr bool value = false;
	};

	template <IProvidedSyscallConfig... T>
	struct _$IsTupleOfProvidedSyscallConfigs<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept ITupleOfProvidedSyscallConfigs = _$IsTupleOfProvidedSyscallConfigs<T>::value;
}

#endif
