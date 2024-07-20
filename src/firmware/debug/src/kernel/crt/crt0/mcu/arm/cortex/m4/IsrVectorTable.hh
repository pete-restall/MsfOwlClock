#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_ISRVECTORTABLE_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_ISRVECTORTABLE_HH

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	using IsrVector = void (*const)(void) noexcept;
}

#endif
