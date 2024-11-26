#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IPROVIDEDSYSCALLCONFIG_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IPROVIDEDSYSCALLCONFIG_HH
#include "../../IHandleSyscall.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T>
	concept IProvidedSyscallConfig = IHandleSyscallWithAnyArg<typename T::Handler>;
}

#endif
