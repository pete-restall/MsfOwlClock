#ifndef __SMEG_TESTS_UNIT_KERNEL_DRIVERS_DUMMYTASKCONFIG_HH
#define __SMEG_TESTS_UNIT_KERNEL_DRIVERS_DUMMYTASKCONFIG_HH

namespace smeg::tests::unit::kernel::drivers::config
{
	template <auto X>
	struct DummyDriverConfig
	{
		struct DriverToDriverApi
		{
			struct Type
			{
			};
		};
	};
}

#endif
