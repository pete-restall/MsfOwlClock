#ifndef __SMEG_KERNEL_ISYSCALL_HH
#define __SMEG_KERNEL_ISYSCALL_HH
#include <concepts>

#include "ISyscallHandlerContext.hh"

namespace smeg::kernel
{
	template <typename T, template <typename> typename TSyscallFor>
	concept _$ISyscallWithConstStructArg =
		requires(const T &arg, typename TSyscallFor<T>::Handler &handler, _$DummySyscallHandlerContext &context)
		{
			{ handler.onSyscall(context, arg) } -> std::same_as<void>;
		};

	template <typename T, template <typename> typename TSyscallFor>
	concept _$ISyscallWithNonConstStructArg =
		requires(T &arg, typename TSyscallFor<T>::Handler &handler, _$DummySyscallHandlerContext &context)
		{
			{ handler.onSyscall(context, arg) } -> std::same_as<void>;
		};

	template <typename T, template <typename> typename TSyscallFor>
	concept ISyscall = _$ISyscallWithConstStructArg<T, TSyscallFor> || _$ISyscallWithNonConstStructArg<T, TSyscallFor>;
}

#endif
