#ifndef __SMEG_KERNEL_BAREMETAL_MCU_MICROCHIP_PIC32_PIC32CX1025SG41100_PORT_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_MICROCHIP_PIC32_PIC32CX1025SG41100_PORT_HH
#include <type_traits>
#include "../../../../Register.hh"

namespace smeg::kernel::bare_metal::mcu::microchip::pic32::pic32cx1025sg41100
{
	struct Port
	{
		RegisterU32 DIR;
		RegisterU32 DIRCLR;
		RegisterU32 DIRSET;
		RegisterU32 DIRTGL;
		RegisterU32 OUT;
		RegisterU32 OUTCLR;
		RegisterU32 OUTSET;
		RegisterU32 OUTTGL;
		RegisterU32 IN;
		RegisterU32 CTRL;
		RegisterU32 WRCONFIG;
		RegisterU32 EVCTRL;
		RegisterU8 PMUX[16];
		RegisterU8 PINCFG[32];
	};

	static_assert(sizeof(Port) == 0x60, "Native PORT register bank must be 96 bytes");
	static_assert(std::is_standard_layout_v<Port>, "Native PORT register bank must be standard layout");

	extern "C"
	{
		extern volatile Port __linker_peripherals_ahbApb_apbb_portA;
		extern volatile Port __linker_peripherals_ahbApb_apbb_portB;
		extern volatile Port __linker_peripherals_ahbApb_apbb_portC;
	}
}

#endif
