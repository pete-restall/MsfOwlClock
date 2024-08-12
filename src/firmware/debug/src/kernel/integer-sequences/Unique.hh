#ifndef __SMEG_KERNEL_INTEGERSEQUENCES_UNIQUE_HH
#define __SMEG_KERNEL_INTEGERSEQUENCES_UNIQUE_HH
#include <concepts>
#include <type_traits>
#include <utility>
#include "utilities.hh"

namespace smeg::kernel::integer_sequences
{
	template <std::integral T, T... Tail>
	struct Unique;

	template <std::integral T, T Head, T... Tail>
	struct Unique<T, Head, Tail...>
	{
		using Values = std::conditional<
			((Head != Tail) && ...),
			decltype(pushFront<Head>(typename Unique<T, Tail...>::Values{})),
			typename Unique<T, Tail...>::Values
		>::type;
	};

	template <std::integral T, T Head>
	struct Unique<T, Head>
	{
		using Values = std::integer_sequence<T, Head>;
	};

	template <std::integral T>
	struct Unique<T>
	{
		using Values = std::integer_sequence<T>;
	};
}

#endif
