#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_RESERVEDISR_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_RESERVEDISR_HH

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	class ReservedIsr
	{
	public:
		static void onInterrupt(void) noexcept;
	};
}

#endif
