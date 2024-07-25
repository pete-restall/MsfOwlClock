#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_CRT0ENVIRONMENT_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_CRT0ENVIRONMENT_HH
#include "../../../../../ICrt0Environment.hh"
#include "linker/LinkerMemoryMap.hh"

namespace smeg::kernel::crt::crt0::mcu::microchip::pic32c::pic32cx1025sg41100
{
	class Crt0Environment
	{
	public:
		auto getLinkerMemoryMap(void) const
		{
			return linker::LinkerMemoryMap();
		}
	};

	static_assert(ICrt0Environment<Crt0Environment>, "Crt0Environment must be an ICrt0Environment");
}

#endif
