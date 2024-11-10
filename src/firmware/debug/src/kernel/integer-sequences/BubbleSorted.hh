#ifndef __SMEG_KERNEL_INTEGERSEQUENCES_BUBBLESORTED_HH
#define __SMEG_KERNEL_INTEGERSEQUENCES_BUBBLESORTED_HH
#include <cstddef>
#include <concepts>
#include <type_traits>
#include <utility>

#include "utilities.hh"

namespace smeg::kernel::integer_sequences
{
	template <std::integral T, T... Ints>
	class BubbleSorted
	{
	private:
		template <bool IsAscending, T... Tail>
		struct BubbleSortIteration;

		template <bool IsAscending, T A, T B, T... Tail>
		struct BubbleSortIteration<IsAscending, A, B, Tail...>
		{
			using IsPairInOrder = std::conditional<
				(IsAscending && A < B) || (!IsAscending && B < A),
				std::true_type,
				std::false_type
			>::type;

			using Next = std::conditional<
				IsPairInOrder::value,
				BubbleSortIteration<IsAscending, B, Tail...>,
				BubbleSortIteration<IsAscending, A, Tail...>
			>::type;

			using IsFullyOrdered = std::conditional<
				IsPairInOrder::value && Next::IsFullyOrdered::value,
				std::true_type,
				std::false_type
			>::type;

			using Values = std::conditional<
				IsPairInOrder::value,
				decltype(pushFront<A>(typename Next::Values{})),
				decltype(pushFront<B>(typename Next::Values{}))
			>::type;
		};

		template <bool IsAscending, T A>
		struct BubbleSortIteration<IsAscending, A>
		{
			using IsPairInOrder = std::true_type;
			using IsFullyOrdered = std::true_type;
			using Values = std::integer_sequence<T, A>;
		};

		template <bool IsAscending>
		struct BubbleSortIteration<IsAscending>
		{
			using IsPairInOrder = std::true_type;
			using IsFullyOrdered = std::true_type;
			using Values = std::integer_sequence<T>;
		};

		template <bool IsAscending, std::size_t N, auto... Sequence>
		static consteval auto sort(std::integer_sequence<T, Sequence...>)
		{
			using Iteration = BubbleSortIteration<IsAscending, Sequence...>;
			if constexpr (Iteration::IsFullyOrdered::value || N > sizeof...(Sequence))
				return typename Iteration::Values{};
			else
				return sort<IsAscending, N + 1>(typename Iteration::Values{});
		}

	public:
		using Ascending = decltype(sort<true, 0>(std::integer_sequence<T, Ints...>{}));
		using Descending = decltype(sort<false, 0>(std::integer_sequence<T, Ints...>{}));
	};

	template <std::integral T, T... Ints>
	consteval auto bubbleSortedAscending(std::integer_sequence<T, Ints...>)
	{
		return typename BubbleSorted<T, Ints...>::Ascending{};
	}

	template <std::integral T, T... Ints>
	consteval auto bubbleSortedDescending(std::integer_sequence<T, Ints...>)
	{
		return typename BubbleSorted<T, Ints...>::Descending{};
	}
}

#endif
