#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_CRT0ENVIRONMENT_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_CRT0ENVIRONMENT_HH
#include "../../../../../ICrt0Environment.hh"
#include "../../../../DefaultCrt0EnvironmentConfig.hh"
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

		using Config = DefaultCrt0EnvironmentConfig<1, 32>; // TODO: figure this out; (maximum number of ISR priorities * register context saving + any stack space used by individual ISRs)
	};

	static_assert(ICrt0Environment<Crt0Environment>, "Crt0Environment must be an ICrt0Environment");
}

#endif
