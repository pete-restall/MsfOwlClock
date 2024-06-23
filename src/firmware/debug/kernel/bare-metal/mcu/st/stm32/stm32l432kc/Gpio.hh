#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ST_STM32_STM32L432KC_GPIO_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ST_STM32_STM32L432KC_GPIO_HH
#include <type_traits>
#include "../../../../Register.hh"

namespace smeg::kernel::bare_metal::mcu::st::stm32::stm32l432kc
{
	struct Gpio
	{
		RegisterU32 MODER;
		RegisterU32 OTYPER;
		RegisterU32 OSPEEDR;
		RegisterU32 PUPDR;
		RegisterU32 IDR;
		RegisterU32 ODR;
		RegisterU32 BSRR;
		RegisterU32 LCKR;
		RegisterU32 AFRL;
		RegisterU32 AFRH;
		RegisterU32 BRR;
	};

	static_assert(sizeof(Gpio) == 0x2c, "Native GPIO register bank must be 44 bytes");
	static_assert(std::is_standard_layout_v<Gpio>, "Native GPIO register bank must be standard layout");

	extern "C"
	{
		extern volatile Gpio __linker_peripherals_ahb2_gpioA;
		extern volatile Gpio __linker_peripherals_ahb2_gpioB;
		extern volatile Gpio __linker_peripherals_ahb2_gpioC;
	}
}

#endif
