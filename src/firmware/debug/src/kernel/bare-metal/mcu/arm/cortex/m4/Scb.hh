#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_SCB_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_SCB_HH
#include <type_traits>
#include "../../../../Register.hh"

namespace smeg::kernel::bare_metal::mcu::arm::cortex::m4
{
	struct Scb
	{
		RegisterU32 CPUID;
		RegisterU32 ICSR;
		RegisterU32 VTOR;
		RegisterU32 AIRCR;
		RegisterU32 SCR;
		RegisterU32 CCR;
		RegisterU32 SHPR1;
		RegisterU32 SHPR2;
		RegisterU32 SHPR3;
		RegisterU32 SHCSR;
		RegisterU32 CFSR;
		RegisterU32 HFSR;
		RegisterU32 DFSR;
		RegisterU32 MMFAR;
		RegisterU32 BFAR;
		RegisterU32 AFSR;
		RegisterU32 _reserved_40[18];
		RegisterU32 CPACR;
		RegisterU32 _reserved_8c;
	};

	static_assert(sizeof(Scb) == 0x90, "Native SCB register bank must be 144 bytes");
	static_assert(std::is_standard_layout_v<Scb>, "Native SCB register bank must be standard layout");
}

#endif
