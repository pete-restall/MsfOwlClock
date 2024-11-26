#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_ITUPLEOFPROVIDEDAPICONFIGS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_ITUPLEOFPROVIDEDAPICONFIGS_HH
#include <tuple>

#include "IProvidedApiConfig.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T>
	struct _$IsTupleOfProvidedApiConfigs
	{
		static constexpr bool value = false;
	};

	template <IProvidedApiConfig... T>
	struct _$IsTupleOfProvidedApiConfigs<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept ITupleOfProvidedApiConfigs = _$IsTupleOfProvidedApiConfigs<T>::value;
}

#endif
