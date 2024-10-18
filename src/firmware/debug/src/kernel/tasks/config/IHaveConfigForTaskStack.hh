#ifndef __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASKSTACK_HH
#define __SMEG_KERNEL_TASKS_CONFIG_IHAVECONFIGFORTASKSTACK_HH
#include <concepts>
#include <cstdint>
#include <type_traits>

namespace smeg::kernel::tasks::config
{
	template <typename T>
	concept _IHaveConfigForTaskStackRequiredProperties = std::convertible_to<decltype(T::numberOfSlots), std::size_t> && T::numberOfSlots >= 0;

	template <typename T>
	concept IHaveConfigForTaskStackWithMemorySection = _IHaveConfigForTaskStackRequiredProperties<T> && std::is_class_v<typename T::MemorySection>;

	template <typename T>
	concept IHaveConfigForTaskStackWithoutMemorySection = _IHaveConfigForTaskStackRequiredProperties<T> && !IHaveConfigForTaskStackWithMemorySection<T>;

	template <typename T>
	concept IHaveConfigForTaskStack = IHaveConfigForTaskStackWithMemorySection<T> || IHaveConfigForTaskStackWithoutMemorySection<T>;
}

#endif
