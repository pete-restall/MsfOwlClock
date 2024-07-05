#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_ILINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_ILINKERMEMORYMAP_HH
#include "../../../IInitialisable.hh"

namespace smeg::kernel::crt::crt0::linker
{
	template <typename T>
	concept ILinkerMemoryMap = INonConstInitialisable<T>;
}

#endif
