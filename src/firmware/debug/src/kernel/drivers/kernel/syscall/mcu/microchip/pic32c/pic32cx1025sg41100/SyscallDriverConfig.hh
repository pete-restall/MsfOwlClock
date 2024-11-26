#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_SYSCALLDRIVERCONFIG_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_SYSCALLDRIVERCONFIG_HH
#include "../../../arm/cortex/m4/DefaultSyscallDriverConfig.hh"
#include "../../../../SyscallFor.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::microchip::pic32c::pic32cx1025sg41100
{
	using namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4;

	template <typename TKernelConfigs>
	using SyscallDriverConfig = DefaultSyscallDriverConfig<TKernelConfigs, SyscallFor>;
}

#endif
