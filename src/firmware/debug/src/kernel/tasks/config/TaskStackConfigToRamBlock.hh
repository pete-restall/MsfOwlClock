#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKCONFIGTORAMBLOCK_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKCONFIGTORAMBLOCK_HH
#include <cstdint>
#include <tuple>
#include "dsl/DefaultMemorySection.hh"
#include "IHaveAssociatedConfigForTaskStack.hh"
#include "IHaveConfigForTasks.hh"
#include "TaskStackRamBlock.hh"

namespace smeg::kernel::tasks::config
{
	template <
		IHaveConfigForTasks TConfig,
		IHaveAssociatedConfigForTaskStack TTaskStackConfig,
		std::size_t StackIndex,
		template <IHaveConfigForTasks, IHaveAssociatedConfigForTaskStack> typename TTaskStackNumberOfSlotsFor>
	struct TaskStackConfigToRamBlock;

	template <
		IHaveConfigForTasks TConfig,
		IHaveAssociatedConfigForTaskStackWithMemorySection TTaskStackConfig,
		std::size_t StackIndex,
		template <IHaveConfigForTasks, IHaveAssociatedConfigForTaskStack> typename TTaskStackNumberOfSlotsFor>
	struct TaskStackConfigToRamBlock<TConfig, TTaskStackConfig, StackIndex, TTaskStackNumberOfSlotsFor>
	{
		using AsTuple = std::tuple<TaskStackRamBlock<
			TConfig,
			StackIndex,
			typename TTaskStackConfig::Resource::MemorySection,
			TTaskStackNumberOfSlotsFor<TConfig, TTaskStackConfig>::value>>;
	};

	template <
		IHaveConfigForTasks TConfig,
		IHaveAssociatedConfigForTaskStackWithoutMemorySection TTaskStackConfig,
		std::size_t StackIndex,
		template <IHaveConfigForTasks, IHaveAssociatedConfigForTaskStack> typename TTaskStackNumberOfSlotsFor>
	struct TaskStackConfigToRamBlock<TConfig, TTaskStackConfig, StackIndex, TTaskStackNumberOfSlotsFor>
	{
		using AsTuple = std::tuple<TaskStackRamBlock<
			TConfig,
			StackIndex,
			dsl::DefaultMemorySection,
			TTaskStackNumberOfSlotsFor<TConfig, TTaskStackConfig>::value>>;
	};
}

#endif
