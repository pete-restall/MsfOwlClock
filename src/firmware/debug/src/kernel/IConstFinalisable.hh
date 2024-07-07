#ifndef __SMEG_KERNEL_ICONSTFINALISABLE_HH
#define __SMEG_KERNEL_ICONSTFINALISABLE_HH
#include <concepts>

namespace smeg::kernel
{
	template <class T>
	concept IConstFinalisable = requires(const T &obj)
	{
		{ obj.finalise() } -> std::same_as<void>;
	};
}

#endif
