#include <array>
#include <cstddef>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/integer-sequences/BubbleSorted.hh"

#include "../../IntegerSequenceUtilities.hh"

using namespace mettle;

using namespace smeg::kernel::integer_sequences;

namespace smeg::tests::unit::kernel::integer_sequences
{
	suite<> bubbleSortedTest("BubbleSorted Test Suite", [](auto &unit)
	{
		unit.test("bubbleSortedAscending_calledWithIntegerSequence_expectSortedIntegerSequenceIsReturned", []()
		{
			std::array assertions
			{
				typeid(bubbleSortedAscending(std::integer_sequence<int>{})) == typeid(std::integer_sequence<int>{}),
				typeid(bubbleSortedAscending(std::integer_sequence<int, 3, 2, 1>{})) == typeid(std::integer_sequence<int, 1, 2, 3>{}),
				typeid(bubbleSortedAscending(std::index_sequence<3, 1, 2>{})) == typeid(std::index_sequence<1, 2, 3>{}),
				typeid(bubbleSortedAscending(std::integer_sequence<char, 6, 4, 2, 0, -2>{})) == typeid(std::integer_sequence<char, -2, 0, 2, 4, 6>{})
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("bubbleSortedDescending_calledWithIntegerSequence_expectSortedIntegerSequenceIsReturned", []()
		{
			std::array assertions
			{
				typeid(bubbleSortedDescending(std::integer_sequence<int>{})) == typeid(std::integer_sequence<int>{}),
				typeid(bubbleSortedDescending(std::integer_sequence<int, 1, 3, 2>{})) == typeid(std::integer_sequence<int, 3, 2, 1>{}),
				typeid(bubbleSortedDescending(std::index_sequence<1, 3, 2>{})) == typeid(std::index_sequence<3, 2, 1>{}),
				typeid(bubbleSortedDescending(std::integer_sequence<char, -2, 0, 2, 4, 6>{})) == typeid(std::integer_sequence<char, 6, 4, 2, 0, -2>{})
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("Ascending_getWithEmptySequence_expectEmptySequence", []()
		{
			expect(asArray(BubbleSorted<int>::Ascending{}), array());
			expect(asArray(BubbleSorted<std::size_t>::Ascending{}), array());
		});

		unit.test("Ascending_getWithSingleElement_expectSameElement", []()
		{
			expect(asArray(BubbleSorted<int, -69>::Ascending{}), array(-69));
			expect(asArray(BubbleSorted<std::size_t, 13>::Ascending{}), array(13));
		});

		unit.test("Ascending_getWithDuplicatedElement_expectSameElements", []()
		{
			expect(asArray(BubbleSorted<int, -234, -234>::Ascending{}), array(-234, -234));
			expect(asArray(BubbleSorted<std::size_t, 87234, 87234, 87234, 87234, 87234>::Ascending{}), array(87234, 87234, 87234, 87234, 87234));
		});

		unit.test("Ascending_getWithOutOfOrderElements_expectElementsSortedInAscendingOrder", []()
		{
			expect(asArray(BubbleSorted<int, 877, 10, 253, 666, 10, 5644, -823, 9834>::Ascending{}), array(-823, 10, 10, 253, 666, 877, 5644, 9834));
			expect(asArray(BubbleSorted<std::size_t, 782332, 0, 5, 1278, 28, 0>::Ascending{}), array(0, 0, 5, 28, 1278, 782332));
		});

		unit.test("Descending_getWithEmptySequence_expectEmptySequence", []()
		{
			expect(asArray(BubbleSorted<int>::Descending{}), array());
			expect(asArray(BubbleSorted<std::size_t>::Descending{}), array());
		});

		unit.test("Descending_getWithSingleElement_expectSameElement", []()
		{
			expect(asArray(BubbleSorted<int, 23>::Descending{}), array(23));
			expect(asArray(BubbleSorted<std::size_t, 872>::Descending{}), array(872));
		});

		unit.test("Decending_getWithDuplicatedElement_expectSameElements", []()
		{
			expect(asArray(BubbleSorted<int, 9, 9, 9, 9, 9>::Descending{}), array(9, 9, 9, 9, 9));
			expect(asArray(BubbleSorted<std::size_t, 2415, 2415>::Descending{}), array(2415, 2415));
		});

		unit.test("Descending_getWithOutOfOrderElements_expectElementsSortedInDescendingOrder", []()
		{
			expect(asArray(BubbleSorted<int, 877, 10, 253, 666, 10, 5644, -823, 9834>::Descending{}), array(9834, 5644, 877, 666, 253, 10, 10, -823));
			expect(asArray(BubbleSorted<std::size_t, 782332, 0, 5, 1278, 28, 0>::Descending{}), array(782332, 1278, 28, 5, 0, 0));
		});
	});
}
