#include "Isrs.hh"

#define __STM32L432KC_ISRS_CLASS "_ZN4smeg6kernel3crt4crt03mcu2st5stm3211stm32l432kc4Isrs"
#define __STM32L432KC_DEFAULT_ISR_NAME __STM32L432KC_ISRS_CLASS "10defaultIsrEv"
#define __STM32L432KC_RESERVED_ISR_NAME __STM32L432KC_ISRS_CLASS "11reservedIsrEv"
#define __STM32L432KC_UNAVAILABLE_ISR_NAME __STM32L432KC_ISRS_CLASS "14unavailableIsrEv"

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	[[gnu::naked]]
	void Isrs::defaultIsr(void) noexcept
	{
		__asm__ volatile ("b.n " __ARM_CORTEX_M4_DEFAULT_ISR_NAME);
	}

	[[gnu::naked]]
	void Isrs::reservedIsr(void) noexcept
	{
		__asm__ volatile ("b.n " __ARM_CORTEX_M4_RESERVED_ISR_NAME);
	}

	[[gnu::naked]]
	void Isrs::unavailableIsr(void) noexcept
	{
		__asm__ volatile ("b.n " __ARM_CORTEX_M4_RESERVED_ISR_NAME);
	}

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::wwdg(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::pvdPvm(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::rtcTampCssLse(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::rtcWkup(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::flash(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::rcc(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::exti0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::exti1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::exti2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::exti3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::exti4(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma1Ch1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma1Ch2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma1Ch3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma1Ch4(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma1Ch5(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma1Ch6(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma1Ch7(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::adc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::can1Tx(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::can1Rx0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::can1Rx1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::can1Sce(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::exti9_5(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::tim1BrkTim15(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::tim1UpTim16(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::tim1TrgCom(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::tim1Cc(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::tim2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableTim3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved30(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::i2c1Ev(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::i2c1Er(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableI2c2Ev(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableI2c2Er(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::spi1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableSpi2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::usart1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::usart2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableUsart3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::exti15_10(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::rtcAlarm(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved42(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved43(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved44(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved45(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved46(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved47(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved48(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableSdmmc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved50(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::spi3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableUart4(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved53(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::tim6DacUnder(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::tim7(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma2Ch1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma2Ch2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma2Ch3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma2Ch4(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma2Ch5(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableDfsdm1Flt0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableDfsdm1Flt1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved63(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::comp(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::lpTim1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::lpTim2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::usbFs(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma2Ch6(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::dma2Ch7(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::lpUart1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::quadSpi(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::i2c3Ev(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::i2c3Er(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::sai1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_RESERVED_ISR_NAME)]]
	void Isrs::reserved75(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::swpmi1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::tsc(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableLcd(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::aes(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::rng(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::fpu(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_DEFAULT_ISR_NAME)]]
	void Isrs::crs(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableI2c4Ev(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__STM32L432KC_UNAVAILABLE_ISR_NAME)]]
	void Isrs::unavailableI2c4Er(void) noexcept;
}
