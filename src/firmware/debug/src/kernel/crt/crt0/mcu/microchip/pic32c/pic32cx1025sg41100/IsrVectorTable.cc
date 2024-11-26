#include <array>

#include "../../../../../../drivers/config/DriverIsrConfigsFrom.hh"
#include "../../../../../../drivers/config/IsrOrDefaultByIrqFrom.hh"
#include "../../../../../../drivers/config/RequiredDriverConfigsFrom.hh"
#include "../../../arm/cortex/m4/IsrVectorTable.hh"
#include "../../../arm/cortex/m4/ReservedIsr.hh"
#include "../../../arm/cortex/m4/UnhandledIsr.hh"
#include "KernelConfigs.hh"

using namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4;
using namespace smeg::kernel::drivers::config;

namespace smeg::kernel::crt::crt0::mcu::microchip::pic32c::pic32cx1025sg41100
{
	using RequiredDriverConfigs = RequiredDriverConfigsFrom<KernelConfigs>::PerConfig;
	using IsrConfigs = DriverIsrConfigsFrom<RequiredDriverConfigs>::PerConfig;

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
	using UnhandledeicExtint0Isr = UnhandledIsr;
	using UnhandledeicExtint1Isr = UnhandledIsr;
	using UnhandledeicExtint2Isr = UnhandledIsr;
	using UnhandledeicExtint3Isr = UnhandledIsr;
	using UnhandledeicExtint4Isr = UnhandledIsr;
	using UnhandledeicExtint5Isr = UnhandledIsr;
	using UnhandledeicExtint6Isr = UnhandledIsr;
	using UnhandledeicExtint7Isr = UnhandledIsr;
	using UnhandledeicExtint8Isr = UnhandledIsr;
	using UnhandledeicExtint9Isr = UnhandledIsr;
	using UnhandledeicExtint10Isr = UnhandledIsr;
	using UnhandledeicExtint11Isr = UnhandledIsr;
	using UnhandledeicExtint12Isr = UnhandledIsr;
	using UnhandledeicExtint13Isr = UnhandledIsr;
	using UnhandledeicExtint14Isr = UnhandledIsr;
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
		&IsrOrDefaultByIrqFrom<IsrConfigs, 16, UnhandledPmIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 17, UnhandledMclkIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 18, UnhandledOscctrlXosc0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 19, UnhandledOscctrlXosc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 20, UnhandledOscctrlDfllIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 21, UnhandledOscctrlDpll0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 22, UnhandledOscctrlDpll1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 23, UnhandledOsc32kCtrlIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 24, UnhandledSupcOtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 25, UnhandledSupcBoddetIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 26, UnhandledWdtIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 27, UnhandledRtcIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 28, UnhandledeicExtint0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 29, UnhandledeicExtint1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 30, UnhandledeicExtint2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 31, UnhandledeicExtint3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 32, UnhandledeicExtint4Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 33, UnhandledeicExtint5Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 34, UnhandledeicExtint6Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 35, UnhandledeicExtint7Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 36, UnhandledeicExtint8Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 37, UnhandledeicExtint9Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 38, UnhandledeicExtint10Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 39, UnhandledeicExtint11Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 40, UnhandledeicExtint12Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 41, UnhandledeicExtint13Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 42, UnhandledeicExtint14Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 43, UnhandledEicExtint15Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 44, UnhandledFreqmIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 45, UnhandledNvmctrl0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 46, UnhandledNvmctrl1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 47, UnhandledDmac0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 48, UnhandledDmac1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 49, UnhandledDmac2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 50, UnhandledDmac3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 51, UnhandledDmacOTHERIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 52, UnhandledEvsys0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 53, UnhandledEvsys1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 54, UnhandledEvsys2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 55, UnhandledEvsys3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 56, UnhandledEvsysOtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 57, UnhandledPacIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 58, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 59, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 60, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 61, UnhandledRamEccIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 62, UnhandledSercom0_0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 63, UnhandledSercom0_1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 64, UnhandledSercom0_2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 65, UnhandledSercom0OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 66, UnhandledSercom1_0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 67, UnhandledSercom1_1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 68, UnhandledSercom1_2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 69, UnhandledSercom1OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 70, UnhandledSercom2_0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 71, UnhandledSercom2_1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 72, UnhandledSercom2_2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 73, UnhandledSercom2OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 74, UnhandledSercom3_0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 75, UnhandledSercom3_1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 76, UnhandledSercom3_2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 77, UnhandledSercom3OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 78, UnhandledSercom4_0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 79, UnhandledSercom4_1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 80, UnhandledSercom4_2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 81, UnhandledSercom4OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 82, UnhandledSercom5_0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 83, UnhandledSercom5_1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 84, UnhandledSercom5_2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 85, UnhandledSercom5OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 86, UnhandledSercom6_0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 87, UnhandledSercom6_1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 88, UnhandledSercom6_2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 89, UnhandledSercom6OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 90, UnhandledSercom7_0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 91, UnhandledSercom7_1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 92, UnhandledSercom7_2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 93, UnhandledSercom7OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 94, UnhandledCan0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 95, UnhandledCan1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 96, UnhandledUsbOtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 97, UnhandledUsbSofHsofIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 98, UnhandledUsbTrcpt0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 99, UnhandledUsbTrcpt1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 100, UnhandledGmacIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 101, UnhandledTcc0OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 102, UnhandledTcc0Mc0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 103, UnhandledTcc0Mc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 104, UnhandledTcc0Mc2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 105, UnhandledTcc0Mc3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 106, UnhandledTcc0Mc4Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 107, UnhandledTcc0Mc5Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 108, UnhandledTcc1OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 109, UnhandledTcc1Mc0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 110, UnhandledTcc1Mc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 111, UnhandledTcc1Mc2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 112, UnhandledTcc1Mc3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 113, UnhandledTcc2OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 114, UnhandledTcc2Mc0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 115, UnhandledTcc2Mc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 116, UnhandledTcc2Mc2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 117, UnhandledTcc3OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 118, UnhandledTcc3Mc0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 119, UnhandledTcc3Mc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 120, UnhandledTcc4OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 121, UnhandledTcc4Mc0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 122, UnhandledTcc4Mc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 123, UnhandledTc0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 124, UnhandledTc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 125, UnhandledTc2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 126, UnhandledTc3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 127, UnhandledTc4Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 128, UnhandledTc5Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 129, UnhandledTc6Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 130, UnhandledTc7Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 131, UnhandledPdecOtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 132, UnhandledPdecMc0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 133, UnhandledPdecMc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 134, UnhandledAdc0OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 135, UnhandledAdc0ResrdyIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 136, UnhandledAdc1OtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 137, UnhandledAdc1ResrdyIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 138, UnhandledAcIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 139, UnhandledDacOtherIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 140, UnhandledDacEmpty0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 141, UnhandledDacEmpty1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 142, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 143, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 144, UnhandledI2sIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 145, UnhandledPccIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 146, UnhandledAesIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 147, UnhandledTrngIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 148, UnhandledIcmIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 149, UnhandledPukccIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 150, UnhandledQspiIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 151, UnhandledSdhc0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 152, UnhandledSdhc1Isr>::Handler::onInterrupt
	};

	static_assert(sizeof(isrVectorTable) == 137 * sizeof(IsrVector), "The PIC32CX1025SG41100 ISR Vector Table must consist of 137 vectors");
};
