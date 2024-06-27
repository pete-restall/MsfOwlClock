#ifndef __SMEG_KERNEL_CRT_IAPPLICATIONLINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_IAPPLICATIONLINKERMEMORYMAP_HH
#include "../IInitialisable.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept IApplicationLinkerMemoryMap = IInitialisable<T>;
}

#endif
