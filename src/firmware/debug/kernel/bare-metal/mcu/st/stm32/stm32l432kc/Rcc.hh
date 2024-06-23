#ifndef __SMEG_KERNEL_BAREMETAL_MCU_ST_STM32_STM32L432KC_RCC_HH
#define __SMEG_KERNEL_BAREMETAL_MCU_ST_STM32_STM32L432KC_RCC_HH
#include <type_traits>
#include "../../../../Register.hh"

namespace smeg::kernel::bare_metal::mcu::st::stm32::stm32l432kc
{
	struct Rcc
	{
		RegisterU32 CR;
		RegisterU32 ICSCR;
		RegisterU32 CFGR;
		RegisterU32 PLLCFGR;
		RegisterU32 PLLSAI1CFGR;
		RegisterU32 _reserved14;
		RegisterU32 CIER;
		RegisterU32 CIFR;
		RegisterU32 CICR;
		RegisterU32 _reserved24;
		RegisterU32 AHB1RSTR;
		RegisterU32 AHB2RSTR;
		RegisterU32 AHB3RSTR;
		RegisterU32 _reserved34;
		RegisterU32 APB1RSTR1;
		RegisterU32 APB1RSTR2;
		RegisterU32 APB2RSTR;
		RegisterU32 _reserved44;
		RegisterU32 AHB1ENR;
		RegisterU32 AHB2ENR;
		RegisterU32 AHB3ENR;
		RegisterU32 _reserved54;
		RegisterU32 APB1ENR1;
		RegisterU32 APB1ENR2;
		RegisterU32 APB2ENR;
		RegisterU32 _reserved64;
		RegisterU32 AHB1SMENR;
		RegisterU32 AHB2SMENR;
		RegisterU32 AHB3SMENR;
		RegisterU32 _reserved74;
		RegisterU32 APB1SMENR1;
		RegisterU32 APB1SMENR2;
		RegisterU32 APB2SMENR;
		RegisterU32 _reserved84;
		RegisterU32 CCIPR;
		RegisterU32 _reserved8c;
		RegisterU32 BDCR;
		RegisterU32 CSR;
		RegisterU32 CRRCR;
		RegisterU32 CCIPR2;
	};

	static_assert(sizeof(Rcc) == 0xa0, "Native RCC register bank must be 160 bytes");
	static_assert(std::is_standard_layout_v<Rcc>, "Native RCC register bank must be standard layout");

	extern "C"
	{
		extern volatile Rcc __linker_peripherals_ahb1_rcc;
	}
}

#endif
