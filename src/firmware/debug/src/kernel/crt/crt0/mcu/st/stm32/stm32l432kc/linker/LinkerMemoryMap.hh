#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERMEMORYMAP_HH
#include "LinkerAppMemoryMap.hh"
#include "LinkerKernelMemoryMap.hh"

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	class LinkerMemoryMap
	{
public:
		LinkerKernelMemoryMap getLinkerMemoryMapForKernel(void) const
		{
			return LinkerKernelMemoryMap();
		}

		LinkerAppMemoryMap getLinkerMemoryMapForApp(void) const
		{
			return LinkerAppMemoryMap();
		}
	};
}

#endif
