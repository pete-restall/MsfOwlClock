#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORDRIVERS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORDRIVERS_HH
#include "ITupleOfDriverConfigs.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T>
	concept IHaveConfigForDrivers = ITupleOfDriverConfigs<typename T::Drivers>;
}

#endif
