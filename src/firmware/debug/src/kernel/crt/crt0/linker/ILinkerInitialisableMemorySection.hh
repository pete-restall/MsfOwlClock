#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_ILINKERINITIALISABLEMEMORYSECTION_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_ILINKERINITIALISABLEMEMORYSECTION_HH
#include "../../../INonConstInitialisable.hh"

namespace smeg::kernel::crt::crt0::linker
{
	template <typename T>
	concept ILinkerInitialisableMemorySection = INonConstInitialisable<T>;
}

#endif
