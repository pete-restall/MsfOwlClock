#ifndef __SMEG_KERNEL_CRT_ILINKERAPPMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERAPPMEMORYMAP_HH
#include "../INonConstFinalisable.hh"
#include "../INonConstInitialisable.hh"

namespace smeg::kernel::crt
{
	template <typename T>
	concept ILinkerAppMemoryMap = requires(const T &map)
	{
		{ map.getInitialiserForRamSections() } -> INonConstInitialisable;
		{ map.getInitialiserForCodeSections() } -> INonConstInitialisable;
		{ map.getFinaliserForCodeSections() } -> INonConstFinalisable;
	};
}

#endif
