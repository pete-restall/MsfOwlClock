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
// TODO: MAKE A CONCEPT OF ILinkerAppFiniArray = INonConstShutdownable (basically INonConstInitialisable but different method name)
// THE ACTUAL LinkerAppFiniArray CAN THEN BE WRITTEN (TDD) WITH AN initialise() METHOD THAT REVERSE-ITERATES A CONSTRUCTOR-PASSED SET OF FUNCTION POINTERS AND CALLS THEM - SIMILAR TO THE BSS AND DATA INITIALISATION
// ALSO THE SAME WITH THE LinkerAppInitArray (INonConstInitialisable, obviously)
// THEN THE GENERIC LinkerMemoryMap(IInitialisableMemorySection...) WITH ITS OWN initialise() THAT JUST CALLS ChainedInitialisation.initialise()
// THEN REFACTOR EVERYTHING INTO MODULES TO REMOVE THE DEPENDENCY ON HEADERS, WHICH SHOULD ALSO ALLOW HIDING OF THE __linker_* CONSTANTS...
	class LinkerAppFiniArray
	{
public:
		consteval const FiniArrayEntry *begin(void) const { return &__linker_code_flash_app_finiArray_start; }
		consteval const FiniArrayEntry *end(void) const { return &__linker_code_flash_app_finiArray_pastEnd; }
	};
}

#endif
