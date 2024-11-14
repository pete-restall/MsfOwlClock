#ifndef __SMEG_KERNEL_TUPLES_TUPLECAT_HH
#define __SMEG_KERNEL_TUPLES_TUPLECAT_HH
#include <tuple>

namespace smeg::kernel::tuples
{
	template <typename... T>
	using TupleCat = decltype(std::tuple_cat(std::declval<T>() ...));
}

#endif
