#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SYSCALLDRIVERCONFIG_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SYSCALLDRIVERCONFIG_HH
#include <tuple>

#include "kernel/tasks/DriverToKernelApis.hh"

#include "../../../../SyscallFor.hh"
#include "DefaultSyscallApi.hh"
#include "SvcallIsr.hh"
#include "SyscallPrimitive.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4
{
	using namespace smeg::kernel::tasks;

	template <typename TKernelConfigs, template <typename, typename> typename TSyscallFor = SyscallFor>
	class DefaultSyscallDriverConfig
	{
	private:
		class DriverToKernelApiConfig
		{
		private:
			template <typename TSyscall>
			using SyscallFor = TSyscallFor<TKernelConfigs, TSyscall>;

		public:
			template <typename TApi>
			using Interface = DriverToKernelApis<TApi>;

			using Type = DefaultSyscallApi<SyscallPrimitive<SyscallFor>, SyscallFor>;
		};

	public:
		struct SvcallIsrConfig
		{
			using Handler = SvcallIsr<TKernelConfigs>;
			static constexpr auto irq = 11;
		};

		using ProvidedApis = std::tuple<DriverToKernelApiConfig>;
		using ProvidedIsrs = std::tuple<SvcallIsrConfig>;
	};
}

#endif
