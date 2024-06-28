#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERAPPFINIARRAY_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERAPPFINIARRAY_HH
#include "InitFiniArray.hh"

extern "C"
{
	extern const smeg::kernel::crt::crt0::linker::InitArrayEntry __linker_code_flash_app_finiArray_start;
	extern const smeg::kernel::crt::crt0::linker::InitArrayEntry __linker_code_flash_app_finiArray_pastEnd;
}

namespace smeg::kernel::crt::crt0::linker
{
	class LinkerAppFiniArray
	{
public:
		consteval const FiniArrayEntry *begin(void) const { return &__linker_code_flash_app_finiArray_start; }
		consteval const FiniArrayEntry *end(void) const { return &__linker_code_flash_app_finiArray_pastEnd; }
	};
}

#endif
