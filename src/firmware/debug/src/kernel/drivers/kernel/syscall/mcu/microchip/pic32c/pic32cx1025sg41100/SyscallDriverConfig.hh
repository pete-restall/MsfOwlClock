#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_SYSCALLDRIVERCONFIG_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_SYSCALLDRIVERCONFIG_HH
#include  <cstddef>

#include "../../../arm/cortex/m4/DefaultSyscallDriverConfig.hh"
#include "../../../../SyscallFor.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::microchip::pic32c::pic32cx1025sg41100
{
	using namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4;

	template <
		typename TKernelConfigs,
		template <typename, std::size_t, typename...> typename TPerCoreApiFactory,
		template <typename, std::size_t, template <typename, std::size_t, typename...> typename> typename TSyscallHandlerFactory>
	struct _$SyscallDriverConfig
	{
		template <typename TConfig, std::size_t McuCoreId>
		using SyscallHandlerFactory = TSyscallHandlerFactory<TConfig, McuCoreId, TPerCoreApiFactory>;

		using Type = DefaultSyscallDriverConfig<
			TKernelConfigs,
			TPerCoreApiFactory,
			SyscallHandlerFactory,
			SyscallFor>;
	};

	template <
		typename TKernelConfigs,
		template <typename, std::size_t, typename...> typename TPerCoreApiFactory,
		template <typename, std::size_t, template <typename, std::size_t, typename...> typename> typename TSyscallHandlerFactory>
	using SyscallDriverConfig = _$SyscallDriverConfig<TKernelConfigs, TPerCoreApiFactory, TSyscallHandlerFactory>::Type;
}

#endif
