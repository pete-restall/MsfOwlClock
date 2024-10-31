#ifndef __SMEG_KERNEL_ISTATICVOIDRUNNABLE_HH
#define __SMEG_KERNEL_ISTATICVOIDRUNNABLE_HH
#include <concepts>
#include <type_traits>

namespace smeg::kernel
{
	template <typename T>
	concept IStaticVoidRunnable = !std::is_member_object_pointer_v<decltype(&T::run)> && requires
	{
		{ T::run() } -> std::same_as<void>;
	};

	template <typename T>
	concept IStaticVoidNoExceptRunnable = IStaticVoidRunnable<T> && noexcept(T::run());
}

#endif
