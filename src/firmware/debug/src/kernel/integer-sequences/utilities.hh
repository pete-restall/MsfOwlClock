#ifndef __SMEG_KERNEL_INTEGERSEQUENCES_UTILITIES_HH
#define __SMEG_KERNEL_INTEGERSEQUENCES_UTILITIES_HH
#include <concepts>
#include <utility>

namespace smeg::kernel::integer_sequences
{
	template <std::integral auto NewFirstElement, std::integral T, T... Ints>
	consteval auto pushFront(std::integer_sequence<T, Ints...>)
	{
		return std::integer_sequence<T, NewFirstElement, Ints...>();
	}
}

#endif
