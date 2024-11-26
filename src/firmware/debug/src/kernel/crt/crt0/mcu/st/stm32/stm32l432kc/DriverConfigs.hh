#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_DRIVERCONFIGS_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_DRIVERCONFIGS_HH
#include <tuple>

#include "../../../../../../drivers/kernel/syscall/mcu/st/stm32/stm32l432kc/SyscallDriverConfig.hh"

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	namespace drivers = smeg::kernel::drivers::kernel;

	template <typename TKernelConfigs>
	using DriverConfigs = std::tuple<
		drivers::syscall::mcu::st::stm32::stm32l432kc::SyscallDriverConfig<TKernelConfigs>>;
}

#endif
