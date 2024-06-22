#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ST_STM32_STM32L432KC_RCC_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ST_STM32_STM32L432KC_RCC_HH
#include <atomic>
#include <cstdint>

namespace smeg::kernel::bare_metal::mcu::st::stm32::stm32l432kc
{
	struct Rcc
	{
		std::atomic<std::uint32_t> CR;
		std::atomic<std::uint32_t> ICSCR;
		std::atomic<std::uint32_t> CFGR;
		std::atomic<std::uint32_t> PLLCFGR;
		std::atomic<std::uint32_t> PLLSAI1CFGR;
		std::atomic<std::uint32_t> _reserved14;
		std::atomic<std::uint32_t> CIER;
		std::atomic<std::uint32_t> CIFR;
		std::atomic<std::uint32_t> CICR;
		std::atomic<std::uint32_t> _reserved24;
		std::atomic<std::uint32_t> AHB1RSTR;
		std::atomic<std::uint32_t> AHB2RSTR;
		std::atomic<std::uint32_t> AHB3RSTR;
		std::atomic<std::uint32_t> _reserved34;
		std::atomic<std::uint32_t> APB1RSTR1;
		std::atomic<std::uint32_t> APB1RSTR2;
		std::atomic<std::uint32_t> APB2RSTR;
		std::atomic<std::uint32_t> _reserved44;
		std::atomic<std::uint32_t> AHB1ENR;
		std::atomic<std::uint32_t> AHB2ENR;
		std::atomic<std::uint32_t> AHB3ENR;
		std::atomic<std::uint32_t> _reserved54;
		std::atomic<std::uint32_t> APB1ENR1;
		std::atomic<std::uint32_t> APB1ENR2;
		std::atomic<std::uint32_t> APB2ENR;
		std::atomic<std::uint32_t> _reserved64;
		std::atomic<std::uint32_t> AHB1SMENR;
		std::atomic<std::uint32_t> AHB2SMENR;
		std::atomic<std::uint32_t> AHB3SMENR;
		std::atomic<std::uint32_t> _reserved74;
		std::atomic<std::uint32_t> APB1SMENR1;
		std::atomic<std::uint32_t> APB1SMENR2;
		std::atomic<std::uint32_t> APB2SMENR;
		std::atomic<std::uint32_t> _reserved84;
		std::atomic<std::uint32_t> CCIPR;
		std::atomic<std::uint32_t> _reserved8c;
		std::atomic<std::uint32_t> BDCR;
		std::atomic<std::uint32_t> CSR;
		std::atomic<std::uint32_t> CRRCR;
		std::atomic<std::uint32_t> CCIPR2;
	};

	static_assert(sizeof(Rcc) == 0xa0, "Native RCC register bank must be 160 bytes");
	static_assert(std::is_aggregate_v<Rcc>, "Native RCC register bank must be able to be memcpy()'d (POD)");

	extern "C"
	{
		extern Rcc __linker_peripherals_ahb1_rcc;
	}
}

#endif
