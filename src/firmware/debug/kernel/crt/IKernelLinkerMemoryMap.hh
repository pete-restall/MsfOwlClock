#ifndef __SMEG_KERNEL_CRT_IKERNELLINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_IKERNELLINKERMEMORYMAP_HH
#include "../IInitialisable.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept IKernelLinkerMemoryMap = IInitialisable<T>;
}

#endif