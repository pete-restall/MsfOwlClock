#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORPROVIDEDAPIS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORPROVIDEDAPIS_HH
#include "ITupleOfProvidedApiConfigs.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T>
	concept IHaveConfigForProvidedApis = ITupleOfProvidedApiConfigs<typename T::ProvidedApis>;
}

#endif
