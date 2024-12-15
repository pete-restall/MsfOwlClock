#include <array>

#include "../../../arm/cortex/m4/isrs.hh"
#include "../../../arm/cortex/m4/ReservedIsr.hh"
#include "../../../arm/cortex/m4/UnhandledIsr.hh"

using namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4;

namespace smeg::kernel::crt::crt0::mcu::microchip::pic32c::pic32cx1025sg41100
{
	using UnhandledPmIsr = UnhandledIsr;
	using UnhandledMclkIsr = UnhandledIsr;
	using UnhandledOscctrlXosc0Isr = UnhandledIsr;
	using UnhandledOscctrlXosc1Isr = UnhandledIsr;
	using UnhandledOscctrlDfllIsr = UnhandledIsr;
	using UnhandledOscctrlDpll0Isr = UnhandledIsr;
	using UnhandledOscctrlDpll1Isr = UnhandledIsr;
	using UnhandledOsc32kCtrlIsr = UnhandledIsr;
	using UnhandledSupcOtherIsr = UnhandledIsr;
	using UnhandledSupcBoddetIsr = UnhandledIsr;
	using UnhandledWdtIsr = UnhandledIsr;
	using UnhandledRtcIsr = UnhandledIsr;
	using UnhandledEicExtint0Isr = UnhandledIsr;
	using UnhandledEicExtint1Isr = UnhandledIsr;
	using UnhandledEicExtint2Isr = UnhandledIsr;
	using UnhandledEicExtint3Isr = UnhandledIsr;
	using UnhandledEicExtint4Isr = UnhandledIsr;
	using UnhandledEicExtint5Isr = UnhandledIsr;
	using UnhandledEicExtint6Isr = UnhandledIsr;
	using UnhandledEicExtint7Isr = UnhandledIsr;
	using UnhandledEicExtint8Isr = UnhandledIsr;
	using UnhandledEicExtint9Isr = UnhandledIsr;
	using UnhandledEicExtint10Isr = UnhandledIsr;
	using UnhandledEicExtint11Isr = UnhandledIsr;
	using UnhandledEicExtint12Isr = UnhandledIsr;
	using UnhandledEicExtint13Isr = UnhandledIsr;
	using UnhandledEicExtint14Isr = UnhandledIsr;
	using UnhandledEicExtint15Isr = UnhandledIsr;
	using UnhandledFreqmIsr = UnhandledIsr;
	using UnhandledNvmctrl0Isr = UnhandledIsr;
	using UnhandledNvmctrl1Isr = UnhandledIsr;
	using UnhandledDmac0Isr = UnhandledIsr;
	using UnhandledDmac1Isr = UnhandledIsr;
	using UnhandledDmac2Isr = UnhandledIsr;
	using UnhandledDmac3Isr = UnhandledIsr;
	using UnhandledDmacOTHERIsr = UnhandledIsr;
	using UnhandledEvsys0Isr = UnhandledIsr;
	using UnhandledEvsys1Isr = UnhandledIsr;
	using UnhandledEvsys2Isr = UnhandledIsr;
	using UnhandledEvsys3Isr = UnhandledIsr;
	using UnhandledEvsysOtherIsr = UnhandledIsr;
	using UnhandledPacIsr = UnhandledIsr;
	using UnhandledRamEccIsr = UnhandledIsr;
	using UnhandledSercom0_0Isr = UnhandledIsr;
	using UnhandledSercom0_1Isr = UnhandledIsr;
	using UnhandledSercom0_2Isr = UnhandledIsr;
	using UnhandledSercom0OtherIsr = UnhandledIsr;
	using UnhandledSercom1_0Isr = UnhandledIsr;
	using UnhandledSercom1_1Isr = UnhandledIsr;
	using UnhandledSercom1_2Isr = UnhandledIsr;
	using UnhandledSercom1OtherIsr = UnhandledIsr;
	using UnhandledSercom2_0Isr = UnhandledIsr;
	using UnhandledSercom2_1Isr = UnhandledIsr;
	using UnhandledSercom2_2Isr = UnhandledIsr;
	using UnhandledSercom2OtherIsr = UnhandledIsr;
	using UnhandledSercom3_0Isr = UnhandledIsr;
	using UnhandledSercom3_1Isr = UnhandledIsr;
	using UnhandledSercom3_2Isr = UnhandledIsr;
	using UnhandledSercom3OtherIsr = UnhandledIsr;
	using UnhandledSercom4_0Isr = UnhandledIsr;
	using UnhandledSercom4_1Isr = UnhandledIsr;
	using UnhandledSercom4_2Isr = UnhandledIsr;
	using UnhandledSercom4OtherIsr = UnhandledIsr;
	using UnhandledSercom5_0Isr = UnhandledIsr;
	using UnhandledSercom5_1Isr = UnhandledIsr;
	using UnhandledSercom5_2Isr = UnhandledIsr;
	using UnhandledSercom5OtherIsr = UnhandledIsr;
	using UnhandledSercom6_0Isr = UnhandledIsr;
	using UnhandledSercom6_1Isr = UnhandledIsr;
	using UnhandledSercom6_2Isr = UnhandledIsr;
	using UnhandledSercom6OtherIsr = UnhandledIsr;
	using UnhandledSercom7_0Isr = UnhandledIsr;
	using UnhandledSercom7_1Isr = UnhandledIsr;
	using UnhandledSercom7_2Isr = UnhandledIsr;
	using UnhandledSercom7OtherIsr = UnhandledIsr;
	using UnhandledCan0Isr = UnhandledIsr;
	using UnhandledCan1Isr = UnhandledIsr;
	using UnhandledUsbOtherIsr = UnhandledIsr;
	using UnhandledUsbSofHsofIsr = UnhandledIsr;
	using UnhandledUsbTrcpt0Isr = UnhandledIsr;
	using UnhandledUsbTrcpt1Isr = UnhandledIsr;
	using UnhandledGmacIsr = UnhandledIsr;
	using UnhandledTcc0OtherIsr = UnhandledIsr;
	using UnhandledTcc0Mc0Isr = UnhandledIsr;
	using UnhandledTcc0Mc1Isr = UnhandledIsr;
	using UnhandledTcc0Mc2Isr = UnhandledIsr;
	using UnhandledTcc0Mc3Isr = UnhandledIsr;
	using UnhandledTcc0Mc4Isr = UnhandledIsr;
	using UnhandledTcc0Mc5Isr = UnhandledIsr;
	using UnhandledTcc1OtherIsr = UnhandledIsr;
	using UnhandledTcc1Mc0Isr = UnhandledIsr;
	using UnhandledTcc1Mc1Isr = UnhandledIsr;
	using UnhandledTcc1Mc2Isr = UnhandledIsr;
	using UnhandledTcc1Mc3Isr = UnhandledIsr;
	using UnhandledTcc2OtherIsr = UnhandledIsr;
	using UnhandledTcc2Mc0Isr = UnhandledIsr;
	using UnhandledTcc2Mc1Isr = UnhandledIsr;
	using UnhandledTcc2Mc2Isr = UnhandledIsr;
	using UnhandledTcc3OtherIsr = UnhandledIsr;
	using UnhandledTcc3Mc0Isr = UnhandledIsr;
	using UnhandledTcc3Mc1Isr = UnhandledIsr;
	using UnhandledTcc4OtherIsr = UnhandledIsr;
	using UnhandledTcc4Mc0Isr = UnhandledIsr;
	using UnhandledTcc4Mc1Isr = UnhandledIsr;
	using UnhandledTc0Isr = UnhandledIsr;
	using UnhandledTc1Isr = UnhandledIsr;
	using UnhandledTc2Isr = UnhandledIsr;
	using UnhandledTc3Isr = UnhandledIsr;
	using UnhandledTc4Isr = UnhandledIsr;
	using UnhandledTc5Isr = UnhandledIsr;
	using UnhandledTc6Isr = UnhandledIsr;
	using UnhandledTc7Isr = UnhandledIsr;
	using UnhandledPdecOtherIsr = UnhandledIsr;
	using UnhandledPdecMc0Isr = UnhandledIsr;
	using UnhandledPdecMc1Isr = UnhandledIsr;
	using UnhandledAdc0OtherIsr = UnhandledIsr;
	using UnhandledAdc0ResrdyIsr = UnhandledIsr;
	using UnhandledAdc1OtherIsr = UnhandledIsr;
	using UnhandledAdc1ResrdyIsr = UnhandledIsr;
	using UnhandledAcIsr = UnhandledIsr;
	using UnhandledDacOtherIsr = UnhandledIsr;
	using UnhandledDacEmpty0Isr = UnhandledIsr;
	using UnhandledDacEmpty1Isr = UnhandledIsr;
	using UnhandledI2sIsr = UnhandledIsr;
	using UnhandledPccIsr = UnhandledIsr;
	using UnhandledAesIsr = UnhandledIsr;
	using UnhandledTrngIsr = UnhandledIsr;
	using UnhandledIcmIsr = UnhandledIsr;
	using UnhandledPukccIsr = UnhandledIsr;
	using UnhandledQspiIsr = UnhandledIsr;
	using UnhandledSdhc0Isr = UnhandledIsr;
	using UnhandledSdhc1Isr = UnhandledIsr;

