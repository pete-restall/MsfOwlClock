#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_KERNELCONFIGS_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_KERNELCONFIGS_HH
#include <tuple>

#include "../../../../../../../kernel-config.hh"
#include "../../../../../../config/PrivateKernelConfig.hh"
#include "Crt0KernelConfig.hh"

namespace smeg::kernel::crt::crt0::mcu::microchip::pic32c::pic32cx1025sg41100
{
	using namespace smeg::config;
	using namespace smeg::kernel::config;

	struct KernelConfigs
	{
		using AsTuple = std::tuple<Crt0KernelConfig<KernelConfigs>, PrivateKernelConfig, KernelConfig>;
	};
}

#endif
