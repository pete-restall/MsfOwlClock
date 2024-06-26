#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKERMEMORYMAP_HH

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
#if false
	class Stm32l432kcLinkerMemoryMap
	{
public:
		LinkerMemoryMap getLinkerMemoryMapForKernel(void) const
		{
			return LinkerMemoryMap(
				// TODO: These would probably be better as individual classes, then the pointers could be retrieved directly rather than being stored (30*4=120 bytes of pointers)
				LinkerInitArray(__linker_code_flash_kernel_initArray_start, __linker_code_flash_kernel_initArray_pastEnd),
				LinkerFiniArray(__linker_code_flash_kernel_finiArray_start, __linker_code_flash_kernel_finiArray_pastEnd)
				LinkerBssMemoryMap(
					LinkerBssMemorySection(__linker_sram_bss_retained16k_kernel_start, __linker_sram_bss_retained16k_kernel_pastEnd),
					LinkerBssMemorySection(__linker_sram_bss_kernel_start, __linker_sram_bss_kernel_pastEnd))

				LinkerDataMemoryMap(
					LinkerDataMemorySection(__linker_sram_data_retained16k_kernel_start, __linker_sram_data_retained16k_kernel_pastEnd, __linker_sram_data_retained16k_kernel_lmaStart)
					LinkerDataMemorySection(__linker_sram_data_kernel_start, __linker_sram_data_kernel_pastEnd, __linker_sram_data_kernel_lmaStart)),

				LinkerStack(__linker_sram_stack_kernel_bottom, __linker_sram_stack_kernel_pastTop));
		}

		LinkerMemoryMap getLinkerMemoryMapForApplication(void) const
		{
			return LinkerMemoryMap(
				LinkerInitArray(__linker_code_flash_application_initArray_start, __linker_code_flash_application_initArray_pastEnd),
				LinkerFiniArray(__linker_code_flash_application_finiArray_start, __linker_code_flash_application_finiArray_pastEnd)
				LinkerBssMemoryMap(
					LinkerBssMemorySection(__linker_sram_bss_retained16k_application_start, __linker_sram_bss_retained16k_application_pastEnd),
					LinkerBssMemorySection(__linker_sram_bss_application_start, __linker_sram_bss_application_pastEnd))

				LinkerDataMemoryMap(
					LinkerDataMemorySection(__linker_sram_data_retained16k_application_start, __linker_sram_data_retained16k_application_pastEnd, __linker_sram_data_retained16k_application_lmaStart)
					LinkerDataMemorySection(__linker_sram_data_application_start, __linker_sram_data_application_pastEnd, __linker_sram_data_application_lmaStart)));
		}
	};

	namespace
	{
		extern "C"
		{
			extern const InitFuncPtr __linker_code_flash_kernel_initArray_start;
			extern const InitFuncPtr __linker_code_flash_kernel_initArray_pastEnd;

			extern const InitFuncPtr __linker_code_flash_kernel_finiArray_start;
			extern const InitFuncPtr __linker_code_flash_kernel_finiArray_pastEnd;

			extern const InitFuncPtr __linker_code_flash_application_initArray_start;
			extern const InitFuncPtr __linker_code_flash_application_initArray_pastEnd;

			extern const InitFuncPtr __linker_code_flash_application_finiArray_start;
			extern const InitFuncPtr __linker_code_flash_application_finiArray_pastEnd;

			extern std::uint32_t __linker_sram_bss_retained16k_kernel_start;
			extern std::uint32_t __linker_sram_bss_retained16k_kernel_pastEnd;
			extern std::uint32_t __linker_sram_data_retained16k_kernel_start;
			extern std::uint32_t __linker_sram_data_retained16k_kernel_pastEnd;
			extern std::uint32_t __linker_sram_data_retained16k_kernel_lmaStart;
			extern std::uint32_t __linker_sram_bss_retained16k_kernel_start;
			extern std::uint32_t __linker_sram_bss_retained16k_kernel_pastEnd;
			extern std::uint32_t __linker_sram_data_retained16k_application_start;
			extern std::uint32_t __linker_sram_data_retained16k_application_pastEnd;
			extern std::uint32_t __linker_sram_data_retained16k_application_lmaStart;
			extern std::uint32_t __linker_sram_bss_retained16k_application_start;
			extern std::uint32_t __linker_sram_bss_retained16k_application_pastEnd;
			extern std::uint32_t __linker_sram_data_kernel_start;
			extern std::uint32_t __linker_sram_data_kernel_pastEnd;
			extern std::uint32_t __linker_sram_data_kernel_lmaStart;
			extern std::uint32_t __linker_sram_bss_kernel_start;
			extern std::uint32_t __linker_sram_bss_kernel_pastEnd;
			extern std::uint32_t __linker_sram_data_application_start;
			extern std::uint32_t __linker_sram_data_application_pastEnd;
			extern std::uint32_t __linker_sram_data_application_lmaStart;
			extern std::uint32_t __linker_sram_bss_application_start;
			extern std::uint32_t __linker_sram_bss_application_pastEnd;
		}
	}
#endif
}

#endif
