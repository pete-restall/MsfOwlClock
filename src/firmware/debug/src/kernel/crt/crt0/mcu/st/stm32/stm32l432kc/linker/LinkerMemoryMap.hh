#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERMEMORYMAP_HH
#include "LinkerAppMemoryMap.hh"
#include "LinkerKernelMemoryMap.hh"

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	class LinkerMemoryMap // TODO: This could (should ?) be made into a template (ILinkerMemoryMap constraint) to avoid un-necessary code in the MCU-specific library; the MCU-specific library should be as lightweight as possible to make it quick / easy to add new MCUs, plus the bootstrapping stuff is largely untestable without an emulator or manual tests
	{
public:
		LinkerKernelMemoryMap createLinkerMemoryMapForKernel(void) const
		{
			return LinkerKernelMemoryMap();
		}

		LinkerAppMemoryMap createLinkerMemoryMapForApp(void) const
		{
			return LinkerAppMemoryMap();
		}
	};
}

#endif
