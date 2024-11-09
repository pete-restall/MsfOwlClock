#ifndef __SMEG_KERNEL_IAPPTODRIVERAPI_HH
#define __SMEG_KERNEL_IAPPTODRIVERAPI_HH
#include <type_traits>

namespace smeg::kernel
{
	template <typename T>
	concept IAppToDriverApi = std::is_class_v<T>; // TODO: Needs to be determined; what should the API look like ?
}

#endif
