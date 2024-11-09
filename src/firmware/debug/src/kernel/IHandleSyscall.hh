#ifndef __SMEG_KERNEL_IHANDLESYSCALL_HH
#define __SMEG_KERNEL_IHANDLESYSCALL_HH
#include <concepts>
#include <cstdint>
#include <type_traits>

#include "ISyscallHandlerContext.hh"

namespace smeg::kernel
{
	template <typename T>
	concept IHandleSyscallWithIntegerArg = requires(const T &handler, _DummySyscallHandlerContext &context, std::uint32_t value)
	{
		{ handler.onSyscall(context, value) } -> std::same_as<void>;
	};

	template <typename T, typename TArg>
	concept IHandleSyscallWithConstStructArg =
		std::is_class_v<TArg> &&
		!IHandleSyscallWithIntegerArg<T> &&
		requires(T &handler, _DummySyscallHandlerContext &context, const TArg &arg)
		{
			{ handler.onSyscall(context, arg) } -> std::same_as<void>;
		};

	template <typename T, typename TArg>
	concept IHandleSyscallWithNonConstStructArg =
		std::is_class_v<TArg> &&
		!IHandleSyscallWithIntegerArg<T> &&
		requires(T &handler, _DummySyscallHandlerContext &context, TArg &arg)
		{
			{ handler.onSyscall(context, arg) } -> std::same_as<void>;
		};

	template <typename T, typename TArg>
	concept IHandleSyscallWithStructArg = IHandleSyscallWithConstStructArg<T, TArg> || IHandleSyscallWithNonConstStructArg<T, TArg>;

	template <typename... T>
	struct _SyscallHandlerTraits
	{
		static constexpr bool isHandlerWithStructArg = false;
	};

	template <typename T, ISyscallHandlerContext TContext, typename TArg>
	struct _SyscallHandlerTraits<void (T::*)(TContext &, TArg &)>
	{
		static constexpr bool isHandlerWithStructArg = true;
	};

	template <typename T>
	concept IHandleSyscallWithAnyStructArg = _SyscallHandlerTraits<decltype(&T::onSyscall)>::isHandlerWithStructArg;

	template <typename T>
	concept IHandleSyscallWithNoArg =
		!IHandleSyscallWithIntegerArg<T> &&
		!IHandleSyscallWithAnyStructArg<T> &&
		requires(T &handler, _DummySyscallHandlerContext &context)
		{
			{ handler.onSyscall(context) } -> std::same_as<void>;
		};

	template <typename T, typename TArg>
	concept IHandleSyscallFor =
		!IHandleSyscallWithNoArg<T> && (
			(std::convertible_to<TArg, std::uint32_t> && IHandleSyscallWithIntegerArg<T>) ||
			(!std::convertible_to<TArg, std::uint32_t> && IHandleSyscallWithStructArg<T, TArg>));

	template <typename T>
	concept IHandleSyscallWithAnyArg =
		!IHandleSyscallWithNoArg<T> && (
			IHandleSyscallWithIntegerArg<T> || IHandleSyscallWithAnyStructArg<T>);

	template <typename T>
	concept IHandleSyscallWithAnyOrNoArg = IHandleSyscallWithAnyArg<T> || IHandleSyscallWithNoArg<T>;
}

#endif
