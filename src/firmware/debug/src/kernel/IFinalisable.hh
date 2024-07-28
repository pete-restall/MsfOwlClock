#ifndef __SMEG_KERNEL_IFINALISABLE_HH
#define __SMEG_KERNEL_IFINALISABLE_HH
#include "IConstFinalisable.hh"
#include "INonConstFinalisable.hh"

namespace smeg::kernel
{
	template <typename T>
	concept IFinalisable = INonConstFinalisable<T> || IConstFinalisable<T>;
}

#endif
