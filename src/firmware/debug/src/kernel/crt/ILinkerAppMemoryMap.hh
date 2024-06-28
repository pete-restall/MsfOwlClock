#ifndef __SMEG_KERNEL_CRT_ILINKERAPPMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERAPPMEMORYMAP_HH
#include "../IInitialisable.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept ILinkerAppMemoryMap = IInitialisable<T>;
}

#endif
