#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SYSCALLDRIVERCONFIG_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SYSCALLDRIVERCONFIG_HH
#include <tuple>

#include "kernel/config/McuCoreTraitsFrom.hh"
#include "kernel/tasks/AppTaskApis.hh"

#include "../../../../PortableSyscallPerCoreIsrFactory.hh"
#include "../../../../SyscallFor.hh"
#include "DefaultSyscallTaskApi.hh"
#include "SvcallIsr.hh"
#include "SyscallPrimitive.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4
{
	using namespace smeg::kernel::config;
	using namespace smeg::kernel::tasks;

	template <
		typename TKernelConfigs,
		template <typename, std::size_t, typename...> typename TPerCoreApiFactory,
		template <typename, std::size_t, typename...> typename TSyscallHandlerFactory,
		template <typename, typename> typename TSyscallFor = SyscallFor>
	class DefaultSyscallDriverConfig
	{
	private:
		template <typename TSyscall>
		using SyscallFor = TSyscallFor<TKernelConfigs, TSyscall>;

		struct AppTaskApiConfig
		{
			template <typename TApi>
			using Interface = AppTaskApis<TApi>;

			using Type = DefaultSyscallTaskApi<SyscallPrimitive<SyscallFor>, SyscallFor>;
		};

		struct SvcallIsrConfig;

		template <auto McuCoreId>
		using PortableSyscallPerCoreIsrFactoryWithDependencies = PortableSyscallPerCoreIsrFactory<
			SvcallIsrConfig,
			McuCoreId,
			TPerCoreApiFactory,
			TSyscallHandlerFactory,
			std::tuple<>>; // TODO: RequiredSyscallHandlersFrom<TKernelConfigs> or something like that...

		struct SvcallIsrConfig
		{
			using Handler = SvcallIsr<
				McuCoreTraitsFrom<TKernelConfigs>,
				PortableSyscallPerCoreIsrFactoryWithDependencies>;

			static constexpr auto irq = 11;
		};

	public:
		using ProvidedApis = std::tuple<AppTaskApiConfig>;
		using ProvidedIsrs = std::tuple<SvcallIsrConfig>;
	};
}

#endif
