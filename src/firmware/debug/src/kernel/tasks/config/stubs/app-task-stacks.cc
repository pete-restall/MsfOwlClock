#include <cstddef>
#include <tuple>

#include "../../../../app-config.hh"
#include "../../../tuples/TupleProjection.hh"
#include "../dsl/DefaultMemorySection.hh"
#include "../IHaveAssociatedConfigForTaskStack.hh"
#include "../TaskStackConfigsFrom.hh"
#include "../TaskStackConfigToRamBlock.hh"
#include "../TaskStackNumberOfSlotsFor.hh"
#include "../TaskStackRamBlock.hh"

DEFINE_TASK_STACK_LINKER_SECTION_FOR_APP(dsl::DefaultMemorySection, ".app.tasks.stacks.default")

namespace smeg::kernel::tasks::config::stubs
{
	void __preventCompilerOptimisingAppTaskStacksAway(void);

	namespace
	{
		using AppConfig = ::smeg::config::AppConfig;

		template <IHaveAssociatedConfigForTaskStack TTaskStackConfig, std::size_t StackIndex>
		using AppTaskStackConfigToRamBlock = TaskStackConfigToRamBlock<AppConfig, TTaskStackConfig, StackIndex, TaskStackNumberOfSlotsFor>;

		TupleProjection<typename TaskStackConfigsFrom<AppConfig>::PerStack, AppTaskStackConfigToRamBlock>::Output appTaskStacks;

		template <typename... T>
		[[gnu::section(".discard")]]
		auto __preventCompilerOptimisingAppTaskStacksAway(std::tuple<T...>)
		{
			volatile auto unused = (T::ramBlock[0] + ...);
			return unused;
		};
	}

	[[gnu::section(".discard")]]
	void __preventCompilerOptimisingAppTaskStacksAway(void)
	{
		(void) __preventCompilerOptimisingAppTaskStacksAway(appTaskStacks);
	}
}
