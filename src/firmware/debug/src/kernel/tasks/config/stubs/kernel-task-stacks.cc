#include <tuple>

#include "../../../../kernel-config.hh"
#include "../../../IHaveValue.hh"
#include "../../../tuples/TupleProjection.hh"
#include "../dsl/DefaultMemorySection.hh"
#include "../IHaveAssociatedConfigForTaskStack.hh"
#include "../TaskStackConfigsFrom.hh"
#include "../TaskStackConfigToRamBlock.hh"
#include "../TaskStackNumberOfSlotsFor.hh"
#include "../TaskStackRamBlock.hh"

DEFINE_TASK_STACK_LINKER_SECTION_FOR_KERNEL(dsl::DefaultMemorySection, ".kernel.tasks.stacks.default")

namespace smeg::kernel::tasks::config::stubs
{
	void __preventCompilerOptimisingKernelTaskStacksAway(void);

	namespace
	{
		using KernelConfig = ::smeg::config::KernelConfig;

		template <IHaveAssociatedConfigForTaskStack TTaskStackConfig, std::size_t StackIndex>
		using KernelTaskStackConfigToRamBlock = TaskStackConfigToRamBlock<KernelConfig, TTaskStackConfig, StackIndex, TaskStackNumberOfSlotsFor>;

		// TODO: This projection can be refactored into a TaskStacksFrom for easier use by, for example, the code that will eventually build the Task Control Blocks
		TupleProjection<typename TaskStackConfigsFrom<KernelConfig>::PerStack, KernelTaskStackConfigToRamBlock>::Output kernelTaskStacks;

		template <typename... T>
		[[gnu::section(".discard")]]
		auto __preventCompilerOptimisingKernelTaskStacksAway(std::tuple<T...>)
		{
			volatile auto unused = (T::ramBlock[0] + ...);
			return unused;
		};
	}

	[[gnu::section(".discard")]]
	void __preventCompilerOptimisingKernelTaskStacksAway(void)
	{
		(void) __preventCompilerOptimisingKernelTaskStacksAway(kernelTaskStacks);
	}
}
