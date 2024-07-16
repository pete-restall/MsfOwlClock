#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_CACHE_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_CACHE_HH
#include <type_traits>
#include "../../../../Register.hh"

namespace smeg::kernel::bare_metal::mcu::arm::cortex::m4
{
	struct Cache
	{
		RegisterU32 ICIALLU;
		RegisterU32 _reserved_04;
		RegisterU32 ICIMVAU;
		RegisterU32 DCIMVAC;
		RegisterU32 DCISW;
		RegisterU32 DCCMVAU;
		RegisterU32 DCCMVAC;
		RegisterU32 DCCSW;
		RegisterU32 DCCIMVAC;
		RegisterU32 DCCISW;
		RegisterU32 BPIALL;
		RegisterU32 _reserved_2c;
		RegisterU32 _reserved_30;
	};

	static_assert(sizeof(Cache) == 0x34, "Native CACHE register bank must be 52 bytes");
	static_assert(std::is_standard_layout_v<Cache>, "Native DEBUG register bank must be standard layout");
}

#endif
