#include <concepts>
#include <utility>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/bare-metal/OffsetIntegerSequence.hh"

using namespace mettle;
using namespace smeg::kernel::bare_metal;

namespace smeg::tests::unit::kernel::bare_metal
{
	template <typename T, T... Ints>
	auto asVector(std::integer_sequence<T, Ints...>)
	{
		return std::vector{Ints...};
	}

	template <typename T>
	auto asVector(std::integer_sequence<T>)
	{
		return std::vector<T>{};
	}

	suite<> offsetSequenceTest("OffsetIntegerSequence Tests", [](auto &unit)
	{
		unit.test("Seq_enumeratedWithOffsetOf0AndSequenceLengthOf1_expectSingleEntryOf0", []()
		{
			using seq = std::make_integer_sequence<int, 1>;
			using offsetSeq = OffsetIntegerSequence<0, seq>::Seq;
			expect(asVector(offsetSeq{}), array(0));
		});

		unit.test("Seq_enumeratedWithOffsetOf1AndSequenceLengthOf1_expectSingleEntryOf1", []()
		{
			using seq = std::make_integer_sequence<int, 1>;
			using offsetSeq = OffsetIntegerSequence<1, seq>::Seq;
			expect(asVector(offsetSeq{}), array(1));
		});

		unit.test("Seq_enumeratedWithOffsetOf2AndSequenceLengthOf1_expectSingleEntryOf2", []()
		{
			using seq = std::make_integer_sequence<int, 1>;
			using offsetSeq = OffsetIntegerSequence<2, seq>::Seq;
			expect(asVector(offsetSeq{}), array(2));
		});

		unit.test("Seq_enumeratedWithOffsetOf0AndSequenceLengthOf5_expect5IncrementingEntriesStartingFrom0", []()
		{
			using seq = std::make_integer_sequence<int, 5>;
			using offsetSeq = OffsetIntegerSequence<0, seq>::Seq;
			expect(asVector(offsetSeq{}), array(0, 1, 2, 3, 4));
		});

		unit.test("Seq_enumeratedWithOffsetOf10AndSequenceLengthOf5_expect5IncrementingEntriesStartingFrom10", []()
		{
			using seq = std::make_integer_sequence<int, 5>;
			using offsetSeq = OffsetIntegerSequence<10, seq>::Seq;
			expect(asVector(offsetSeq{}), array(10, 11, 12, 13, 14));
		});

		unit.test("Seq_enumeratedWithOffsetOfNegative10AndSequenceLengthOf5_expect5IncrementingEntriesStartingFromNegative10", []()
		{
			using seq = std::make_integer_sequence<int, 5>;
			using offsetSeq = OffsetIntegerSequence<-10, seq>::Seq;
			expect(asVector(offsetSeq{}), array(-10, -9, -8, -7, -6));
		});

		unit.test("Seq_enumeratedWithOffsetOfNegative5AndSequenceLengthOf10_expect10IncrementingEntriesStartingFromNegative5AndProgressingThrough0", []()
		{
			using seq = std::make_integer_sequence<int, 10>;
			using offsetSeq = OffsetIntegerSequence<-5, seq>::Seq;
			expect(asVector(offsetSeq{}), array(-5, -4, -3, -2, -1, 0, 1, 2, 3, 4));
		});

		unit.test("Seq_enumeratedWithAnyOffsetAndSequenceLengthOf0_expectNoEntries", []()
		{
			using seq = std::make_integer_sequence<int, 0>;
			using offsetSeq = OffsetIntegerSequence<0, seq>::Seq;
			expect(asVector(offsetSeq{}).empty(), equal_to(true));
		});
	});
}
