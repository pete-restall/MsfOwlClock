#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_CRT0KERNELCONFIG_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_CRT0KERNELCONFIG_HH
#include "../../../../DefaultCrt0KernelConfig.hh"
#include "../../../../IsrStackMemorySection.hh"
#include "DriverConfigs.hh"

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	template <typename TKernelConfigs>
	using Crt0KernelConfig = DefaultCrt0KernelConfig<1, 32, IsrStackMemorySection, DriverConfigs<TKernelConfigs>>; // TODO: figure this out; (maximum number of ISR priorities * register context saving + any stack space used by individual ISRs)
}

#endif
