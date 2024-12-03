#ifndef __SMEG_KERNEL_DRIVERS_IISR_HH
#define __SMEG_KERNEL_DRIVERS_IISR_HH
#include <concepts>
#include <type_traits>

#include "IIsrApi.hh"
#include "IsrApis.hh"

namespace smeg::kernel::drivers
{
	template <typename... T>
	struct _$IsIsrApis
	{
		static constexpr bool value = false;
	};

	template <IIsrApi... TApis>
	struct _$IsIsrApis<IsrApis<TApis...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept _$IIsrHasTypedefForRequiredApis = _$IsIsrApis<std::remove_cv_t<typename T::RequiredApis>>::value;

	template <typename T>
	concept INakedIsr =
		std::is_nothrow_default_constructible_v<T> &&
		!_$IIsrHasTypedefForRequiredApis<T> &&
		requires
		{
			{ T::onInterrupt() } noexcept -> std::same_as<void>;
		};

	template <typename T> // TODO: This is now public; needs to be tested - for symmetry, ensure IPerCoreIsrWithoutRequiredApis is also public / tested
	concept IPerCoreIsrWithRequiredApis =
		_$IIsrHasTypedefForRequiredApis<T> &&
		!std::is_default_constructible_v<T> &&
		std::is_nothrow_constructible_v<T, std::decay_t<typename T::RequiredApis>> &&
		std::is_member_function_pointer_v<decltype(&T::onInterrupt)> &&
		requires(T &isr)
		{
			{ isr.onInterrupt() } noexcept -> std::same_as<void>;
		};

	template <typename T>
	concept _$IPerCoreIsrWithoutRequiredApis =
		!_$IIsrHasTypedefForRequiredApis<T> &&
		std::is_nothrow_default_constructible_v<T> &&
		std::is_member_function_pointer_v<decltype(&T::onInterrupt)> &&
		requires(T &isr)
		{
			{ isr.onInterrupt() } noexcept -> std::same_as<void>;
		};

	template <typename T>
	concept IPerCoreIsr = _$IPerCoreIsrWithoutRequiredApis<T> || IPerCoreIsrWithRequiredApis<T>;

	template <typename T>
	concept IIsr = INakedIsr<T> || IPerCoreIsr<T>;
}

#endif
