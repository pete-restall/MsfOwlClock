#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_DEFAULTSYSCALLAPI_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_DEFAULTSYSCALLAPI_HH
#include "kernel/ISyscall.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4
{
	template <typename TSyscallPrimitive, template <typename> typename TSyscallFor>
	struct DefaultSyscallApi
	{
		// TODO: Syscall API needs to be defined.  Probably something along these lines:
		// template <ISyscall<TSyscallFor> TSyscall>
		// void invoke(TSyscall &syscall) -->
		//   TSyscallPrimitive::invoke(syscall)
	};
}

#endif
