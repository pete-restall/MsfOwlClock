#ifndef __SMEG_TESTS_UNIT_INTEGERSEQUENCEUTILITIES_HH
#define __SMEG_TESTS_UNIT_INTEGERSEQUENCEUTILITIES_HH
#include <utility>
#include <vector>

namespace smeg::tests::unit
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
}

#endif
