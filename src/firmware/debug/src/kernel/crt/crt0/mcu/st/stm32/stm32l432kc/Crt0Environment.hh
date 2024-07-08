#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_CRT0ENVIRONMENT_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_CRT0ENVIRONMENT_HH
#include "../../../../../ICrt0Environment.hh"
#include "linker/LinkerMemoryMap.hh"

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
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
