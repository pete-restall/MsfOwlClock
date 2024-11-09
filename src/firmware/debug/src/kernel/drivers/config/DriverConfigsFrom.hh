#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_DRIVERCONFIGSFROM_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_DRIVERCONFIGSFROM_HH
#include <tuple>

#include "IHaveConfigForDrivers.hh"

namespace smeg::kernel::drivers::config
{
	template <IHaveConfigForDrivers TConfig>
	class DriverConfigsFrom
	{
	public:
		using PerConfig = typename TConfig::Drivers;
	};
}

#endif
