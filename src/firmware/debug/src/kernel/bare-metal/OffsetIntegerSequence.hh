#ifndef __SMEG_KERNEL_BAREMETAL_OFFSETINTEGERSEQUENCE_HH
#define __SMEG_KERNEL_BAREMETAL_OFFSETINTEGERSEQUENCE_HH
#include <concepts>
#include <utility>

namespace smeg::kernel::bare_metal
{
	template <std::integral auto Offset, typename TSeq>
	struct OffsetIntegerSequence;

	template <std::integral auto Offset, decltype(Offset)... Ints>
	struct OffsetIntegerSequence<Offset, std::integer_sequence<decltype(Offset), Ints...>>
	{
		using Values = std::integer_sequence<decltype(Offset), Offset + Ints...>;
	};
}

#endif
