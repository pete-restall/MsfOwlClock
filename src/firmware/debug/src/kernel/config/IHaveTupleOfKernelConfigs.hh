#ifndef __SMEG_KERNEL_CONFIG_IHAVETUPLEOFKERNELCONFIGS_HH
#define __SMEG_KERNEL_CONFIG_IHAVETUPLEOFKERNELCONFIGS_HH
#include "ITupleOfKernelConfigs.hh"

namespace smeg::kernel::config
{
	template <typename T>
	concept IHaveTupleOfKernelConfigs = ITupleOfKernelConfigs<typename T::AsTuple>;
}

#endif
