#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_DUMMYTASK_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_DUMMYTASK_HH

namespace smeg::tests::unit::kernel::tasks::config
{
	template <auto X>
	struct DummyTask
	{
		void run(void)
		{
		}
	};
}

#endif
