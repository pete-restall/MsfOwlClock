#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_LINKER_LINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_LINKER_LINKERMEMORYMAP_HH
#include "LinkerAppMemoryMap.hh"
#include "LinkerKernelMemoryMap.hh"

namespace smeg::kernel::crt::crt0::mcu::microchip::pic32c::pic32cx1025sg41100::linker
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
