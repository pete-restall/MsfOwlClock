#ifndef __SMEG_KERNEL_ISYSCALL_HH
#define __SMEG_KERNEL_ISYSCALL_HH
#include <concepts>
#include <cstdint>
#include <type_traits>

#include "ISyscallHandlerContext.hh"

namespace smeg::kernel
{
	template <typename T, template <typename> typename TSyscallFor>
	concept ISyscallWithIntegerArg = requires(
		const T &arg,
		typename TSyscallFor<T>::Handler &handler,
		_DummySyscallHandlerContext &context,
		std::uint32_t value)
	{
		{ handler.onSyscall(context, value) } -> std::same_as<void>;
		{ arg.getValue() } -> std::convertible_to<std::uint32_t>;
	};

	template <typename T, template <typename> typename TSyscallFor>
	concept ISyscallWithConstStructArg =
		!ISyscallWithIntegerArg<T, TSyscallFor> &&
		requires(const T &arg, typename TSyscallFor<T>::Handler &handler, _DummySyscallHandlerContext &context)
		{
			{ handler.onSyscall(context, arg) } -> std::same_as<void>;
		};

	template <typename T, template <typename> typename TSyscallFor>
	concept ISyscallWithNonConstStructArg =
		!ISyscallWithIntegerArg<T, TSyscallFor> &&
		requires(T &arg, typename TSyscallFor<T>::Handler &handler, _DummySyscallHandlerContext &context)
		{
			{ handler.onSyscall(context, arg) } -> std::same_as<void>;
		};

	template <typename T, template <typename> typename TSyscallFor>
	concept ISyscallWithStructArg = ISyscallWithConstStructArg<T, TSyscallFor> || ISyscallWithNonConstStructArg<T, TSyscallFor>;

	template <typename T, template <typename> typename TSyscallFor>
	concept ISyscallWithNoArgs =
		!ISyscallWithIntegerArg<T, TSyscallFor> &&
		!ISyscallWithStructArg<T, TSyscallFor> &&
		requires(typename TSyscallFor<T>::Handler &handler, _DummySyscallHandlerContext &context)
		{
			{ handler.onSyscall(context) } -> std::same_as<void>;
		};

	template <typename T, template <typename> typename TSyscallFor>
	concept ISyscall = ISyscallWithNoArgs<T, TSyscallFor> || ISyscallWithIntegerArg<T, TSyscallFor> || ISyscallWithStructArg<T, TSyscallFor>;
}

#endif
