#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKERKERNELFINIARRAY_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_LINKERKERNELFINIARRAY_HH
#include "../../../../../InitFiniArray.hh"

extern "C"
{
	extern const smeg::kernel::crt::InitArrayEntry __linker_code_flash_kernel_finiArray_start;
	extern const smeg::kernel::crt::InitArrayEntry __linker_code_flash_kernel_finiArray_pastEnd;
}

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	class LinkerKernelFiniArray
	{
public:
		const FiniArrayEntry *begin(void) const { return &__linker_code_flash_kernel_finiArray_start; }
		const FiniArrayEntry *end(void) const { return &__linker_code_flash_kernel_finiArray_pastEnd; }
	};
}

#endif
