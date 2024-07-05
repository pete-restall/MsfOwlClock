#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERAPPMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERAPPMEMORYMAP_HH
#include <cstdint>
#include "../../../../../../../ChainedInitialisation.hh"
#include "../../../../../linker/LinkerBssMemorySection.hh"
#include "../../../../../linker/LinkerDataMemorySection.hh"

extern "C"
{
	extern std::uint32_t __linker_sram_bss_app_start;
	extern std::uint32_t __linker_sram_bss_app_pastEnd;

	extern std::uint32_t __linker_sram_data_app_start;
	extern std::uint32_t __linker_sram_data_app_pastEnd;

	extern const std::uint32_t __linker_sram_data_app_lmaStart;
	extern const std::uint32_t __linker_sram_data_app_lmaPastEnd;

	extern std::uint32_t __linker_sram_bss_retained16k_app_start;
	extern std::uint32_t __linker_sram_bss_retained16k_app_pastEnd;

	extern std::uint32_t __linker_sram_retained16k_data_app_start;
	extern std::uint32_t __linker_sram_retained16k_data_app_pastEnd;

	extern const std::uint32_t __linker_sram_retained16k_data_app_lmaStart;
	extern const std::uint32_t __linker_sram_retained16k_data_app_lmaPastEnd;
}

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	using namespace smeg::kernel::crt::crt0::linker;

	class LinkerAppMemoryMap
	{
public:
		void initialise(void)
		{
			ChainedInitialisation initialisers(
				LinkerBssMemorySection(&__linker_sram_bss_app_start, &__linker_sram_bss_app_pastEnd),
				LinkerBssMemorySection(&__linker_sram_bss_retained16k_app_start, &__linker_sram_bss_retained16k_app_pastEnd),
				LinkerDataMemorySection(
					&__linker_sram_data_app_lmaStart,
					&__linker_sram_data_app_lmaPastEnd,
					&__linker_sram_data_app_start),
				LinkerDataMemorySection(
					&__linker_sram_retained16k_data_app_lmaStart,
					&__linker_sram_retained16k_data_app_lmaPastEnd,
					&__linker_sram_retained16k_data_app_start));

			initialisers.initialise();
		}
	};
}

#endif
