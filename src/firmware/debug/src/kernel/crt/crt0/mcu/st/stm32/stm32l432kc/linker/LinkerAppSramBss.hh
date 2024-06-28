#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERAPPSRAMBSS_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERAPPSRAMBSS_HH
#include <cstdint>

extern "C"
{
	extern const std::uint32_t __linker_sram_bss_app_start;
	extern const std::uint32_t __linker_sram_bss_app_pastEnd;
}

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	class LinkerAppSramBss
	{
public:
		consteval const std::uint32_t *begin(void) const { return &__linker_sram_bss_app_start; }
		consteval const std::uint32_t *end(void) const { return &__linker_sram_bss_app_pastEnd; }
	};
}

#endif
