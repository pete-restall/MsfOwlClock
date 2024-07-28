#ifndef __SMEG_KERNEL_ICONSTINITIALISABLE_HH
#define __SMEG_KERNEL_ICONSTINITIALISABLE_HH
#include <concepts>

namespace smeg::kernel
{
	template <typename T>
	concept IConstInitialisable = requires(const T &obj)
	{
		{ obj.initialise() } -> std::same_as<void>;
	};
}

#endif
