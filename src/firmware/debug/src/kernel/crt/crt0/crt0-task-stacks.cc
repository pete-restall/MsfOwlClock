#include <tuple>

#include "../../tuples/TupleProjection.hh"
#include "../../tasks/config/dsl/DefaultMemorySection.hh"
#include "../../tasks/config/IHaveAssociatedConfigForTaskStack.hh"
#include "../../tasks/config/TaskStackConfigsFrom.hh"
#include "../../tasks/config/TaskStackConfigToRamBlock.hh"
#include "../../tasks/config/TaskStackNumberOfSlotsFor.hh"
#include "../../tasks/config/TaskStackRamBlock.hh"

using namespace smeg::kernel::crt::crt0;
using namespace smeg::kernel::tasks::config;

DEFINE_TASK_STACK_LINKER_SECTION_FOR(Crt0Config, IsrStackMemorySection, ".kernel.tasks.stacks.isrs")

namespace smeg::kernel::crt::crt0
{
	void __preventCompilerOptimisingCrt0TaskStacksAway(void);

	namespace
	{
		template <IHaveAssociatedConfigForTaskStack TTaskStackConfig, std::size_t StackIndex>
		using Crt0TaskStackConfigToRamBlock = TaskStackConfigToRamBlock<Crt0Config, TTaskStackConfig, StackIndex, TaskStackNumberOfSlotsFor>;

		TupleProjection<typename TaskStackConfigsFrom<Crt0Config>::PerStack, Crt0TaskStackConfigToRamBlock>::Output crt0TaskStacks;

		template <typename... T>
		[[gnu::section(".discard")]]
		auto __preventCompilerOptimisingCrt0TaskStacksAway(std::tuple<T...>)
		{
			volatile auto unused = (T::ramBlock[0] + ...);
			return unused;
		};
	}

	[[gnu::section(".discard")]]
	void __preventCompilerOptimisingCrt0TaskStacksAway(void)
	{
		(void) __preventCompilerOptimisingCrt0TaskStacksAway(crt0TaskStacks);
	}
}
