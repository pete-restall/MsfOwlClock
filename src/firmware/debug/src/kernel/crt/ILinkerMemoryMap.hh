#ifndef __SMEG_KERNEL_CRT_ILINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERMEMORYMAP_HH
#include "ILinkerAppMemoryMap.hh"
#include "ILinkerKernelMemoryMap.hh"

namespace smeg::kernel::crt
{
	template <typename T>
	concept ILinkerMemoryMap = requires(const T &map)
	{
		{ map.getLinkerMemoryMapForKernel() } -> ILinkerKernelMemoryMap;
		{ map.getLinkerMemoryMapForApp() } -> ILinkerAppMemoryMap;
	};
}

#endif
