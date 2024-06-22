#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ST_STM32_STM32L432KC_GPIO_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ST_STM32_STM32L432KC_GPIO_HH
#include <atomic>
#include <cstdint>
#include <type_traits>

namespace smeg::kernel::bare_metal::mcu::st::stm32::stm32l432kc
{
	struct Gpio
	{
		std::atomic<std::uint32_t> MODER;
		std::atomic<std::uint32_t> OTYPER;
		std::atomic<std::uint32_t> OSPEEDR;
		std::atomic<std::uint32_t> PUPDR;
		std::atomic<std::uint32_t> IDR;
		std::atomic<std::uint32_t> ODR;
		std::atomic<std::uint32_t> BSRR;
		std::atomic<std::uint32_t> LCKR;
		std::atomic<std::uint32_t> AFRL;
		std::atomic<std::uint32_t> AFRH;
		std::atomic<std::uint32_t> BRR;
	};

	static_assert(sizeof(Gpio) == 0x2c, "Native GPIO register bank must be 44 bytes");
	static_assert(std::is_aggregate_v<Gpio>, "Native GPIO register bank must be able to be memcpy()'d (POD)");

	extern "C"
	{
		extern Gpio __linker_peripherals_ahb2_gpioA;
		extern Gpio __linker_peripherals_ahb2_gpioB;
		extern Gpio __linker_peripherals_ahb2_gpioC;
	}
}

#endif
