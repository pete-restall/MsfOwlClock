#ifndef __SMEG_KERNEL_INONCONSTINITIALISABLE_HH
#define __SMEG_KERNEL_INONCONSTINITIALISABLE_HH
#include <type_traits>

namespace smeg::kernel
{
	template <class T>
	concept INonConstInitialisable = requires(T &obj)
	{
		{ obj.initialise() } -> std::same_as<void>;
	};
}

#endif
