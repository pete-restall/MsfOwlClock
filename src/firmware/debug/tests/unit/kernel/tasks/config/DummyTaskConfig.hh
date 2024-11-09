#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_CONFIG_DUMMYTASKCONFIG_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_CONFIG_DUMMYTASKCONFIG_HH
#include "DummyTask.hh"
#include "DummyTaskStack.hh"

namespace smeg::tests::unit::kernel::tasks::config
{
	template <auto X>
	struct DummyTaskConfig
	{
		using Type = DummyTask<X>;
		using Stack = DummyTaskStack<X + 42>;
	};
}

#endif
