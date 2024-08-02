#ifndef __SMEG_TESTS_UNIT_TUPLEUTILITIES_HH
#define __SMEG_TESTS_UNIT_TUPLEUTILITIES_HH
#include <tuple>

namespace smeg::tests::unit
{
	template <typename T>
	constexpr auto popFront(T &tuple)
	{
		static_assert(std::tuple_size_v<T> > 0, "An empty tuple does not have a front element available to pop");
		return std::apply([](auto, auto... back) noexcept { return std::make_tuple(back...); }, tuple);
	}
}

#endif
