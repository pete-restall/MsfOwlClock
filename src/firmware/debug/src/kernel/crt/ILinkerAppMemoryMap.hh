#ifndef __SMEG_KERNEL_CRT_ILINKERAPPMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERAPPMEMORYMAP_HH
#include "../INonConstInitialisable.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept ILinkerAppMemoryMap = requires(const T &map)
	{
		{ map.createInitialiserForRamSections() } -> INonConstInitialisable;
		{ map.createInitialiserForCodeSections() } -> INonConstInitialisable;
	};
}

#endif
