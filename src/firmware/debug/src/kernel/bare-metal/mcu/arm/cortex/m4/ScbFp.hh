#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_SCBFP_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ARM_CORTEX_M4_SCBFP_HH
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "../../../../Register.hh"
#include "../../../../BitfieldTraits.hh"

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

	// TODO: Something like this for holding bitfields ?  Doesn't seem adequate though.  Maybe a bit onerous.
	// Might be better to have a single 'union REGNAME { RegisterU32 raw; struct { ... } traits; }' ?  Would that have consistent layout though ?
	struct FpccrRegisterBitfields
	{
		template <std::size_t LeftIndex, std::size_t NumBits>
		using Bits = BitfieldTraits<std::uint32_t, LeftIndex, NumBits>;

		template <std::size_t Index>
		using Bit = Bits<Index, 1>;

		using ASPEN = Bit<31>;
		using LSPEN = Bit<30>;
		using MONRDY = Bit<8>;
		using BFRDY = Bit<6>;
		using MMRDY = Bit<5>;
		using HFRDY = Bit<4>;
		using THREAD = Bit<3>;
		using USER = Bit<1>;
		using LSPACT = Bit<0>;
	};
}

#endif
