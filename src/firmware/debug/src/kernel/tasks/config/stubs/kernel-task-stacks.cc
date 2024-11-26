#include <tuple>

#include "../../../../kernel-config.hh"
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
		using KernelConfig = ::smeg::config::KernelConfig; // TODO: See comments in crt0-task-stacks; the whole concept of needing files for each layer of Tasks should really vanish if that can be accomplished

		template <IHaveAssociatedConfigForTaskStack TTaskStackConfig, std::size_t StackIndex>
		using KernelTaskStackConfigToRamBlock = TaskStackConfigToRamBlock<KernelConfig, TTaskStackConfig, StackIndex, TaskStackNumberOfSlotsFor>;

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
