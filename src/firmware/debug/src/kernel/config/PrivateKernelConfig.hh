#ifndef __SMEG_KERNEL_CONFIG_PRIVATEKERNELCONFIG_HH
#define __SMEG_KERNEL_CONFIG_PRIVATEKERNELCONFIG_HH
#include <tuple>

namespace smeg::kernel::config
{
	struct PrivateKernelConfig
	{
		using Drivers = std::tuple<>;
	};
}

#endif
