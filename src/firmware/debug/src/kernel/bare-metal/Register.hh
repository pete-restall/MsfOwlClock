#ifndef __SMEG_KERNEL_BAREMETAL_REGISTER_HH
#define __SMEG_KERNEL_BAREMETAL_REGISTER_HH
#include <atomic>

namespace smeg::kernel::bare_metal
{
	using RegisterU32 = volatile std::atomic_uint32_t;
}

#endif
