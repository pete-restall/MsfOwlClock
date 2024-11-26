#ifndef __SMEG_TESTS_UNIT_KERNEL_DRIVERS_DUMMYPROVIDEDISRCONFIG_HH
#define __SMEG_TESTS_UNIT_KERNEL_DRIVERS_DUMMYPROVIDEDISRCONFIG_HH

namespace smeg::tests::unit::kernel::drivers::config
{
	template <auto X>
	struct DummyProvidedIsrConfig
	{
		struct Handler
		{
			static void onInterrupt(void) noexcept
			{
			}
		};

		static constexpr auto irq = 23;
	};
}

#endif
