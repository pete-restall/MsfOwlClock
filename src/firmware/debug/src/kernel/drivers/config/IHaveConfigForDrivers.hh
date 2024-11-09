#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORDRIVERS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORDRIVERS_HH
#include <cstddef>
#include <tuple>

#include "IHaveConfigForDriver.hh"

namespace smeg::kernel::drivers::config
{
	template <typename... T>
	struct _IsTupleOfDriverConfigs
	{
		static constexpr bool value = false;
	};

	template <IHaveConfigForDriver... T>
	struct _IsTupleOfDriverConfigs<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept IHaveConfigForDrivers = _IsTupleOfDriverConfigs<typename T::Drivers>::value;
}

#endif
