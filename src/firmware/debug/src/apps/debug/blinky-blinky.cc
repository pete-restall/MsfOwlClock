// TODO: Can be removed once we start to get tasks working properly
#include <cstdint>
#include <atomic>

#if false
#include "../../kernel/bare-metal/mcu/st/stm32/stm32l432kc/Gpio.hh"
#include "../../kernel/bare-metal/mcu/arm/cortex/m4/Rcc.hh"

using namespace smeg::kernel::bare_metal::mcu::arm::cortex;
using namespace smeg::kernel::bare_metal::mcu::st::stm32;

static volatile m4::Rcc &rcc(m4::__linker_peripherals_ahb1_rcc);
static volatile stm32l432kc::Gpio &gpioB(stm32l432kc::__linker_peripherals_ahb2_gpioB);

void blinkyBlinky(void)
{
	// LED = PB3 (pin 26)
	rcc.AHB2ENR = 2;
	gpioB.MODER = 0xfffffe7f;
	while (true)
	{
		gpioB.ODR ^= 1 << 3;
		for (auto i = 0; i < 200000; i++)
			__asm__ volatile ("nop");
	}
}

#else

#include "../../kernel/bare-metal/mcu/microchip/pic32/pic32cx1025sg41100/Port.hh"

using namespace smeg::kernel::bare_metal::mcu::microchip::pic32;

static volatile pic32cx1025sg41100::Port &portA(pic32cx1025sg41100::__linker_peripherals_ahbApb_apbb_portA);
static volatile pic32cx1025sg41100::Port &portB(pic32cx1025sg41100::__linker_peripherals_ahbApb_apbb_portB);
static volatile pic32cx1025sg41100::Port &portC(pic32cx1025sg41100::__linker_peripherals_ahbApb_apbb_portC);

void blinkyBlinky(void)
{
	// SDCARD_EN = PC15
	portC.DIR = 1 << 15;
	portC.OUT = 1 << 15;

	// /SDCARD_BUSYLED = PB25
	portB.DIR = 1 << 25;
	portB.OUT = 0;

	while (true)
	{
		for (auto n = 0; n < 20; n++)
		{
			portB.OUTTGL = 1 << 25;
			for (auto i = 0; i < 2400000; i++)
				__asm__ volatile ("nop");
		}
/*
		// MSF_RCV_EN = PA04
		// AMP_EN = PA06
		portA.DIR = (1 << 4) | (1 << 6);
		portA.OUTTGL = (1 << 4);
		for (auto i = 0; i < 240000; i++)
			__asm__ volatile ("nop");
		portA.OUTTGL = (1 << 6);

		// DS = PC05
		// STCP = PC06
		// SHCP = PC07
		portC.DIRSET = 0b111 << 5;
		portC.OUTCLR = 0b110 << 5;
		portC.OUTSET = 0b001 << 5;
		for (auto i = 0; i < 8; i++)
		{
			portC.OUTSET = 0b100 << 5;
			__asm__ volatile ("nop");
			__asm__ volatile ("nop");
			portC.OUTCLR = 0b100 << 5;
			__asm__ volatile ("nop");
			__asm__ volatile ("nop");
		}

		portC.OUTSET = 0b010 << 5;
		__asm__ volatile ("nop");
		__asm__ volatile ("nop");
		portC.OUTCLR = 0b010 << 5;

		while (true)
			;;
*/
	}
}

#endif
