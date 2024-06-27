#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_ISRS_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ST_STM32_STM32L432KC_ISRS_HH
#include "../../../arm/cortex/m4/Isrs.hh"

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	class Isrs
	{
private:
		static void defaultIsr(void) noexcept;
		static void reservedIsr(void) noexcept;
		static void unavailableIsr(void) noexcept;

public:
		static void wwdg(void) noexcept;
		static void pvdPvm(void) noexcept;
		static void rtcTampCssLse(void) noexcept;
		static void rtcWkup(void) noexcept;
		static void flash(void) noexcept;
		static void rcc(void) noexcept;
		static void exti0(void) noexcept;
		static void exti1(void) noexcept;
		static void exti2(void) noexcept;
		static void exti3(void) noexcept;
		static void exti4(void) noexcept;
		static void dma1Ch1(void) noexcept;
		static void dma1Ch2(void) noexcept;
		static void dma1Ch3(void) noexcept;
		static void dma1Ch4(void) noexcept;
		static void dma1Ch5(void) noexcept;
		static void dma1Ch6(void) noexcept;
		static void dma1Ch7(void) noexcept;
		static void adc1(void) noexcept;
		static void can1Tx(void) noexcept;
		static void can1Rx0(void) noexcept;
		static void can1Rx1(void) noexcept;
		static void can1Sce(void) noexcept;
		static void exti9_5(void) noexcept;
		static void tim1BrkTim15(void) noexcept;
		static void tim1UpTim16(void) noexcept;
		static void tim1TrgCom(void) noexcept;
		static void tim1Cc(void) noexcept;
		static void tim2(void) noexcept;
		static void unavailableTim3(void) noexcept;
		static void reserved30(void) noexcept;
		static void i2c1Ev(void) noexcept;
		static void i2c1Er(void) noexcept;
		static void unavailableI2c2Ev(void) noexcept;
		static void unavailableI2c2Er(void) noexcept;
		static void spi1(void) noexcept;
		static void unavailableSpi2(void) noexcept;
		static void usart1(void) noexcept;
		static void usart2(void) noexcept;
		static void unavailableUsart3(void) noexcept;
		static void exti15_10(void) noexcept;
		static void rtcAlarm(void) noexcept;
		static void reserved42(void) noexcept;
		static void reserved43(void) noexcept;
		static void reserved44(void) noexcept;
		static void reserved45(void) noexcept;
		static void reserved46(void) noexcept;
		static void reserved47(void) noexcept;
		static void reserved48(void) noexcept;
		static void unavailableSdmmc1(void) noexcept;
		static void reserved50(void) noexcept;
		static void spi3(void) noexcept;
		static void unavailableUart4(void) noexcept;
		static void reserved53(void) noexcept;
		static void tim6DacUnder(void) noexcept;
		static void tim7(void) noexcept;
		static void dma2Ch1(void) noexcept;
		static void dma2Ch2(void) noexcept;
		static void dma2Ch3(void) noexcept;
		static void dma2Ch4(void) noexcept;
		static void dma2Ch5(void) noexcept;
		static void unavailableDfsdm1Flt0(void) noexcept;
		static void unavailableDfsdm1Flt1(void) noexcept;
		static void reserved63(void) noexcept;
		static void comp(void) noexcept;
		static void lpTim1(void) noexcept;
		static void lpTim2(void) noexcept;
		static void usbFs(void) noexcept;
		static void dma2Ch6(void) noexcept;
		static void dma2Ch7(void) noexcept;
		static void lpUart1(void) noexcept;
		static void quadSpi(void) noexcept;
		static void i2c3Ev(void) noexcept;
		static void i2c3Er(void) noexcept;
		static void sai1(void) noexcept;
		static void reserved75(void) noexcept;
		static void swpmi1(void) noexcept;
		static void tsc(void) noexcept;
		static void unavailableLcd(void) noexcept;
		static void aes(void) noexcept;
		static void rng(void) noexcept;
		static void fpu(void) noexcept;
		static void crs(void) noexcept;
		static void unavailableI2c4Ev(void) noexcept;
		static void unavailableI2c4Er(void) noexcept;
	};
}

#endif
