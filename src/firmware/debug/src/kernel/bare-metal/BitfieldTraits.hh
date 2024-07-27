#ifndef __SMEG_KERNEL_BAREMETAL_BITFIELDTRAITS_HH
#define __SMEG_KERNEL_BAREMETAL_BITFIELDTRAITS_HH
#include <concepts>
#include <limits>
#include <type_traits>
#include <utility>

#include "Bitmask.hh"
#include "OffsetIntegerSequence.hh"

namespace smeg::kernel::bare_metal
{
	template <std::integral TInt, std::size_t LeftIndex, std::size_t NumBits = 1>
	struct BitfieldTraits
	{
	private:
		using TUnsignedInt = std::make_unsigned_t<TInt>;
		static_assert(LeftIndex >= 0 && LeftIndex < std::numeric_limits<TUnsignedInt>::digits, "Bit index is beyond the integer's range");
		static_assert(NumBits > 0, "Number of bits must be at least 1");
		static_assert(LeftIndex - (NumBits - 1) >= 0, "Too many bits specified for the given index");

	public:
		static constexpr std::size_t leftIndex{LeftIndex};
		static constexpr std::size_t rightIndex{LeftIndex - NumBits + 1};

		using Indices = typename OffsetIntegerSequence<rightIndex, std::make_index_sequence<NumBits>>::Values;

		using Mask = BitmaskFrom<Indices>;
	};
}

#endif
