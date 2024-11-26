#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IPROVIDEDAPICONFIG_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IPROVIDEDAPICONFIG_HH
#include <type_traits>

namespace smeg::kernel::drivers::config
{
	template <typename T>
	concept IProvidedApiConfig = std::is_class_v<typename T::Type> && std::is_class_v<typename T::Interface<typename T::Type>>;
}

#endif
