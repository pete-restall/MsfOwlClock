#include "../../../arm/cortex/m4/Isrs.hh"

#include "Isrs.hh"

#define __PIC32CX1025SG41100_ISRS_CLASS "_ZN4smeg6kernel3crt4crt03mcu9microchip6pic32c18pic32cx1025sg411004Isrs"
#define __PIC32CX1025SG41100_DEFAULT_ISR_NAME __PIC32CX1025SG41100_ISRS_CLASS "10defaultIsrEv"
#define __PIC32CX1025SG41100_RESERVED_ISR_NAME __PIC32CX1025SG41100_ISRS_CLASS "11reservedIsrEv"

namespace smeg::kernel::crt::crt0::mcu::microchip::pic32c::pic32cx1025sg41100
{
	[[gnu::naked]]
	void Isrs::defaultIsr(void) noexcept
	{
		__asm__ volatile ("b.n " __PIC32CX1025SG41100_DEFAULT_ISR_NAME);
	}

	[[gnu::naked]]
	void Isrs::reservedIsr(void) noexcept
	{
		__asm__ volatile ("b.n " __PIC32CX1025SG41100_RESERVED_ISR_NAME);
	}

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::pm(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::mclk(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::oscctrlXosc0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::oscctrlXosc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::oscctrlDfll(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::oscctrlDpll0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::oscctrlDpll1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::osc32kCtrl(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::supcOther(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::supcBoddet(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::wdt(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::rtc(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint4(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint5(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint6(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint7(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint8(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint9(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint10(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint11(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint12(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint13(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint14(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::eicExtint15(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::freqm(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::nvmctrl0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::nvmctrl1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::dmac0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::dmac1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::dmac2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::dmac3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::dmacOTHER(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::evsys0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::evsys1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::evsys2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::evsys3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::evsysOther(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::pac(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_RESERVED_ISR_NAME)]]
	void Isrs::reserved42(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_RESERVED_ISR_NAME)]]
	void Isrs::reserved43(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_RESERVED_ISR_NAME)]]
	void Isrs::reserved44(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::ramEcc(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom0_0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom0_1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom0_2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom0Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom1_0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom1_1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom1_2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom1Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom2_0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom2_1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom2_2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom2Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom3_0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom3_1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom3_2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom3Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom4_0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom4_1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom4_2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom4Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom5_0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom5_1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom5_2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom5Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom6_0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom6_1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom6_2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom6Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom7_0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom7_1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom7_2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sercom7Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::can0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::can1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::usbOther(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::usbSofHsof(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::usbTrcpt0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::usbTrcpt1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::gmac(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc0Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc0Mc0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc0Mc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc0Mc2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc0Mc3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc0Mc4(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc0Mc5(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc1Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc1Mc0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc1Mc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc1Mc2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc1Mc3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc2Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc2Mc0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc2Mc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc2Mc2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc3Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc3Mc0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc3Mc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc4Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc4Mc0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tcc4Mc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tc0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tc2(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tc3(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tc4(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tc5(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tc6(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::tc7(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::pdecOther(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::pdecMc0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::pdecMc1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::adc0Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::adc0Resrdy(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::adc1Other(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::adc1Resrdy(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::ac(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::dacOther(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::dacEmpty0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::dacEmpty1(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_RESERVED_ISR_NAME)]]
	void Isrs::reserved126(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_RESERVED_ISR_NAME)]]
	void Isrs::reserved127(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::i2s(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::pcc(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::aes(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::trng(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::icm(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::pukcc(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::qspi(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sdhc0(void) noexcept;

	[[gnu::weak]]
	[[gnu::alias(__PIC32CX1025SG41100_DEFAULT_ISR_NAME)]]
	void Isrs::sdhc1(void) noexcept;
}
