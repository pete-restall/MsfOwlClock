#ifndef __SMEG_KERNEL_CRT_ILINKERMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_ILINKERMEMORYMAP_HH
#include "../IInitialisable.hh"
#include "IApplicationLinkerMemoryMap.hh"
#include "IKernelLinkerMemoryMap.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept ILinkerMemoryMap = requires(const T &map)
	{
		{ map.getLinkerMemoryMapForKernel() } -> IKernelLinkerMemoryMap;
		{ map.getLinkerMemoryMapForApplication() } -> IApplicationLinkerMemoryMap;
	};
}

#endif
