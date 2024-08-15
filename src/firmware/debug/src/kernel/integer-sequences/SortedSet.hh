#ifndef __SMEG_KERNEL_INTEGERSEQUENCES_SORTEDSET_HH
#define __SMEG_KERNEL_INTEGERSEQUENCES_SORTEDSET_HH
#include <concepts>
#include <cstdint>
#include <utility>
#include "BubbleSorted.hh"
#include "Unique.hh"

namespace smeg::kernel::integer_sequences
{
	template <template <typename, auto...> typename TSort, std::integral T, T... Ints>
	class _SortedSet
	{
	private:
		template <T... UniqueInts>
		static consteval auto sorted(std::integer_sequence<T, UniqueInts...>)
		{
			return TSort<T, UniqueInts...>{};
		}

		using UniqueInts = typename Unique<T, Ints...>::Values;
		using SortedInts = decltype(sorted(UniqueInts{}));

	public:
		using Ascending = SortedInts::Ascending;
		using Descending = SortedInts::Descending;
	};

	template <std::integral T, T... Ints>
	using SortedSet = _SortedSet<BubbleSorted, T, Ints...>;
}

#endif
