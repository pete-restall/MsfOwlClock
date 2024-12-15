#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVEREQUIREDAPIS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVEREQUIREDAPIS_HH
#include <type_traits>

namespace smeg::kernel
{
	template <template <typename...> typename TApisInterface, typename... T>
	struct _$IsRequiredApisTypedef
	{
		static constexpr bool value = false;
	};

	template <template <typename...> typename TApisInterface, typename... TApis>
	struct _$IsRequiredApisTypedef<TApisInterface, TApisInterface<TApis...>>
	{
		static constexpr bool value = true;
	};

	template <typename T, template <typename...> typename TApisInterface>
	concept _$HasTypedefForRequiredApis = _$IsRequiredApisTypedef<TApisInterface, std::remove_cv_t<typename T::RequiredApis>>::value;

	template <typename T>
	concept IHaveAnyRequiredApisTypedef = std::is_class_v<typename T::RequiredApis>;

	template <typename T, typename... TArgs>
	concept IHaveAnyRequiredApis =
		IHaveAnyRequiredApisTypedef<T> &&
		!std::is_default_constructible_v<T> &&
		std::is_constructible_v<T, std::decay_t<typename T::RequiredApis>, TArgs...>;

	template <typename T, template <typename...> typename TApisInterface, typename... TArgs>
	concept IHaveRequiredApis =
		IHaveAnyRequiredApisTypedef<T> &&
		_$HasTypedefForRequiredApis<T, TApisInterface> &&
		IHaveAnyRequiredApis<T, TArgs...>;
}

#endif
