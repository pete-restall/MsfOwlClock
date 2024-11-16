#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_CONFIG_DUMMYTASKSTACKCONFIG_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_CONFIG_DUMMYTASKSTACKCONFIG_HH

namespace smeg::tests::unit::kernel::tasks::config
{
	template <auto N>
	struct DummyTaskStackConfig
	{
		static constexpr auto numberOfSlots = 0;
	};
}

#endif
