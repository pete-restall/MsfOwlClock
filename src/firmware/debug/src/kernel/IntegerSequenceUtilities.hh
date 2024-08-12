#ifndef __SMEG_KERNEL_INTEGERSEQUENCEUTILITIES_HH
#define __SMEG_KERNEL_INTEGERSEQUENCEUTILITIES_HH
#include <concepts>
#include <utility>

namespace smeg::kernel
{
	template <std::integral auto NewFirstElement, std::integral T, T... Ints>
	constexpr auto pushFront(std::integer_sequence<T, Ints...>)
	{
		return std::integer_sequence<T, NewFirstElement, Ints...>();
	}
}

#endif
