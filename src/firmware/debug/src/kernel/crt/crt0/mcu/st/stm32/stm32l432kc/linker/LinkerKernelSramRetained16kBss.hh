#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERKERNELSRAMRETAINED16KBSS_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERKERNELSRAMRETAINED16KBSS_HH
#include <cstdint>

extern "C"
{
	extern std::uint32_t __linker_sram_bss_retained16k_kernel_start;
	extern std::uint32_t __linker_sram_bss_retained16k_kernel_pastEnd;
}

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	class LinkerKernelSramRetained16kBss
	{
public:
		consteval std::uint32_t *begin(void) const { return &__linker_sram_bss_retained16k_kernel_start; }
		consteval std::uint32_t *end(void) const { return &__linker_sram_bss_retained16k_kernel_pastEnd; }
	};
}

#endif
