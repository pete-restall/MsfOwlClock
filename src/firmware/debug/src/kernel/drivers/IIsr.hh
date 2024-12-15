#ifndef __SMEG_KERNEL_DRIVERS_IISR_HH
#define __SMEG_KERNEL_DRIVERS_IISR_HH
#include <concepts>
#include <type_traits>

#include "../IHaveRequiredApis.hh"
#include "IsrApis.hh"

namespace smeg::kernel::drivers
{
	template <typename T>
	concept INakedIsr =
		std::is_nothrow_default_constructible_v<T> &&
		!IHaveAnyRequiredApisTypedef<T> &&
		requires
		{
			{ T::onInterrupt() } noexcept -> std::same_as<void>;
		};

	template <typename T>
	concept _$IPerCoreIsrWithRequiredApis =
		IHaveRequiredApis<T, IsrApis> &&
		std::is_nothrow_constructible_v<T, std::decay_t<typename T::RequiredApis>> &&
		std::is_member_function_pointer_v<decltype(&T::onInterrupt)> &&
		requires(T &isr)
		{
			{ isr.onInterrupt() } noexcept -> std::same_as<void>;
		};

	template <typename T>
	concept _$IPerCoreIsrWithoutRequiredApis =
		!IHaveAnyRequiredApisTypedef<T> &&
		std::is_nothrow_default_constructible_v<T> &&
		std::is_member_function_pointer_v<decltype(&T::onInterrupt)> &&
		requires(T &isr)
		{
			{ isr.onInterrupt() } noexcept -> std::same_as<void>;
		};

	template <typename T>
	concept IPerCoreIsr = _$IPerCoreIsrWithoutRequiredApis<T> || _$IPerCoreIsrWithRequiredApis<T>;

	template <typename T>
	concept IIsr = INakedIsr<T> || IPerCoreIsr<T>;
}

#endif
