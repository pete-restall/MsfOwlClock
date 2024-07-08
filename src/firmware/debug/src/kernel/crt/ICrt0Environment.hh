#ifndef __SMEG_KERNEL_CRT_ICRT0ENVIRONMENT_HH
#define __SMEG_KERNEL_CRT_ICRT0ENVIRONMENT_HH
#include "ILinkerMemoryMap.hh"

namespace smeg::kernel::crt
{
	template <class T>
	concept ICrt0Environment = requires(const T &env)
	{
		{ env.getLinkerMemoryMap() } -> ILinkerMemoryMap;
	};
}

#endif
