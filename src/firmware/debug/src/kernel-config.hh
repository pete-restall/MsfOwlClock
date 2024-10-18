#ifndef __RESTALL_MSFOWLCLOCK_KERNELCONFIG_HH
#define __RESTALL_MSFOWLCLOCK_KERNELCONFIG_HH
#include <tuple>
#include "kernel/public/config.hh"

namespace smeg::config
{
	struct __NopTask { void run(void) {  } }; // TODO: TEMPORARY FOR COMPILATION AND DEBUGGING...
	struct __NopTaskConfig { using Type = __NopTask; struct Stack { static constexpr auto numberOfSlots = 32; }; }; // TODO: TEMPORARY FOR COMPILATION AND DEBUGGING...

	struct KernelConfig
	{
		// TODO:
		// KernelConfig will need to contain settings for things such as the scheduler and the other drivers.  The default 'idle' task
		// also needs to be specified, but this should be overridable by the app once it's loaded (should be able to provide its own).
		using Tasks = std::tuple<__NopTaskConfig, __NopTaskConfig>;
	};
}

#endif
