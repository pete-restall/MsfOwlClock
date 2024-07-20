#include <concepts>
#include <limits>
#include <type_traits>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/bare-metal/Bitmask.hh"

using namespace mettle;
using namespace smeg::kernel::bare_metal;

namespace smeg::tests::unit::kernel::bare_metal
{
	template <typename T, int... Bits>
	static void asInteger_getWhenSingleBitSpecifiedInTurn_expectCorrectMask(void)
	{
		for (auto p : {(std::make_pair(Bitmask<T, Bits>::asInteger, static_cast<T>(1 << Bits)))...})
			expect(p.first, equal_to(p.second));
	}

	template <typename T, int... Bits>
	static void asInteger_getWhenSingleBitSpecifiedInTurn_expectCorrectMask(std::integer_sequence<int, Bits...>)
	{
		asInteger_getWhenSingleBitSpecifiedInTurn_expectCorrectMask<T, Bits...>();
	}

	template <typename T, int Offset>
	static void asInteger_getWhenAlternatingPatternInSuccessiveBytes_expectCorrectMasks(void)
	{
		expect(Bitmask<T, Offset + 0, Offset + 2, Offset + 4, Offset + 6>::asInteger, equal_to(static_cast<T>(0x55 << Offset)));
		if constexpr (sizeof(T) > Offset / 8 + 1)
			asInteger_getWhenAlternatingPatternInSuccessiveBytes_expectCorrectMasks<T, Offset + 8>();
	}

	suite<> bitmaskTest("Bitmask Tests", [](auto &suite)
	{
		subsuite<std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t>(suite, "Bitmask Struct Tests", [](auto &unit)
		{
			unit.test("asInteger_getWhenNoBits_expect0", [](auto intType)
			{
				using T = decltype(intType);
				expect(Bitmask<T>::asInteger, equal_to(0));
			});

			unit.test("asInteger_getWhenSingleBitSpecifiedInTurn_expectCorrectMask", [](auto intType)
			{
				using T = decltype(intType);
				using TUnsigned = std::make_unsigned_t<T>;
				using bitNumbers = std::make_integer_sequence<int, std::numeric_limits<TUnsigned>::digits>;
				asInteger_getWhenSingleBitSpecifiedInTurn_expectCorrectMask<T>(bitNumbers{});
			});

			unit.test("asInteger_getWhenFirstAndLastBitsSpecifiedInOrder_expectCorrectMask", [](auto intType)
			{
				using T = decltype(intType);
				using TUnsigned = std::make_unsigned_t<T>;
				constexpr auto firstBit(0);
				constexpr auto lastBit(std::numeric_limits<TUnsigned>::digits - 1);
				expect(Bitmask<T, firstBit, lastBit>::asInteger, equal_to(static_cast<T>(1 | (1 << lastBit))));
			});

			unit.test("asInteger_getWhenFirstAndLastBitsSpecifiedOutOfOrder_expectCorrectMask", [](auto intType)
			{
				using T = decltype(intType);
				using TUnsigned = std::make_unsigned_t<T>;
				constexpr auto firstBit(0);
				constexpr auto lastBit(std::numeric_limits<TUnsigned>::digits - 1);
				expect(Bitmask<T, lastBit, firstBit>::asInteger, equal_to(static_cast<T>(1 | (1 << lastBit))));
			});

			unit.test("asInteger_getWhenSameBitIsSpecifiedMultipleTimes_expectCorrectMask", [](auto intType)
			{
				using T = decltype(intType);
				expect(Bitmask<T, 6, 6, 6>::asInteger, equal_to(1 << 6));
			});

			unit.test("asInteger_getWhenAlternatingPatternInSuccessiveBytes_expectCorrectMasks", [](auto intType)
			{
				using T = decltype(intType);
				asInteger_getWhenAlternatingPatternInSuccessiveBytes_expectCorrectMasks<T, 0>();
				asInteger_getWhenAlternatingPatternInSuccessiveBytes_expectCorrectMasks<T, 1>();
			});

			unit.test("asInteger_getWhenAllBitsSpecified_expectCorrectMask", [](auto intType)
			{
				using T = decltype(intType);
				using TUnsigned = std::make_unsigned_t<T>;
				using bitmask = BitmaskFrom<std::make_integer_sequence<T, std::numeric_limits<TUnsigned>::digits>>;
				expect(bitmask::asInteger, equal_to(static_cast<T>(~0)));
			});
		});

		subsuite<std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t>(suite, "Bitmask Function Tests", [](auto &unit)
		{
			unit.test("bitmaskFrom_getWhenNoBitsInSequence_expectBitmaskIsAllUnset", [](auto intType)
			{
				using T = decltype(intType);
				using TNoBitsSeq = std::make_integer_sequence<T, 0>;
				using bitmask = decltype(bitmaskFrom(TNoBitsSeq{}));
				expect(bitmask::asInteger, equal_to(0));
			});

			unit.test("bitmaskFrom_getWhenAllBitsInSequence_expectBitmaskIsAllSet", [](auto intType)
			{
				using T = decltype(intType);
				using TUnsigned = std::make_unsigned_t<T>;
				using TAllBitsSeq = std::make_integer_sequence<T, std::numeric_limits<TUnsigned>::digits>;
				using bitmask = decltype(bitmaskFrom(TAllBitsSeq{}));
				expect(bitmask::asInteger, equal_to(static_cast<T>(~0)));
			});
		});
	});
}
