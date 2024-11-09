#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORDRIVERAPIS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORDRIVERAPIS_HH
#include "../../IAppToDriverApi.hh"
#include "../../IDriverToDriverApi.hh"
#include "../../IDriverToKernelApi.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T>
	concept IHaveConfigForAppToDriverApis = IAppToDriverApi<typename T::AppToDriverApi::Type>;

	template <typename T>
	concept IHaveConfigForDriverToDriverApis = IDriverToDriverApi<typename T::DriverToDriverApi::Type>;

	template <typename T>
	concept IHaveConfigForDriverToKernelApis = IDriverToKernelApi<typename T::DriverToKernelApi::Type>;

	template <typename T>
	concept IHaveConfigForDriverApis = IHaveConfigForAppToDriverApis<T> || IHaveConfigForDriverToDriverApis<T> || IHaveConfigForDriverToKernelApis<T>;
}

#endif
