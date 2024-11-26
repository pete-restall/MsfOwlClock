#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_UNHANDLEDISR_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_UNHANDLEDISR_HH

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	class UnhandledIsr
	{
	public:
		static void onInterrupt(void) noexcept;
	};
}

#endif
