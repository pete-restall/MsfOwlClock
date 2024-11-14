#ifndef __SMEG_KERNEL_TUPLES_ASTUPLE_HH
#define __SMEG_KERNEL_TUPLES_ASTUPLE_HH
#include <tuple>
#include <type_traits>

namespace smeg::kernel::tuples
{
	template <typename T>
	using AsTuple = decltype(std::tuple_cat(std::declval<T>()));
}

#endif
