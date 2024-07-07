#ifndef __SMEG_KERNEL_CRT_ILINKERAPPMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERAPPMEMORYMAP_HH
#include "../INonConstFinalisable.hh"
#include "../INonConstInitialisable.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept ILinkerAppMemoryMap = requires(const T &map)
	{
		{ map.createInitialiserForRamSections() } -> INonConstInitialisable;
		{ map.createInitialiserForCodeSections() } -> INonConstInitialisable;
		{ map.createFinaliserForCodeSections() } -> INonConstFinalisable;
	};
}

#endif
