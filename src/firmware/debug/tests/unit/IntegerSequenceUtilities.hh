#ifndef __SMEG_TESTS_UNIT_INTEGERSEQUENCEUTILITIES_HH
#define __SMEG_TESTS_UNIT_INTEGERSEQUENCEUTILITIES_HH
#include <algorithm>
#include <array>
#include <utility>
#include <vector>

namespace smeg::tests::unit
{
	template <typename T, T... Ints>
	auto asArray(std::integer_sequence<T, Ints...>)
	{
		return std::array<T, sizeof...(Ints)>{Ints...};
	}

	template <typename T, T... Ints>
	auto asSortedArray(std::integer_sequence<T, Ints...>)
	{
		std::array<T, sizeof...(Ints)> array{Ints...};
		std::sort(array.begin(), array.end());
		return array;
	}

	template <typename T, T... Ints>
	auto asVector(std::integer_sequence<T, Ints...>)
	{
		return std::vector<T>{Ints...};
	}
}

#endif
