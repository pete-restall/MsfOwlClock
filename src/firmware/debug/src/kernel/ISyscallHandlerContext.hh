#ifndef __SMEG_KERNEL_ISYSCALLHANDLERCONTEXT_HH
#define __SMEG_KERNEL_ISYSCALLHANDLERCONTEXT_HH
#include <type_traits>

namespace smeg::kernel
{
	template <typename T>
	concept ISyscallHandlerContext = std::is_class_v<T>; // TODO: Need to define what goes into this; probably things like a pointer to the current Task Control Block, etc.

	struct _DummySyscallHandlerContext
	{
		static_assert(ISyscallHandlerContext<_DummySyscallHandlerContext>, "_DummySyscallHandlerContext must be an ISyscallHandlerContext");
	};
}

#endif
