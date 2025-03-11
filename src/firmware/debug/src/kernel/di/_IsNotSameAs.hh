#ifndef __SMEG_KERNEL_DI__ISNOTSAMEAS_HH
#define __SMEG_KERNEL_DI__ISNOTSAMEAS_HH
#include <type_traits>

namespace smeg::kernel::di
{
	template <typename T, typename TNot>
	concept _$IsNotSameAs = !std::is_same_v<T, TNot>;
}

#endif
