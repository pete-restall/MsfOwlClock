#ifndef __SMEG_KERNEL_CRT_ILINKERKERNELMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERKERNELMEMORYMAP_HH
#include "../INonConstFinalisable.hh"
#include "../INonConstInitialisable.hh"

namespace smeg::kernel::crt
{
	template <typename T>
	concept ILinkerKernelMemoryMap = requires(const T &map)
	{
		{ map.getInitialiserForRamSections() } -> INonConstInitialisable;
		{ map.getInitialiserForCodeSections() } -> INonConstInitialisable;
		{ map.getFinaliserForCodeSections() } -> INonConstFinalisable;
	};
}

#endif
