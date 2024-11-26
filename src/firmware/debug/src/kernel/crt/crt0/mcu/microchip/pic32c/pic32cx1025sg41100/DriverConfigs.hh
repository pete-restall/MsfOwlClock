#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_DRIVERCONFIGS_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_MICROCHIP_PIC32C_PIC32CX1025SG41100_DRIVERCONFIGS_HH
#include <tuple>

#include "../../../../../../drivers/kernel/syscall/mcu/microchip/pic32c/pic32cx1025sg41100/SyscallDriverConfig.hh"

namespace smeg::kernel::crt::crt0::mcu::microchip::pic32c::pic32cx1025sg41100
{
	namespace drivers = smeg::kernel::drivers::kernel;

	template <typename TKernelConfigs>
	using DriverConfigs = std::tuple<
		drivers::syscall::mcu::microchip::pic32c::pic32cx1025sg41100::SyscallDriverConfig<TKernelConfigs>>;
}

#endif
