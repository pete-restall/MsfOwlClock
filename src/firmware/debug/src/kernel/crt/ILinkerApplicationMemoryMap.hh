#ifndef __SMEG_KERNEL_CRT_ILINKERAPPLICATIONMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERAPPLICATIONMEMORYMAP_HH
#include "../IInitialisable.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept ILinkerApplicationMemoryMap = IInitialisable<T>;
}

#endif
