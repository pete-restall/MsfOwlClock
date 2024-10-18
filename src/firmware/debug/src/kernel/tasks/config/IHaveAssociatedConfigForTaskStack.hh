#ifndef __SMEG_KERNEL_TASKS_CONFIG_IHAVEASSOCIATEDCONFIGFORTASKSTACK_HH
#define __SMEG_KERNEL_TASKS_CONFIG_IHAVEASSOCIATEDCONFIGFORTASKSTACK_HH
#include "IHaveConfigForTaskStack.hh"

namespace smeg::kernel::tasks::config
{
	template <typename T>
	concept IHaveAssociatedConfigForTaskStackWithMemorySection = IHaveConfigForTaskStackWithMemorySection<typename T::Resource>;

	template <typename T>
	concept IHaveAssociatedConfigForTaskStackWithoutMemorySection = IHaveConfigForTaskStackWithoutMemorySection<typename T::Resource>;

	template <typename T>
	concept IHaveAssociatedConfigForTaskStack = IHaveAssociatedConfigForTaskStackWithMemorySection<T> || IHaveAssociatedConfigForTaskStackWithoutMemorySection<T>;
}

#endif
