#ifndef __SMEG_KERNEL_TASKS_IAPPTASKAPI_HH
#define __SMEG_KERNEL_TASKS_IAPPTASKAPI_HH
#include <type_traits>

namespace smeg::kernel::tasks
{
	template <typename T>
	concept IAppTaskApi = std::is_class_v<T>; // TODO: Needs to be determined; what should the API look like ?
}

#endif
