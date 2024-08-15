#include <array>
#include <cstdint>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/integer-sequences/SortedSet.hh"

#include "../../IntegerSequenceUtilities.hh"

using namespace mettle;

using namespace smeg::kernel::integer_sequences;

namespace smeg::tests::unit::kernel::integer_sequences
{
	suite<> sortedSetTest("SortedSet Test Suite", [](auto &unit)
	{
		unit.test("Ascending_getWithEmptySequence_expectEmptySequence", []()
		{
			expect(asArray(SortedSet<int>::Ascending{}), array());
			expect(asArray(SortedSet<std::size_t>::Ascending{}), array());
		});

		unit.test("Ascending_getWithSingleElement_expectSameElement", []()
		{
			expect(asArray(SortedSet<int, -18>::Ascending{}), array(-18));
			expect(asArray(SortedSet<std::size_t, 44>::Ascending{}), array(44));
		});

		unit.test("Ascending_getWithDuplicatedElement_expectSingleUniqueElement", []()
		{
			expect(asArray(SortedSet<int, -9834, -9834>::Ascending{}), array(-9834));
			expect(asArray(SortedSet<std::size_t, 8, 8, 8, 8, 8>::Ascending{}), array(8));
		});

		unit.test("Ascending_getWithOutOfOrderElements_expectUniqueElementsSortedInAscendingOrder", []()
		{
			expect(asArray(SortedSet<int, 0, -87, 90, -87, 12845, 42, 12845, -928456>::Ascending{}), array(-928456, -87, 0, 42, 90, 12845));
			expect(asArray(SortedSet<std::size_t, 777, 14536, 372, 16, 0, 372>::Ascending{}), array(0, 16, 372, 777, 14536));
		});

		unit.test("Descending_getWithEmptySequence_expectEmptySequence", []()
		{
			expect(asArray(SortedSet<int>::Descending{}), array());
			expect(asArray(SortedSet<std::size_t>::Descending{}), array());
		});

		unit.test("Descending_getWithSingleElement_expectSameElement", []()
		{
			expect(asArray(SortedSet<int, 871263>::Descending{}), array(871263));
			expect(asArray(SortedSet<std::size_t, 1>::Descending{}), array(1));
		});

		unit.test("Decending_getWithDuplicatedElement_expectSingleUniqueElement", []()
		{
			expect(asArray(SortedSet<int, 3, 3, 3, 3, 3>::Descending{}), array(3));
			expect(asArray(SortedSet<std::size_t, 18273757, 18273757>::Descending{}), array(18273757));
		});

		unit.test("Descending_getWithOutOfOrderElements_expectUniqueElementsSortedInDescendingOrder", []()
		{
			expect(asArray(SortedSet<int, 0, 18, 2, 7365, 90892, 3, 0, 7, 42378639, 8, 45790>::Descending{}), array(42378639, 90892, 45790, 7365, 18, 8, 7, 3, 2, 0));
			expect(asArray(SortedSet<std::size_t, 87, 9, 26, 4, 3, 3, 3>::Descending{}), array(87, 26, 9, 4, 3));
		});
	});
}
