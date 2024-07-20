#ifndef __SMEG_KERNEL_BAREMETAL_BITMASK_HH
#define __SMEG_KERNEL_BAREMETAL_BITMASK_HH
#include <concepts>
#include <limits>
#include <type_traits>

namespace smeg::kernel::bare_metal
{
	template <std::integral TInt, std::integral auto... Bits>
	struct Bitmask
	{
		private: using TUnsignedInt = std::make_unsigned_t<TInt>;

		static_assert(
			((Bits >= 0 && Bits < std::numeric_limits<TUnsignedInt>::digits) && ...),
			"All bit indices must be within range of the given (unsigned) integer type");

		public: static constexpr TInt asInteger{static_cast<TInt>((0 | ... | (static_cast<TUnsignedInt>(1 << Bits))))};
	};

	template <std::integral TInt, std::integral auto... Bits>
	consteval auto bitmaskFrom(std::integer_sequence<TInt, Bits...>)
	{
		return Bitmask<TInt, Bits...>{};
	}

	template <typename TSeq>
	using BitmaskFrom = decltype(bitmaskFrom(TSeq{}));
}

#endif
