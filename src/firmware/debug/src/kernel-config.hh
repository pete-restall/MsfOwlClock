#ifndef __RESTALL_MSFOWLCLOCK_KERNELCONFIG_HH
#define __RESTALL_MSFOWLCLOCK_KERNELCONFIG_HH
#include "kernel/config/dsl.hh"

namespace smeg::config
{
	struct KernelConfig
	{
		// TODO:
		// KernelConfig will need to contain settings for things such as the scheduler and the other drivers.  The default 'idle' task
		// also needs to be specified, but this should be overridable by the app once it's loaded (should be able to provide its own).
	};
}

#endif
