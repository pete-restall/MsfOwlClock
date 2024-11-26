#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_SYSCALLAPI_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_SYSCALLAPI_HH
#include "kernel/config/IHaveTupleOfKernelConfigs.hh"

#include "../../../../SyscallFor.hh"
#include "../../../arm/cortex/m4/DefaultSyscallApi.hh"
#include "../../../arm/cortex/m4/SyscallPrimitive.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::microchip::pic32c::pic32cx1025sg41100
{
	using namespace smeg::kernel::config;
	using namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4;

	template <IHaveTupleOfKernelConfigs TKernelConfigs>
	using SyscallApi = DefaultSyscallApi<SyscallPrimitive, SyscallFor<TKernelConfigs>>;
}

#endif
