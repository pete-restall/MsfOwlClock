#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_CRT0ENVIRONMENT_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_CRT0ENVIRONMENT_HH
#include "../../../../../ICrt0Environment.hh"
#include "../../../../../NoBootloader.hh" // TODO: This is temporary; bootloader needs to be derived from KernelConfig (if present) and probably needs MCU-specific injections - default to a sensible MCU-specific default if not specified explicitly in KernelConfig; there's always NoBootloader but it's not ideal
#include "../../../../IsrStackMemorySection.hh"
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

		auto getBootloader(void) const
		{
			// TODO: This is temporary; bootloader needs to be derived from KernelConfig (if present) and probably needs MCU-specific injections - default to a sensible MCU-specific default if not specified explicitly in KernelConfig; there's always NoBootloader but it's not ideal
			// Note that the bootloader type should not be specified directly in the config, otherwise the dependency arrows point the wrong way; use some tokens that can be examined at compile-time (constexpr, string literals, dummy classes in a 'dsl' namespace, whatever)
			return NoBootloader();
		}
	};

	static_assert(ICrt0Environment<Crt0Environment>, "Crt0Environment must be an ICrt0Environment");
}

#endif
