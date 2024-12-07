#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_DRIVERTOKERNEL_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_DRIVERTOKERNEL_HH
#include "kernel/mcu-defs.hh"

#include SMEG_MCU_CONFIG_HEADER_FOR_DRIVER_IMPLEMENTATIONS
#include SMEG_MCU_RELATIVE_HEADER(SyscallApi.hh)

namespace smeg::kernel::drivers::kernel::syscall
{
	// TODO: This header will need to be renamed.  Something like 'app.hh', to match the new 'AppApis' and 'IAppApi' convention.
	using SyscallApi = SMEG_MCU_RELATIVE_NAMESPACE::SyscallApi<SMEG_MCU_KERNEL_CONFIGS_FOR_DRIVER_IMPLEMENTATIONS>;
}

#endif
