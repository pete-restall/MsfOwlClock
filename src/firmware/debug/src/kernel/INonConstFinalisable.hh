#ifndef __SMEG_KERNEL_INONCONSTFINALISABLE_HH
#define __SMEG_KERNEL_INONCONSTFINALISABLE_HH
#include <concepts>

namespace smeg::kernel
{
	template <class T>
	concept INonConstFinalisable = requires(T &obj)
	{
		{ obj.finalise() } -> std::same_as<void>;
	};
}

#endif
