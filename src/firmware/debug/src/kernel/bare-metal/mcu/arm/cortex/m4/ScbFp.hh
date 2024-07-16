#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_SCBFP_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_SCBFP_HH
#include <type_traits>
#include "../../../../Register.hh"

namespace smeg::kernel::bare_metal::mcu::arm::cortex::m4
{
	struct ScbFp
	{
		RegisterU32 FPCCR;
		RegisterU32 FPCAR;
		RegisterU32 FPDSCR;
		RegisterU32 MVFR0;
		RegisterU32 MVFR1;
		RegisterU32 MVFR2;
	};

	static_assert(sizeof(ScbFp) == 0x18, "Native SCB FP register bank must be 24 bytes");
	static_assert(std::is_standard_layout_v<ScbFp>, "Native SCB FP register bank must be standard layout");
}

#endif
