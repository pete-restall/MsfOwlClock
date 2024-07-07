#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERKERNELMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERKERNELMEMORYMAP_HH
#include <cstdint>
#include "../../../../../../../ChainedFinalisation.hh"
#include "../../../../../../../ChainedInitialisation.hh"
#include "../../../../../linker/LinkerBssMemorySection.hh"
#include "../../../../../linker/LinkerDataMemorySection.hh"
#include "../../../../../linker/LinkerFiniArraySection.hh"
#include "../../../../../linker/LinkerInitArraySection.hh"

extern "C"
{
	extern std::uint32_t __linker_sram_bss_kernel_start;
	extern std::uint32_t __linker_sram_bss_kernel_pastEnd;

	extern std::uint32_t __linker_sram_data_kernel_start;
	extern std::uint32_t __linker_sram_data_kernel_pastEnd;

	extern const std::uint32_t __linker_sram_data_kernel_lmaStart;
	extern const std::uint32_t __linker_sram_data_kernel_lmaPastEnd;

	extern std::uint32_t __linker_sram_bss_retained16k_kernel_start;
	extern std::uint32_t __linker_sram_bss_retained16k_kernel_pastEnd;

	extern std::uint32_t __linker_sram_retained16k_data_kernel_start;
	extern std::uint32_t __linker_sram_retained16k_data_kernel_pastEnd;

	extern const std::uint32_t __linker_sram_retained16k_data_kernel_lmaStart;
	extern const std::uint32_t __linker_sram_retained16k_data_kernel_lmaPastEnd;

	extern const smeg::kernel::crt::crt0::linker::LinkerInitArrayEntry __linker_code_flash_kernel_initArray_start;
	extern const smeg::kernel::crt::crt0::linker::LinkerInitArrayEntry __linker_code_flash_kernel_initArray_pastEnd;

	extern const smeg::kernel::crt::crt0::linker::LinkerFiniArrayEntry __linker_code_flash_kernel_finiArray_start;
	extern const smeg::kernel::crt::crt0::linker::LinkerFiniArrayEntry __linker_code_flash_kernel_finiArray_pastEnd;
}

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	using namespace smeg::kernel::crt::crt0::linker;

	class LinkerKernelMemoryMap
	{
public:
		ChainedInitialisation createInitialiserForRamSections(void) const
		{
			return ChainedInitialisation(
				LinkerBssMemorySection(&__linker_sram_bss_kernel_start, &__linker_sram_bss_kernel_pastEnd),
				LinkerBssMemorySection(&__linker_sram_bss_retained16k_kernel_start, &__linker_sram_bss_retained16k_kernel_pastEnd),
				LinkerDataMemorySection(
					&__linker_sram_data_kernel_lmaStart,
					&__linker_sram_data_kernel_lmaPastEnd,
					&__linker_sram_data_kernel_start),
				LinkerDataMemorySection(
					&__linker_sram_retained16k_data_kernel_lmaStart,
					&__linker_sram_retained16k_data_kernel_lmaPastEnd,
					&__linker_sram_retained16k_data_kernel_start));
		}

		ChainedInitialisation createInitialiserForCodeSections(void) const
		{
			return ChainedInitialisation(
				LinkerInitArraySection(&__linker_code_flash_kernel_initArray_start, &__linker_code_flash_kernel_initArray_pastEnd));
		}

		ChainedFinalisation createFinaliserForCodeSections(void) const
		{
			return ChainedFinalisation(
				LinkerFiniArraySection(&__linker_code_flash_kernel_finiArray_start, &__linker_code_flash_kernel_finiArray_pastEnd));
		}
	};
}

#endif
