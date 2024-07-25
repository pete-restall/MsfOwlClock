#include <cstdint>
#include <atomic>

#if false
#include "../kernel/bare-metal/mcu/st/stm32/stm32l432kc/Gpio.hh"
#include "../kernel/bare-metal/mcu/arm/cortex/m4/Rcc.hh"

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

void blinkyBlinky(void)
{
	while (true)
		;;
}

#endif
