#ifndef __SMEG_KERNEL_DRIVERS_ISYSCALLAPI_HH
#define __SMEG_KERNEL_DRIVERS_ISYSCALLAPI_HH
#include <type_traits>

namespace smeg::kernel::drivers
{
	template <typename T>
	concept ISyscallApi = std::is_class_v<T>; // TODO: Needs to be determined; what should the API look like ?  Should have a 'noexcept' constructor to prevent leakage during initialisation of per-core statics...
}

#endif
