#include <cstddef>
#include <cstdint>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/integer-sequences/Unique.hh"

#include "../../IntegerSequenceUtilities.hh"

using namespace mettle;

using namespace smeg::kernel::integer_sequences;

namespace smeg::tests::unit::kernel::integer_sequences
{
	suite<> uniqueTest("Unique Test Suite", [](auto &unit)
	{
		unit.test("Values_getWithEmptySequence_expectEmptySequence", []()
		{
			expect(asArray(Unique<int>::Values{}), array());
			expect(asArray(Unique<std::size_t>::Values{}), array());
		});

		unit.test("Values_getWithSingleElement_expectSameElement", []()
		{
			expect(asArray(Unique<int, -46>::Values{}), array(-46));
			expect(asArray(Unique<char, 0>::Values{}), array(0));
			expect(asArray(Unique<std::size_t, 981247>::Values{}), array(981247));
		});

		unit.test("Values_getWithDuplicatedElement_expectSingleElement", []()
		{
			expect(asArray(Unique<int, -11, -11>::Values{}), array(-11));
			expect(asArray(Unique<long, 0, 0, 0>::Values{}), array(0));
			expect(asArray(Unique<std::size_t, 120, 120, 120, 120, 120, 120, 120, 120, 120>::Values{}), array(120));
		});

		unit.test("Values_getWithDuplicatedAndUnduplicatedElements_expectEachElementExactlyOnceInUnspecifiedOrder", []()
		{
			expect(asSortedArray(Unique<short, -3, 5, 5>::Values{}), array(-3, 5));
			expect(asSortedArray(Unique<std::int32_t, -78, -78, 10, 11, 12, 11, 10, -10, -78>::Values{}), array(-78, -10, 10, 11, 12));
			expect(asSortedArray(Unique<std::size_t, 1, 2, 3, 2, 1, 0, 2, 4, 6, 4, 2, 0, 1, 2, 3>::Values{}), array(0, 1, 2, 3, 4, 6));
		});
	});
}
