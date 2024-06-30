#ifndef __SMEG_KERNEL_ICONSTINITIALISABLE_HH
#define __SMEG_KERNEL_ICONSTINITIALISABLE_HH
#include <type_traits>

namespace smeg::kernel
{
	template <class T>
	concept IConstInitialisable = requires(const T &obj)
	{
		{ obj.initialise() } -> std::same_as<void>;
	};
}

#endif
