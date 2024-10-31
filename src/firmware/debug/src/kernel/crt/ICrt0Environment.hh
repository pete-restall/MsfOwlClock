#ifndef __SMEG_KERNEL_CRT_ICRT0ENVIRONMENT_HH
#define __SMEG_KERNEL_CRT_ICRT0ENVIRONMENT_HH
#include "../tasks/config/IHaveConfigForTasks.hh"
#include "IBootloader.hh"
#include "ILinkerMemoryMap.hh"

namespace smeg::kernel::crt
{
	template <typename T>
	concept ICrt0Environment = requires(const T &env)
	{
		{ env.getLinkerMemoryMap() } -> ILinkerMemoryMap;
		{ env.getBootloader() } -> IBootloader;
	} &&
	tasks::config::IHaveConfigForTasks<typename T::Config>;
}

#endif
