#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_CRT0KERNELCONFIG_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_CRT0KERNELCONFIG_HH
#include "../../../../DefaultCrt0KernelConfig.hh"
#include "../../../../IsrStackMemorySection.hh"
#include "DriverConfigs.hh"
#include "McuCoreTraits.hh"

namespace smeg::kernel::crt::crt0::mcu::microchip::pic32c::pic32cx1025sg41100
{
	template <typename TKernelConfigs>
	using Crt0KernelConfig = DefaultCrt0KernelConfig<
		McuCoreTraits,
		32,
		IsrStackMemorySection,
		DriverConfigs<TKernelConfigs>>; // TODO: figure this out; (maximum number of ISR priorities * register context saving + any stack space used by individual ISRs)
}

#endif
