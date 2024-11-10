#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/bare-metal/BitfieldTraits.hh"
#include "kernel/bare-metal/Bitmask.hh"

#include "../../IntegerSequenceUtilities.hh"

using namespace mettle;
using namespace smeg::kernel::bare_metal;

namespace smeg::tests::unit::kernel::bare_metal
{
	template <typename TInt, std::size_t... BitIndices>
	static void leftIndex_get_expectSameValueAsLeftIndexTemplateParameter(std::integer_sequence<std::size_t, BitIndices...>)
	{
		constexpr std::array traitLeftIndices{(BitfieldTraits<TInt, BitIndices>::leftIndex)...};
		expect(traitLeftIndices, array(BitIndices...));
	}

	template <typename TInt, std::size_t LeftIndex, std::size_t... NumBits>
	static void rightIndex_get_expectRightIndexIsNumberOfBitsAwayExclusive(std::integer_sequence<std::size_t, NumBits...>)
	{
		constexpr std::array traitRightIndices{(BitfieldTraits<TInt, LeftIndex, NumBits>::rightIndex)...};
		expect(traitRightIndices, array((LeftIndex - (NumBits - 1))...));
	}

	template <typename TInt, std::size_t LeftIndex, std::size_t NumBits, std::size_t... BitIndices>
	static void indices_getWhenUsingAllBits_expect(std::integer_sequence<std::size_t, BitIndices...>)
	{
		auto indices(asVector(typename BitfieldTraits<TInt, LeftIndex, NumBits>::Indices{}));
		expect(indices, array(BitIndices...));
	}

	template <typename TInt, std::size_t... BitIndices>
	static void indices_getWhenUsingEachSingleBit_expect(std::integer_sequence<std::size_t, BitIndices...>)
	{
		std::vector indices{asVector(typename BitfieldTraits<TInt, BitIndices, 1>::Indices{})...};
		expect(indices, array((std::vector{BitIndices})...));
	}

	template <typename T>
	using IsBitmaskConstructedFromIndicesOf = std::is_convertible<typename T::Mask, BitmaskFrom<typename T::Indices>>;

	suite<> bitfieldTraitsTest("BitfieldTraits Tests", [](auto &suite)
	{
		subsuite<std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t>(suite, "Bitmask Struct Tests", [](auto &unit)
		{
			unit.test("leftIndex_get_expectSameValueAsLeftIndexTemplateParameter", [](auto intType)
			{
				using TInt = decltype(intType);
				using TUnsignedInt = std::make_unsigned_t<TInt>;
				using BitIndices = std::make_index_sequence<std::numeric_limits<TUnsignedInt>::digits>;
				leftIndex_get_expectSameValueAsLeftIndexTemplateParameter<TInt>(BitIndices{});
			});

			unit.test("rightIndex_getWhenLeftIndexIsMostSignificantBit_expectRightIndexIsNumberOfBitsAwayExclusive", [](auto intType)
			{
				using TInt = decltype(intType);
				using TUnsignedInt = std::make_unsigned_t<TInt>;
				constexpr auto msb = std::numeric_limits<TUnsignedInt>::digits - 1;
				using NumBits = OffsetIntegerSequence<std::size_t(1), std::make_index_sequence<msb + 1>>;
				rightIndex_get_expectRightIndexIsNumberOfBitsAwayExclusive<TInt, msb>(typename NumBits::Values{});
			});

			unit.test("rightIndex_getWhenLeftIndexIsNotMostSignificantBit_expectRightIndexIsNumberOfBitsAwayExclusive", [](auto intType)
			{
				using TInt = decltype(intType);
				using TUnsignedInt = std::make_unsigned_t<TInt>;
				constexpr auto leftIndex = std::numeric_limits<TUnsignedInt>::digits - 5;
				using NumBits = OffsetIntegerSequence<std::size_t(1), std::make_index_sequence<leftIndex + 1>>;
				rightIndex_get_expectRightIndexIsNumberOfBitsAwayExclusive<TInt, leftIndex>(typename NumBits::Values{});
			});

			unit.test("Indices_getWhenUsingAllBitsInField_expectEachBitIndexStartingFromTheLeastSignificantBit", [](auto intType)
			{
				using TInt = decltype(intType);
				using TUnsignedInt = std::make_unsigned_t<TInt>;
				using BitIndices = std::make_index_sequence<std::numeric_limits<TUnsignedInt>::digits>;
				constexpr auto numBits = std::numeric_limits<TUnsignedInt>::digits;
				constexpr auto msb = numBits - 1;
				indices_getWhenUsingAllBits_expect<TInt, msb, numBits>(BitIndices{});
			});

			unit.test("Indices_getWhenUsingSingleBit_expectEachCorrespondingBit", [](auto intType)
			{
				using TInt = decltype(intType);
				using TUnsignedInt = std::make_unsigned_t<TInt>;
				using BitIndices = std::make_index_sequence<std::numeric_limits<TUnsignedInt>::digits>;
				indices_getWhenUsingEachSingleBit_expect<TInt>(BitIndices{});
			});

			unit.test("Mask_getForSampleOfBitfields_expectBitmaskWithSameParameters", [](auto intType)
			{
				using TInt = decltype(intType);
				using TUnsignedInt = std::make_unsigned_t<TInt>;
				constexpr auto numBits = std::numeric_limits<TUnsignedInt>::digits;
				constexpr auto msb = numBits - 1;
				std::vector samples
				{
					IsBitmaskConstructedFromIndicesOf<BitfieldTraits<TInt, 7, 3>>::value,
					IsBitmaskConstructedFromIndicesOf<BitfieldTraits<TInt, msb, 6>>::value,
					IsBitmaskConstructedFromIndicesOf<BitfieldTraits<TInt, msb, numBits>>::value,
					IsBitmaskConstructedFromIndicesOf<BitfieldTraits<TInt, 0, 1>>::value
				};

				expect(samples, each(equal_to(true)));
			});
		});
	});
}
