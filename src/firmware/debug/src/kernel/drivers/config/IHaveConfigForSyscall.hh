#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORSYSCALL_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORSYSCALL_HH
#include "../../IHandleSyscall.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T>
	concept IHaveConfigForSyscall = IHandleSyscallWithAnyArg<typename T::Handler>;
}

#endif
