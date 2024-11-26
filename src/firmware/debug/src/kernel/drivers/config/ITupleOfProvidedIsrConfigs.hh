#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_ITUPLEOFPROVIDEDISRCONFIGS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_ITUPLEOFPROVIDEDISRCONFIGS_HH
#include <tuple>

#include "IProvidedIsrConfig.hh"

namespace smeg::kernel::drivers::config
{
	template <typename... T>
	struct _$IsTupleOfProvidedIsrConfigs
	{
		static constexpr bool value = false;
	};

	template <IProvidedIsrConfig... T>
	struct _$IsTupleOfProvidedIsrConfigs<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept ITupleOfProvidedIsrConfigs = _$IsTupleOfProvidedIsrConfigs<T>::value;
}

#endif
