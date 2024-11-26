#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ST_STM32_STM32L432KC_SYSCALLAPI_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ST_STM32_STM32L432KC_SYSCALLAPI_HH
#include "kernel/config/IHaveTupleOfKernelConfigs.hh"

#include "../../../../SyscallFor.hh"
#include "../../../arm/cortex/m4/DefaultSyscallApi.hh"
#include "../../../arm/cortex/m4/SyscallPrimitive.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::st::stm32::stm32l432kc
{
	using namespace smeg::kernel::config;
	using namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4;

	template <IHaveTupleOfKernelConfigs TKernelConfigs>
	using SyscallApi = DefaultSyscallApi<SyscallPrimitive, SyscallFor<TKernelConfigs>>;
}

#endif