	[[gnu::used]]
	[[gnu::section(".isr_vector_table.mcu")]]
	static const std::array<IsrVector, 137> isrVectorTable
	{
		&IsrOrDefaultByIrq<16, UnhandledPmIsr>::onInterrupt,
		&IsrOrDefaultByIrq<17, UnhandledMclkIsr>::onInterrupt,
		&IsrOrDefaultByIrq<18, UnhandledOscctrlXosc0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<19, UnhandledOscctrlXosc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<20, UnhandledOscctrlDfllIsr>::onInterrupt,
		&IsrOrDefaultByIrq<21, UnhandledOscctrlDpll0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<22, UnhandledOscctrlDpll1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<23, UnhandledOsc32kCtrlIsr>::onInterrupt,
		&IsrOrDefaultByIrq<24, UnhandledSupcOtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<25, UnhandledSupcBoddetIsr>::onInterrupt,
		&IsrOrDefaultByIrq<26, UnhandledWdtIsr>::onInterrupt,
		&IsrOrDefaultByIrq<27, UnhandledRtcIsr>::onInterrupt,
		&IsrOrDefaultByIrq<28, UnhandledEicExtint0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<29, UnhandledEicExtint1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<30, UnhandledEicExtint2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<31, UnhandledEicExtint3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<32, UnhandledEicExtint4Isr>::onInterrupt,
		&IsrOrDefaultByIrq<33, UnhandledEicExtint5Isr>::onInterrupt,
		&IsrOrDefaultByIrq<34, UnhandledEicExtint6Isr>::onInterrupt,
		&IsrOrDefaultByIrq<35, UnhandledEicExtint7Isr>::onInterrupt,
		&IsrOrDefaultByIrq<36, UnhandledEicExtint8Isr>::onInterrupt,
		&IsrOrDefaultByIrq<37, UnhandledEicExtint9Isr>::onInterrupt,
		&IsrOrDefaultByIrq<38, UnhandledEicExtint10Isr>::onInterrupt,
		&IsrOrDefaultByIrq<39, UnhandledEicExtint11Isr>::onInterrupt,
		&IsrOrDefaultByIrq<40, UnhandledEicExtint12Isr>::onInterrupt,
		&IsrOrDefaultByIrq<41, UnhandledEicExtint13Isr>::onInterrupt,
		&IsrOrDefaultByIrq<42, UnhandledEicExtint14Isr>::onInterrupt,
		&IsrOrDefaultByIrq<43, UnhandledEicExtint15Isr>::onInterrupt,
		&IsrOrDefaultByIrq<44, UnhandledFreqmIsr>::onInterrupt,
		&IsrOrDefaultByIrq<45, UnhandledNvmctrl0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<46, UnhandledNvmctrl1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<47, UnhandledDmac0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<48, UnhandledDmac1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<49, UnhandledDmac2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<50, UnhandledDmac3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<51, UnhandledDmacOTHERIsr>::onInterrupt,
		&IsrOrDefaultByIrq<52, UnhandledEvsys0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<53, UnhandledEvsys1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<54, UnhandledEvsys2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<55, UnhandledEvsys3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<56, UnhandledEvsysOtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<57, UnhandledPacIsr>::onInterrupt,
		&IsrOrDefaultByIrq<58, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<59, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<60, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<61, UnhandledRamEccIsr>::onInterrupt,
		&IsrOrDefaultByIrq<62, UnhandledSercom0_0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<63, UnhandledSercom0_1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<64, UnhandledSercom0_2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<65, UnhandledSercom0OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<66, UnhandledSercom1_0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<67, UnhandledSercom1_1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<68, UnhandledSercom1_2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<69, UnhandledSercom1OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<70, UnhandledSercom2_0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<71, UnhandledSercom2_1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<72, UnhandledSercom2_2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<73, UnhandledSercom2OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<74, UnhandledSercom3_0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<75, UnhandledSercom3_1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<76, UnhandledSercom3_2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<77, UnhandledSercom3OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<78, UnhandledSercom4_0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<79, UnhandledSercom4_1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<80, UnhandledSercom4_2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<81, UnhandledSercom4OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<82, UnhandledSercom5_0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<83, UnhandledSercom5_1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<84, UnhandledSercom5_2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<85, UnhandledSercom5OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<86, UnhandledSercom6_0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<87, UnhandledSercom6_1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<88, UnhandledSercom6_2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<89, UnhandledSercom6OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<90, UnhandledSercom7_0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<91, UnhandledSercom7_1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<92, UnhandledSercom7_2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<93, UnhandledSercom7OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<94, UnhandledCan0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<95, UnhandledCan1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<96, UnhandledUsbOtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<97, UnhandledUsbSofHsofIsr>::onInterrupt,
		&IsrOrDefaultByIrq<98, UnhandledUsbTrcpt0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<99, UnhandledUsbTrcpt1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<100, UnhandledGmacIsr>::onInterrupt,
		&IsrOrDefaultByIrq<101, UnhandledTcc0OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<102, UnhandledTcc0Mc0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<103, UnhandledTcc0Mc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<104, UnhandledTcc0Mc2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<105, UnhandledTcc0Mc3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<106, UnhandledTcc0Mc4Isr>::onInterrupt,
		&IsrOrDefaultByIrq<107, UnhandledTcc0Mc5Isr>::onInterrupt,
		&IsrOrDefaultByIrq<108, UnhandledTcc1OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<109, UnhandledTcc1Mc0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<110, UnhandledTcc1Mc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<111, UnhandledTcc1Mc2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<112, UnhandledTcc1Mc3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<113, UnhandledTcc2OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<114, UnhandledTcc2Mc0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<115, UnhandledTcc2Mc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<116, UnhandledTcc2Mc2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<117, UnhandledTcc3OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<118, UnhandledTcc3Mc0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<119, UnhandledTcc3Mc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<120, UnhandledTcc4OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<121, UnhandledTcc4Mc0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<122, UnhandledTcc4Mc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<123, UnhandledTc0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<124, UnhandledTc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<125, UnhandledTc2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<126, UnhandledTc3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<127, UnhandledTc4Isr>::onInterrupt,
		&IsrOrDefaultByIrq<128, UnhandledTc5Isr>::onInterrupt,
		&IsrOrDefaultByIrq<129, UnhandledTc6Isr>::onInterrupt,
		&IsrOrDefaultByIrq<130, UnhandledTc7Isr>::onInterrupt,
		&IsrOrDefaultByIrq<131, UnhandledPdecOtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<132, UnhandledPdecMc0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<133, UnhandledPdecMc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<134, UnhandledAdc0OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<135, UnhandledAdc0ResrdyIsr>::onInterrupt,
		&IsrOrDefaultByIrq<136, UnhandledAdc1OtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<137, UnhandledAdc1ResrdyIsr>::onInterrupt,
		&IsrOrDefaultByIrq<138, UnhandledAcIsr>::onInterrupt,
		&IsrOrDefaultByIrq<139, UnhandledDacOtherIsr>::onInterrupt,
		&IsrOrDefaultByIrq<140, UnhandledDacEmpty0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<141, UnhandledDacEmpty1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<142, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<143, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<144, UnhandledI2sIsr>::onInterrupt,
		&IsrOrDefaultByIrq<145, UnhandledPccIsr>::onInterrupt,
		&IsrOrDefaultByIrq<146, UnhandledAesIsr>::onInterrupt,
		&IsrOrDefaultByIrq<147, UnhandledTrngIsr>::onInterrupt,
		&IsrOrDefaultByIrq<148, UnhandledIcmIsr>::onInterrupt,
		&IsrOrDefaultByIrq<149, UnhandledPukccIsr>::onInterrupt,
		&IsrOrDefaultByIrq<150, UnhandledQspiIsr>::onInterrupt,
		&IsrOrDefaultByIrq<151, UnhandledSdhc0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<152, UnhandledSdhc1Isr>::onInterrupt
	};

	static_assert(sizeof(isrVectorTable) == 137 * sizeof(IsrVector), "The PIC32CX1025SG41100 ISR Vector Table must consist of 137 vectors");
};
