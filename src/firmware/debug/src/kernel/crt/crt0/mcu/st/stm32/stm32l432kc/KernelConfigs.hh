#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_KERNELCONFIGS_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_KERNELCONFIGS_HH
#include <tuple>

#include "../../../../../../../kernel-config.hh"
#include "../../../../../../config/PrivateKernelConfig.hh"
#include "Crt0KernelConfig.hh"

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	using namespace smeg::config;
	using namespace smeg::kernel::config;

	struct KernelConfigs
	{
		using AsTuple = std::tuple<Crt0KernelConfig<KernelConfigs>, PrivateKernelConfig, KernelConfig>;
	};
}

#endif
