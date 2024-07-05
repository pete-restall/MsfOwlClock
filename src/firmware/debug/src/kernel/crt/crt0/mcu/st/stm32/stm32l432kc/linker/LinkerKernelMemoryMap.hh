#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERKERNELMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKER_LINKERKERNELMEMORYMAP_HH
#include <cstdint>
#include "../../../../../../../ChainedInitialisation.hh"
#include "../../../../../linker/LinkerBssMemorySection.hh"
#include "../../../../../linker/LinkerDataMemorySection.hh"

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
}

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	using namespace smeg::kernel::crt::crt0::linker;

	class LinkerKernelMemoryMap
	{
public:
		void initialise(void)
		{
			ChainedInitialisation initialisers(
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

			initialisers.initialise();
		}
	};
}

#endif
