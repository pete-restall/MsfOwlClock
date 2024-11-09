#ifndef __SMEG_KERNEL_IDRIVERTODRIVERAPI_HH
#define __SMEG_KERNEL_IDRIVERTODRIVERAPI_HH
#include <type_traits>

namespace smeg::kernel
{
	template <typename T>
	concept IDriverToDriverApi = std::is_class_v<T>; // TODO: Needs to be determined; what should the API look like ?
}

#endif
