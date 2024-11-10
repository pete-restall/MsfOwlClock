#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_SCS_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_SCS_HH
#include <type_traits>
#include "../../../../Register.hh"
#include "Cache.hh"
#include "Debug.hh"
#include "Scb.hh"
#include "ScbFp.hh"

namespace smeg::kernel::bare_metal::mcu::arm::cortex::m4
{
	struct Scs // TODO: SEE PAGE B3-595 OF ARMV7 REFERENCE MANUAL - THERE'S MORE IN THIS BANK !
	{
		RegisterU32 _reserved_0;
		RegisterU32 ICTR;
		RegisterU32 ACTLR;
		RegisterU32 _reserved_00c[829];
		Scb SCB;
		RegisterU32 _reserved_d90[24];
		Debug DEBUG;
		RegisterU32 STIR;
		RegisterU32 _reserved_f04[12];
		ScbFp SCB_FP;
		RegisterU32 _reserved_f4c;
		Cache CACHE;
		RegisterU32 _reserved_f84[3];
		RegisterU32 _reserved_f90[16];
		RegisterU32 PID4;
		RegisterU32 PID5;
		RegisterU32 PID6;
		RegisterU32 PID7;
		RegisterU32 PID0;
		RegisterU32 PID1;
		RegisterU32 PID2;
		RegisterU32 PID3;
		RegisterU32 CID0;
		RegisterU32 CID1;
		RegisterU32 CID2;
		RegisterU32 CID3;
	};

	static_assert(sizeof(Scs) == 0x1000, "Native SCS register bank must be 4096 bytes");
	static_assert(std::is_standard_layout_v<Scs>, "Native SCS register bank must be standard layout");

	extern "C"
	{
		extern volatile Scs __linker_system_scs;
	}
}

#endif
