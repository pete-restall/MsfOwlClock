#ifndef __SMEG_KERNEL_CRT0_MCU_ARM_CORTEX_M4_ISRVECTORTABLE_HH
#define __SMEG_KERNEL_CRT0_MCU_ARM_CORTEX_M4_ISRVECTORTABLE_HH

namespace smeg::kernel::crt0::mcu::arm::cortex::m4
{
	typedef void (*const IsrVector)(void) noexcept;
}

#endif
