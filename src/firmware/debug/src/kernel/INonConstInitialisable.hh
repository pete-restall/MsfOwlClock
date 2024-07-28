#ifndef __SMEG_KERNEL_INONCONSTINITIALISABLE_HH
#define __SMEG_KERNEL_INONCONSTINITIALISABLE_HH
#include <concepts>

namespace smeg::kernel
{
	template <typename T>
	concept INonConstInitialisable = requires(T &obj)
	{
		{ obj.initialise() } -> std::same_as<void>;
	};
}

#endif
