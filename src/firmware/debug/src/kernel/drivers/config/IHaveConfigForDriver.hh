#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORDRIVER_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORDRIVER_HH
#include "../../tasks/config/IHaveConfigForTasks.hh"
#include "IHaveConfigForDriverApis.hh"
#include "IHaveConfigForSyscalls.hh"

namespace smeg::kernel::drivers::config
{
	using namespace smeg::kernel::tasks::config;

	template <typename T>
	concept IHaveConfigForDriver = IHaveConfigForSyscalls<T> || IHaveConfigForTasks<T> || IHaveConfigForDriverApis<T>;
}

#endif
