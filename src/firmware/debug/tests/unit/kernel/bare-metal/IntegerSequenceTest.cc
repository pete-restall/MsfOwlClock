#include <concepts>
#include <utility>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/bare-metal/IHaveValuesOf.hh"
#include "kernel/bare-metal/IntegerSequence.hh"

using namespace mettle;
using namespace smeg::kernel::bare_metal;

namespace smeg::tests::unit::kernel::bare_metal
{
	template <typename T, T... Ints>
	static auto asVector(std::integer_sequence<T, Ints...>)
	{
		return std::vector{Ints...};
	}

	template <typename T>
	static auto asVector(std::integer_sequence<T>)
	{
		return std::vector<T>{};
	}

	suite<> integerSequenceTest("IntegerSequence Tests", [](auto &unit)
	{
		unit.test("class_testedAgainstIHaveValuesOfConcept_expectTrue", []()
		{
			using seq = std::make_integer_sequence<int, 10>;
			using intSeq = IntegerSequence<seq>;
			expect(IHaveValuesOf<int, intSeq>, equal_to(true));
		});

		unit.test("Values_enumeratedWithSequenceLengthOf1_expectSingleEntryOf0", []()
		{
			using seq = std::make_integer_sequence<int, 1>;
			using intSeq = IntegerSequence<seq>::Values;
			expect(asVector(intSeq{}), array(0));
		});

		unit.test("Values_enumeratedWithSequenceLengthOf5_expect5IncrementingEntriesStartingFrom0", []()
		{
			using seq = std::make_integer_sequence<int, 5>;
			using intSeq = IntegerSequence<seq>::Values;
			expect(asVector(intSeq{}), array(0, 1, 2, 3, 4));
		});

		unit.test("Values_enumeratedWithSequenceLengthOf0_expectNoEntries", []()
		{
			using seq = std::make_integer_sequence<int, 0>;
			using intSeq = IntegerSequence<seq>::Values;
			expect(asVector(intSeq{}).empty(), equal_to(true));
		});
	});
}
