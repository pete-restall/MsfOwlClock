#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ST_STM32_STM32L432KC_SYSCALLDRIVERCONFIG_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ST_STM32_STM32L432KC_SYSCALLDRIVERCONFIG_HH
#include "../../../arm/cortex/m4/DefaultSyscallDriverConfig.hh"
#include "../../../../SyscallFor.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::st::stm32::stm32l432kc
{
	using namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4;

	template <typename TKernelConfigs>
	using SyscallDriverConfig = DefaultSyscallDriverConfig<TKernelConfigs>;
}

#endif
