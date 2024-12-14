#ifndef __SMEG_KERNEL_IHANDLESYSCALL_HH // TODO: MOVE INTO kernel/drivers WITH ISyscallHandlerContext.hh ?  Only drivers ought to be providing implementations of these...
#define __SMEG_KERNEL_IHANDLESYSCALL_HH
#include <concepts>
#include <type_traits>

#include "ISyscallHandlerContext.hh"

namespace smeg::kernel
{
	template <typename T, typename TArg>
	concept _$IHandleSyscallWithConstStructArg =
		std::is_class_v<TArg> &&
		requires(T &handler, _$DummySyscallHandlerContext &context, const TArg &arg)
		{
			{ handler.onSyscall(context, arg) } -> std::same_as<void>;
		};

	template <typename T, typename TArg>
	concept _$IHandleSyscallWithNonConstStructArg =
		std::is_class_v<TArg> &&
		requires(T &handler, _$DummySyscallHandlerContext &context, TArg &arg)
		{
			{ handler.onSyscall(context, arg) } -> std::same_as<void>;
		};

	template <typename... T>
	struct _$SyscallHandlerTraits
	{
		static constexpr bool isHandlerWithStructArg = false;
	};

	template <typename T, ISyscallHandlerContext TContext, typename TArg>
	struct _$SyscallHandlerTraits<void (T::*)(TContext &, TArg &)>
	{
		static constexpr bool isHandlerWithStructArg = true;
	};

	template <typename T, typename TArg>
	concept IHandleSyscallFor = _$IHandleSyscallWithConstStructArg<T, TArg> || _$IHandleSyscallWithNonConstStructArg<T, TArg>;

	template <typename T>
	concept IHandleSyscallWithAnyArg = _$SyscallHandlerTraits<decltype(&T::onSyscall)>::isHandlerWithStructArg;
}

#endif
