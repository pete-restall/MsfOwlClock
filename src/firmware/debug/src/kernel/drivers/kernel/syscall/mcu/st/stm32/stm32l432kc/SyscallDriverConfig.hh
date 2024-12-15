#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ST_STM32_STM32L432KC_SYSCALLDRIVERCONFIG_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ST_STM32_STM32L432KC_SYSCALLDRIVERCONFIG_HH
#include <cstddef>

#include "../../../arm/cortex/m4/DefaultSyscallDriverConfig.hh"
#include "../../../../SyscallFor.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::st::stm32::stm32l432kc
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
