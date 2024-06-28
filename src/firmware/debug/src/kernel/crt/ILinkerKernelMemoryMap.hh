#ifndef __SMEG_KERNEL_CRT_ILINKERKERNELMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERKERNELMEMORYMAP_HH
#include "../IInitialisable.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept ILinkerKernelMemoryMap = IInitialisable<T>;
}

#endif
