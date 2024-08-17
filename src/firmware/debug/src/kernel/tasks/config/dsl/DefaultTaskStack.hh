#ifndef __SMEG_KERNEL_TASKS_CONFIG_DSL_DEFAULTTASKSTACK_HH
#define __SMEG_KERNEL_TASKS_CONFIG_DSL_DEFAULTTASKSTACK_HH
#include <cstdint>

namespace smeg::kernel::tasks::config::dsl
{
	template <std::size_t NumberOfWords>
	struct DefaultTaskStack
	{
		// TODO
		// These classes are basically markers that allow us to define multiple stack types.  This allows the config
		// parser to look for specific types of stack and construct them all contiguously in the same linker section
		// (for example, RetainedTaskStack for stacks in memory retained during hibernation, BackupRamTaskStack, etc.)
		//
		// The MCU-specific memory sections (ie. Retained32k, BackupRam, etc.) need to be exposed to the config headers
		// so that the user can utilise them.
		//
		// The NumberOfWords will need to be adjusted during instantiation of the actual stack.  The adjustment will be
		// MCU-specific as it needs to accommodate the context-saving information.  How to get that MCU-specific constant
		// into the TaskStack instantiation ?
		//
		// The stacks placed into MCU-specific memory sections will need to be constructed by an MCU-specific module, so
		// something like: RetainedTaskStacksFrom<Config> will return an std::tuple<ResourceToTaskAssociation> that can
		// be iterated and turned into an std::tuple<std::array<std::uint32_t, NumberOfWords + NumberOfContextSavingWords>>
		// which is part of a named linker section.
		//
		// The stacks will also require a 'stack control block', which, as a minimum, points to the raw array; stacks for
		// overlaid tasks may require a mutex and / or task index or some other supplementary information.  It might be
		// tempting to use a single 'Stack' class and a richly encapsulated model but it is important to separate the kernel
		// structures (ie. the mutex / owner for stacks used by overlaid tasks) from the raw storage as that can be corrupted
		// by userspace applications.
	};
}

#endif
