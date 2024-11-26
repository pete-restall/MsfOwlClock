#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORPROVIDEDISRS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORPROVIDEDISRS_HH
#include "ITupleOfProvidedIsrConfigs.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T>
	concept IHaveConfigForProvidedIsrs = ITupleOfProvidedIsrConfigs<typename T::ProvidedIsrs>;
}

#endif
