#ifndef __SMEG_KERNEL_DRIVERS_IISRAPI_HH
#define __SMEG_KERNEL_DRIVERS_IISRAPI_HH
#include <type_traits>

namespace smeg::kernel::drivers
{
	template <typename T>
	concept IIsrApi = std::is_class_v<T>; // TODO: Needs to be determined; what should the API look like ?
}

#endif
