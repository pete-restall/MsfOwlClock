#ifndef __SMEG_KERNEL_BAREMETAL_OFFSETINTEGERSEQUENCE_HH
#define __SMEG_KERNEL_BAREMETAL_OFFSETINTEGERSEQUENCE_HH
#include <concepts>
#include <utility>

namespace smeg::kernel::bare_metal
{
	template <std::integral auto N, typename TSeq>
	struct OffsetIntegerSequence;

	template <std::integral auto N, decltype(N)... Ints>
	struct OffsetIntegerSequence<N, std::integer_sequence<decltype(N), Ints...>>
	{
		using Seq = std::integer_sequence<decltype(N), N + Ints...>;
	};
}

#endif
