#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_DEBUG_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_DEBUG_HH
#include <type_traits>
#include "../../../../Register.hh"

namespace smeg::kernel::bare_metal::mcu::arm::cortex::m4
{
	struct Debug
	{
		RegisterU32 DHCSR;
		RegisterU32 DCRSR;
		RegisterU32 DCRDR;
		RegisterU32 DEMCR;
		RegisterU32 _reserved_10[64];
	};

	static_assert(sizeof(Debug) == 0x110, "Native DEBUG register bank must be 272 bytes");
	static_assert(std::is_standard_layout_v<Debug>, "Native DEBUG register bank must be standard layout");
}

#endif
