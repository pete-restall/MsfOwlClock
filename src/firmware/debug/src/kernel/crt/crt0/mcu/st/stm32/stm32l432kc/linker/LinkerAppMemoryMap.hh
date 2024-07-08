#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERAPPMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERAPPMEMORYMAP_HH
#include <cstdint>
#include "../../../../../../../ChainedFinalisation.hh"
#include "../../../../../../../ChainedInitialisation.hh"
#include "../../../../../linker/LinkerBssMemorySection.hh"
#include "../../../../../linker/LinkerDataMemorySection.hh"
#include "../../../../../linker/LinkerFiniArraySection.hh"
#include "../../../../../linker/LinkerInitArraySection.hh"

extern "C"
{
	extern std::uint32_t __linker_sram_bss_app_start[];
	extern std::uint32_t __linker_sram_bss_app_pastEnd;

	extern std::uint32_t __linker_sram_data_app_start[];
	extern std::uint32_t __linker_sram_data_app_pastEnd;

	extern const std::uint32_t __linker_sram_data_app_lmaStart[];
	extern const std::uint32_t __linker_sram_data_app_lmaPastEnd;

	extern std::uint32_t __linker_sram_bss_retained16k_app_start[];
	extern std::uint32_t __linker_sram_bss_retained16k_app_pastEnd;

	extern std::uint32_t __linker_sram_data_retained16k_app_start[];
	extern std::uint32_t __linker_sram_data_retained16k_app_pastEnd;

	extern const std::uint32_t __linker_sram_data_retained16k_app_lmaStart[];
	extern const std::uint32_t __linker_sram_data_retained16k_app_lmaPastEnd;

	extern const smeg::kernel::crt::crt0::linker::LinkerInitArrayEntry __linker_code_flash_app_initArray_start[];
	extern const smeg::kernel::crt::crt0::linker::LinkerInitArrayEntry __linker_code_flash_app_initArray_pastEnd;

	extern const smeg::kernel::crt::crt0::linker::LinkerFiniArrayEntry __linker_code_flash_app_finiArray_start[];
	extern const smeg::kernel::crt::crt0::linker::LinkerFiniArrayEntry __linker_code_flash_app_finiArray_pastEnd;
}

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	using namespace smeg::kernel::crt::crt0::linker;

	class LinkerAppMemoryMap
	{
public:
		auto getInitialiserForRamSections(void) const
		{
			return ChainedInitialisation(
				LinkerBssMemorySection(__linker_sram_bss_app_start, &__linker_sram_bss_app_pastEnd),
				LinkerBssMemorySection(__linker_sram_bss_retained16k_app_start, &__linker_sram_bss_retained16k_app_pastEnd),
				LinkerDataMemorySection(
					__linker_sram_data_app_lmaStart,
					&__linker_sram_data_app_lmaPastEnd,
					__linker_sram_data_app_start),
				LinkerDataMemorySection(
					__linker_sram_data_retained16k_app_lmaStart,
					&__linker_sram_data_retained16k_app_lmaPastEnd,
					__linker_sram_data_retained16k_app_start));
		}

		auto getInitialiserForCodeSections(void) const
		{
			return ChainedInitialisation(
				LinkerInitArraySection(__linker_code_flash_app_initArray_start, &__linker_code_flash_app_initArray_pastEnd));
		}

		auto getFinaliserForCodeSections(void) const
		{
			return ChainedFinalisation(
				LinkerFiniArraySection(__linker_code_flash_app_finiArray_start, &__linker_code_flash_app_finiArray_pastEnd));
		}
	};
}

#endif
