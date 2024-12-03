#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IPROVIDEDISRCONFIG_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IPROVIDEDISRCONFIG_HH
#include <concepts>
#include <type_traits>

#include "../IIsr.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T>
	concept _$IProvidedMandatoryIsrConfig =
		!std::same_as<std::decay_t<decltype(T::irq)>, bool> &&
		std::integral<decltype(T::irq)> &&
		std::conditional_t<T::irq == T::irq, std::true_type, std::false_type>::value;

	template <typename T> // TODO: NEEDS TESTING, NOW THAT THIS IS PUBLIC
	concept IProvidedNakedIsrConfig =
		_$IProvidedMandatoryIsrConfig<T> &&
		INakedIsr<typename T::Handler>;

	template <typename T> // TODO: NEEDS TESTING, NOW THAT THIS IS PUBLIC
	concept IProvidedPerCoreIsrConfig =
		_$IProvidedMandatoryIsrConfig<T> &&
		IPerCoreIsr<typename T::Handler>;

	template <typename T>
	concept IProvidedIsrConfig =
		_$IProvidedMandatoryIsrConfig<T> &&
		IIsr<typename T::Handler>;
}

#endif
