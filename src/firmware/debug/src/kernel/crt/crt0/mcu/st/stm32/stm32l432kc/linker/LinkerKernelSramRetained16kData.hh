#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERKERNELSRAMRETAINED16KDATA_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERKERNELSRAMRETAINED16KDATA_HH
#include <cstdint>

extern "C"
{
	extern std::uint32_t __linker_sram_retained16k_data_kernel_start;
	extern std::uint32_t __linker_sram_retained16k_data_kernel_pastEnd;

	extern const std::uint32_t __linker_sram_retained16k_data_kernel_lmaStart;
	extern const std::uint32_t __linker_sram_retained16k_data_kernel_lmaPastEnd;
}

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	class LinkerKernelSramRetained16kData
	{
public:
		consteval std::uint32_t *ramBegin(void) const { return &__linker_sram_retained16k_data_kernel_start; }
		consteval std::uint32_t *ramEnd(void) const { return &__linker_sram_retained16k_data_kernel_pastEnd; }

		consteval const std::uint32_t *romBegin(void) const { return &__linker_sram_retained16k_data_kernel_lmaStart; }
		consteval const std::uint32_t *romEnd(void) const { return &__linker_sram_retained16k_data_kernel_lmaPastEnd; }
	};
}

#endif