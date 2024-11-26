#ifndef __SMEG_TESTS_UNIT_KERNEL_DRIVERS_DUMMYDRIVERCONFIG_HH
#define __SMEG_TESTS_UNIT_KERNEL_DRIVERS_DUMMYDRIVERCONFIG_HH
#include <tuple>

namespace smeg::tests::unit::kernel::drivers::config
{
	template <auto X>
	struct DummyDriverConfig
	{
		struct UselessApiConfig
		{
			template <typename TApi>
			struct Interface
			{
			};

			struct Type
			{
			};
		};

		struct UselessIsrConfig
		{
			struct Handler
			{
				static void onInterrupt(void) noexcept
				{
				}
			};

			static constexpr auto irq = 23;
		};

		struct UselessSyscallConfig
		{
			struct UselessSyscallContext
			{
			};

			struct UselessSyscall
			{
			};

			struct Handler
			{
				void onSyscall(UselessSyscallContext &, UselessSyscall &)
				{
				}
			};
		};

		struct UselessTaskConfig
		{
			struct Type
			{
				void run(void)
				{
				}
			};

			struct Stack
			{
				static constexpr auto numberOfSlots = 16;
			};
		};

		using ProvidedApis = std::tuple<UselessApiConfig>;
		using ProvidedIsrs = std::tuple<UselessIsrConfig>;
		using ProvidedSyscalls = std::tuple<UselessSyscallConfig>;
		using Tasks = std::tuple<UselessTaskConfig>;
	};
}

#endif
