#ifndef __SMEG_KERNEL_IINITIALISABLE_HH
#define __SMEG_KERNEL_IINITIALISABLE_HH
#include "IConstInitialisable.hh"
#include "INonConstInitialisable.hh"

namespace smeg::kernel
{
	template <class T>
	concept IInitialisable = INonConstInitialisable<T> || IConstInitialisable<T>;
}

#endif
