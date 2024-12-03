#include <array>

#include "../../../arm/cortex/m4/isrs.hh"
#include "../../../arm/cortex/m4/ReservedIsr.hh"
#include "../../../arm/cortex/m4/UnhandledIsr.hh"

using namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4;

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	using UnhandledWwdgIsr = UnhandledIsr;
	using UnhandledPvdPvmIsr = UnhandledIsr;
	using UnhandledRtcTampCssLseIsr = UnhandledIsr;
	using UnhandledRtcWkupIsr = UnhandledIsr;
	using UnhandledFlashIsr = UnhandledIsr;
	using UnhandledRccIsr = UnhandledIsr;
	using UnhandledExti0Isr = UnhandledIsr;
	using UnhandledExti1Isr = UnhandledIsr;
	using UnhandledExti2Isr = UnhandledIsr;
	using UnhandledExti3Isr = UnhandledIsr;
	using UnhandledExti4Isr = UnhandledIsr;
	using UnhandledDma1Ch1Isr = UnhandledIsr;
	using UnhandledDma1Ch2Isr = UnhandledIsr;
	using UnhandledDma1Ch3Isr = UnhandledIsr;
	using UnhandledDma1Ch4Isr = UnhandledIsr;
	using UnhandledDma1Ch5Isr = UnhandledIsr;
	using UnhandledDma1Ch6Isr = UnhandledIsr;
	using UnhandledDma1Ch7Isr = UnhandledIsr;
	using UnhandledAdc1Isr = UnhandledIsr;
	using UnhandledCan1TxIsr = UnhandledIsr;
	using UnhandledCan1Rx0Isr = UnhandledIsr;
	using UnhandledCan1Rx1Isr = UnhandledIsr;
	using UnhandledCan1SceIsr = UnhandledIsr;
	using UnhandledExti9_5Isr = UnhandledIsr;
	using UnhandledTim1BrkTim15Isr = UnhandledIsr;
	using UnhandledTim1UpTim16Isr = UnhandledIsr;
	using UnhandledTim1TrgComIsr = UnhandledIsr;
	using UnhandledTim1CcIsr = UnhandledIsr;
	using UnhandledTim2Isr = UnhandledIsr;
	using UnhandledUnavailableTim3Isr = UnhandledIsr;
	using UnhandledI2c1EvIsr = UnhandledIsr;
	using UnhandledI2c1ErIsr = UnhandledIsr;
	using UnhandledUnavailableI2c2EvIsr = UnhandledIsr;
	using UnhandledUnavailableI2c2ErIsr = UnhandledIsr;
	using UnhandledSpi1Isr = UnhandledIsr;
	using UnhandledUnavailableSpi2Isr = UnhandledIsr;
	using UnhandledUsart1Isr = UnhandledIsr;
	using UnhandledUsart2Isr = UnhandledIsr;
	using UnhandledUnavailableUsart3Isr = UnhandledIsr;
	using UnhandledExti15_10Isr = UnhandledIsr;
	using UnhandledRtcAlarmIsr = UnhandledIsr;
	using UnhandledUnavailableSdmmc1Isr = UnhandledIsr;
	using UnhandledSpi3Isr = UnhandledIsr;
	using UnhandledUnavailableUart4Isr = UnhandledIsr;
	using UnhandledTim6DacUnder = UnhandledIsr;
	using UnhandledTim7Isr = UnhandledIsr;
	using UnhandledDma2Ch1Isr = UnhandledIsr;
	using UnhandledDma2Ch2Isr = UnhandledIsr;
	using UnhandledDma2Ch3Isr = UnhandledIsr;
	using UnhandledDma2Ch4Isr = UnhandledIsr;
	using UnhandledDma2Ch5Isr = UnhandledIsr;
	using UnhandledUnavailableDfsdm1Flt0Isr = UnhandledIsr;
	using UnhandledUnavailableDfsdm1Flt1Isr = UnhandledIsr;
	using UnhandledCompIsr = UnhandledIsr;
	using UnhandledLpTim1Isr = UnhandledIsr;
	using UnhandledLpTim2Isr = UnhandledIsr;
	using UnhandledUsbFsIsr = UnhandledIsr;
	using UnhandledDma2Ch6Isr = UnhandledIsr;
	using UnhandledDma2Ch7Isr = UnhandledIsr;
	using UnhandledLpUart1Isr = UnhandledIsr;
	using UnhandledQuadSpiIsr = UnhandledIsr;
	using UnhandledI2c3EvIsr = UnhandledIsr;
	using UnhandledI2c3ErIsr = UnhandledIsr;
	using UnhandledSai1Isr = UnhandledIsr;
	using UnhandledSwpmi1Isr = UnhandledIsr;
	using UnhandledTscIsr = UnhandledIsr;
	using UnhandledUnavailableLcdIsr = UnhandledIsr;
	using UnhandledAesIsr = UnhandledIsr;
	using UnhandledRngIsr = UnhandledIsr;
	using UnhandledFpuIsr = UnhandledIsr;
	using UnhandledCrsIsr = UnhandledIsr;
	using UnhandledUnavailableI2c4EvIsr = UnhandledIsr;
	using UnhandledUnavailableI2c4ErIsr = UnhandledIsr;

	[[gnu::used]]
	[[gnu::section(".isr_vector_table.mcu")]]
	static const std::array<IsrVector, 85> isrVectorTable
	{
		&IsrOrDefaultByIrq<16, UnhandledWwdgIsr>::onInterrupt,
		&IsrOrDefaultByIrq<17, UnhandledPvdPvmIsr>::onInterrupt,
		&IsrOrDefaultByIrq<18, UnhandledRtcTampCssLseIsr>::onInterrupt,
		&IsrOrDefaultByIrq<19, UnhandledRtcWkupIsr>::onInterrupt,
		&IsrOrDefaultByIrq<20, UnhandledFlashIsr>::onInterrupt,
		&IsrOrDefaultByIrq<21, UnhandledRccIsr>::onInterrupt,
		&IsrOrDefaultByIrq<22, UnhandledExti0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<23, UnhandledExti1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<24, UnhandledExti2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<25, UnhandledExti3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<26, UnhandledExti4Isr>::onInterrupt,
		&IsrOrDefaultByIrq<27, UnhandledDma1Ch1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<28, UnhandledDma1Ch2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<29, UnhandledDma1Ch3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<30, UnhandledDma1Ch4Isr>::onInterrupt,
		&IsrOrDefaultByIrq<31, UnhandledDma1Ch5Isr>::onInterrupt,
		&IsrOrDefaultByIrq<32, UnhandledDma1Ch6Isr>::onInterrupt,
		&IsrOrDefaultByIrq<33, UnhandledDma1Ch7Isr>::onInterrupt,
		&IsrOrDefaultByIrq<34, UnhandledAdc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<35, UnhandledCan1TxIsr>::onInterrupt,
		&IsrOrDefaultByIrq<36, UnhandledCan1Rx0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<37, UnhandledCan1Rx1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<38, UnhandledCan1SceIsr>::onInterrupt,
		&IsrOrDefaultByIrq<39, UnhandledExti9_5Isr>::onInterrupt,
		&IsrOrDefaultByIrq<40, UnhandledTim1BrkTim15Isr>::onInterrupt,
		&IsrOrDefaultByIrq<41, UnhandledTim1UpTim16Isr>::onInterrupt,
		&IsrOrDefaultByIrq<42, UnhandledTim1TrgComIsr>::onInterrupt,
		&IsrOrDefaultByIrq<43, UnhandledTim1CcIsr>::onInterrupt,
		&IsrOrDefaultByIrq<44, UnhandledTim2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<45, UnhandledUnavailableTim3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<46, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<47, UnhandledI2c1EvIsr>::onInterrupt,
		&IsrOrDefaultByIrq<48, UnhandledI2c1ErIsr>::onInterrupt,
		&IsrOrDefaultByIrq<49, UnhandledUnavailableI2c2EvIsr>::onInterrupt,
		&IsrOrDefaultByIrq<50, UnhandledUnavailableI2c2ErIsr>::onInterrupt,
		&IsrOrDefaultByIrq<51, UnhandledSpi1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<52, UnhandledUnavailableSpi2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<53, UnhandledUsart1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<54, UnhandledUsart2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<55, UnhandledUnavailableUsart3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<56, UnhandledExti15_10Isr>::onInterrupt,
		&IsrOrDefaultByIrq<57, UnhandledRtcAlarmIsr>::onInterrupt,
		&IsrOrDefaultByIrq<58, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<59, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<60, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<61, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<62, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<63, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<64, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<65, UnhandledUnavailableSdmmc1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<66, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<67, UnhandledSpi3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<68, UnhandledUnavailableUart4Isr>::onInterrupt,
		&IsrOrDefaultByIrq<69, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<70, UnhandledTim6DacUnder>::onInterrupt,
		&IsrOrDefaultByIrq<71, UnhandledTim7Isr>::onInterrupt,
		&IsrOrDefaultByIrq<72, UnhandledDma2Ch1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<73, UnhandledDma2Ch2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<74, UnhandledDma2Ch3Isr>::onInterrupt,
		&IsrOrDefaultByIrq<75, UnhandledDma2Ch4Isr>::onInterrupt,
		&IsrOrDefaultByIrq<76, UnhandledDma2Ch5Isr>::onInterrupt,
		&IsrOrDefaultByIrq<77, UnhandledUnavailableDfsdm1Flt0Isr>::onInterrupt,
		&IsrOrDefaultByIrq<78, UnhandledUnavailableDfsdm1Flt1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<79, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<80, UnhandledCompIsr>::onInterrupt,
		&IsrOrDefaultByIrq<81, UnhandledLpTim1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<82, UnhandledLpTim2Isr>::onInterrupt,
		&IsrOrDefaultByIrq<83, UnhandledUsbFsIsr>::onInterrupt,
		&IsrOrDefaultByIrq<84, UnhandledDma2Ch6Isr>::onInterrupt,
		&IsrOrDefaultByIrq<85, UnhandledDma2Ch7Isr>::onInterrupt,
		&IsrOrDefaultByIrq<86, UnhandledLpUart1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<87, UnhandledQuadSpiIsr>::onInterrupt,
		&IsrOrDefaultByIrq<88, UnhandledI2c3EvIsr>::onInterrupt,
		&IsrOrDefaultByIrq<89, UnhandledI2c3ErIsr>::onInterrupt,
		&IsrOrDefaultByIrq<90, UnhandledSai1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<91, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<92, UnhandledSwpmi1Isr>::onInterrupt,
		&IsrOrDefaultByIrq<93, UnhandledTscIsr>::onInterrupt,
		&IsrOrDefaultByIrq<94, UnhandledUnavailableLcdIsr>::onInterrupt,
		&IsrOrDefaultByIrq<95, UnhandledAesIsr>::onInterrupt,
		&IsrOrDefaultByIrq<96, UnhandledRngIsr>::onInterrupt,
		&IsrOrDefaultByIrq<97, UnhandledFpuIsr>::onInterrupt,
		&IsrOrDefaultByIrq<98, UnhandledCrsIsr>::onInterrupt,
		&IsrOrDefaultByIrq<99, UnhandledUnavailableI2c4EvIsr>::onInterrupt,
		&IsrOrDefaultByIrq<100, UnhandledUnavailableI2c4ErIsr>::onInterrupt
	};

	static_assert(sizeof(isrVectorTable) == 85 * sizeof(IsrVector), "The STM32L432KC ISR Vector Table must consist of 85 vectors");
};
