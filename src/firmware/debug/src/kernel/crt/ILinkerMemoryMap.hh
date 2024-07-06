#ifndef __SMEG_KERNEL_CRT_ILINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERMEMORYMAP_HH
#include "ILinkerAppMemoryMap.hh"
#include "ILinkerKernelMemoryMap.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept ILinkerMemoryMap = requires(const T &map)
	{
		{ map.createLinkerMemoryMapForKernel() } -> ILinkerKernelMemoryMap;
		{ map.createLinkerMemoryMapForApp() } -> ILinkerAppMemoryMap;
	};
}

#endif
