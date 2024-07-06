#ifndef __SMEG_KERNEL_CRT_ILINKERKERNELMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERKERNELMEMORYMAP_HH
#include "../INonConstInitialisable.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept ILinkerKernelMemoryMap = requires(const T &map)
	{
		{ map.createInitialiserForRamSections() } -> INonConstInitialisable;
		{ map.createInitialiserForCodeSections() } -> INonConstInitialisable;
	};
}

#endif
