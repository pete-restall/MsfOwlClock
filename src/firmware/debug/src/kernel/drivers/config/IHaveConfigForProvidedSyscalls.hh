#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORPROVIDEDSYSCALLS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORPROVIDEDSYSCALLS_HH
#include "ITupleOfProvidedSyscallConfigs.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T>
	concept IHaveConfigForProvidedSyscalls = ITupleOfProvidedSyscallConfigs<typename T::ProvidedSyscalls>;
}

#endif
