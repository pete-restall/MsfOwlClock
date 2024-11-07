#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKNUMBEROFSLOTSFOR_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKNUMBEROFSLOTSFOR_HH
#include "IHaveAssociatedConfigForTaskStack.hh"
#include "IHaveConfigForTasks.hh"
#include "TaskConfigsFrom.hh"

namespace smeg::kernel::tasks::config
{
// TODO: THIS ALL NEEDS TO BE THOUGHT ABOUT, AS WELL AS TESTED IN ISOLTION...

	template <IHaveConfigForTasks TConfig, IHaveAssociatedConfigForTaskStack TTaskStackConfig>
	class TaskStackNumberOfSlotsFor
	{
	private:
//		using TaskConfigs = TupleElementsOf<TaskConfigsFrom<TConfig>::PerTask>::At<TTaskStackConfig::TaskIds>;
//		using TaskContextSwitchingConfigs = TaskContextSwitchingConfigsFrom<TConfig>::PerTask;
//
//		static constexpr auto numberOfContextSwitchingSlots = Max<TupleReduction<TaskContextSwitchingConfigs, TaskContextSwitchingConfigToNumberOfSlots>>::value;
		static constexpr auto numberOfContextSwitchingSlots = 32; // TODO: Effectively a random number, just to get the compilation to pass until the context-switching config functionality is created

// Some considerations for ARM - not necessarily other processors.
// 1. Ensure that the number of bytes is a multiple of 8 to ensure alignment (the linker script aligns the lowest memory address, but the stack starts from the highest)
// 2. ARM 'push' is essentially '*(--sp) = val', which means we're losing one word if we set [MP]SP to the highest memory address; we need to use 'highest memory address + 1'

	public:
		static constexpr auto value = numberOfContextSwitchingSlots + TTaskStackConfig::Resource::numberOfSlots;
	};
}

#endif
