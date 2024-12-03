#ifndef __SMEG_KERNEL_IMCUCORETRAITS_HH
#define __SMEG_KERNEL_IMCUCORETRAITS_HH
#include <concepts>
#include <cstddef>
#include <type_traits>

namespace smeg::kernel
{
	template <typename T>
	concept _$IntegralButNotBoolean = std::integral<std::decay_t<T>> && !std::same_as<std::decay_t<T>, bool>;

	template <typename T>
	concept IMcuCoreTraits =
		_$IntegralButNotBoolean<decltype(T::numberOfMcuCores)> &&
		std::conditional_t<(T::numberOfMcuCores > 0), std::true_type, std::false_type>::value &&
		requires
		{
			{ T::getMcuCoreId() } noexcept -> _$IntegralButNotBoolean;
		};
}

#endif
