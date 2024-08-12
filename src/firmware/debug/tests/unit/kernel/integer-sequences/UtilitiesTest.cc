#include <array>
#include <cstdint>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/integer-sequences/utilities.hh"

using namespace mettle;

using namespace smeg::kernel::integer_sequences;

namespace smeg::tests::unit::kernel::integer_sequences
{
	template <typename T, T... Ints>
	static auto asArray(std::integer_sequence<T, Ints...>)
	{
		return std::array{Ints...};
	}

	suite<> pushFrontTest("pushFront Test Suite", [](auto &unit)
	{
		unit.test("pushFront_calledWithEmptySequence_expectSingleElementSequenceOfSameValue", []()
		{
			const std::integer_sequence<int> emptySequence;
			expect(asArray(pushFront<1>(emptySequence)), array(1));
			expect(asArray(pushFront<-123>(emptySequence)), array(-123));
			expect(asArray(pushFront<456>(emptySequence)), array(456));
		});

		unit.test("pushFront_calledWithSequenceContainingElements_expectNewElementIsPushedToFront", []()
		{
			expect(asArray(pushFront<-6754>(std::integer_sequence<short, 72, 973, 152, 1>{})), array(-6754, 72, 973, 152, 1));
			expect(asArray(pushFront<3>(std::integer_sequence<std::size_t, 1, 4, 1, 5, 9>{})), array(3, 1, 4, 1, 5, 9));
			expect(asArray(pushFront<2>(std::integer_sequence<char, 2>{})), array(2, 2));
		});
	});
}
