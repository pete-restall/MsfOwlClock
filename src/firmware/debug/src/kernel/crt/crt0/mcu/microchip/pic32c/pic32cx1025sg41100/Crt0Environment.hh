#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_CRT0ENVIRONMENT_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_CRT0ENVIRONMENT_HH
#include "../../../../../ICrt0Environment.hh"
#include "../../../../DefaultCrt0EnvironmentConfig.hh"
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

		using Config = DefaultCrt0EnvironmentConfig<1, 32>; // TODO: figure this out; (maximum number of ISR priorities * register context saving + any stack space used by individual ISRs)
	};

	static_assert(ICrt0Environment<Crt0Environment>, "Crt0Environment must be an ICrt0Environment");
}

#endif
