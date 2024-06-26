#ifndef __SMEG_KERNEL_IINITIALISABLE_HH
#define __SMEG_KERNEL_IINITIALISABLE_HH

namespace smeg::kernel
{
	template <class T>
	concept IInitialisable = requires(const T &obj)
	{
		{ obj.initialise() };
	};
}

#endif
