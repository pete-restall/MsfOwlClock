#ifndef __SMEG_KERNEL_CRT0_MCU_ARM_CORTEX_M4_ISRS_HH
#define __SMEG_KERNEL_CRT0_MCU_ARM_CORTEX_M4_ISRS_HH

#define __ARM_CORTEX_M4_ISRS_CLASS "_ZN4smeg6kernel4crt03mcu3arm6cortex2m44Isrs"
#define __ARM_CORTEX_M4_DEFAULT_ISR_NAME __ARM_CORTEX_M4_ISRS_CLASS "10defaultIsrEv"
#define __ARM_CORTEX_M4_RESERVED_ISR_NAME __ARM_CORTEX_M4_ISRS_CLASS "11reservedIsrEv"

namespace smeg::kernel::crt0::mcu::arm::cortex::m4
{
	class Isrs
	{
private:
		static void defaultIsr(void) noexcept;
		static void reservedIsr(void) noexcept;

public:
		static void nmi(void) noexcept;
		static void hardFault(void) noexcept;
		static void memManage(void) noexcept;
		static void busFault(void) noexcept;
		static void usageFault(void) noexcept;
		static void reserved7(void) noexcept;
		static void reserved8(void) noexcept;
		static void reserved9(void) noexcept;
		static void reserved10(void) noexcept;
		static void svCall(void) noexcept;
		static void debugMonitor(void) noexcept;
		static void reserved13(void) noexcept;
		static void pendsv(void) noexcept;
		static void sysTick(void) noexcept;
	};
}

#endif
