#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERKERNELINITARRAY_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERKERNELINITARRAY_HH
#include "InitFiniArray.hh"

extern "C"
{
	extern const smeg::kernel::crt::crt0::linker::InitArrayEntry __linker_code_flash_kernel_initArray_start;
	extern const smeg::kernel::crt::crt0::linker::InitArrayEntry __linker_code_flash_kernel_initArray_pastEnd;
}

namespace smeg::kernel::crt::crt0::linker
{
	class LinkerKernelInitArray
	{
public:
		consteval const InitArrayEntry *begin(void) const { return &__linker_code_flash_kernel_initArray_start; }
		consteval const InitArrayEntry *end(void) const { return &__linker_code_flash_kernel_initArray_pastEnd; }
	};
}

#endif
