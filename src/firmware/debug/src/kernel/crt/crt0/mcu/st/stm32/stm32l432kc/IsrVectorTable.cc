#include <array>

#include "../../../../../../drivers/config/DriverProvidedIsrConfigsFrom.hh"
#include "../../../../../../drivers/config/IsrOrDefaultByIrqFrom.hh"
#include "../../../../../../drivers/config/RequiredDriverConfigsFrom.hh"
#include "../../../arm/cortex/m4/IsrVectorTable.hh"
#include "../../../arm/cortex/m4/ReservedIsr.hh"
#include "../../../arm/cortex/m4/UnhandledIsr.hh"
#include "KernelConfigs.hh"

using namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4;
using namespace smeg::kernel::drivers::config;

namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	using RequiredDriverConfigs = RequiredDriverConfigsFrom<KernelConfigs>::PerConfig;
	using IsrConfigs = DriverProvidedIsrConfigsFrom<RequiredDriverConfigs>::PerConfig;

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
		&IsrOrDefaultByIrqFrom<IsrConfigs, 16, UnhandledWwdgIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 17, UnhandledPvdPvmIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 18, UnhandledRtcTampCssLseIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 19, UnhandledRtcWkupIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 20, UnhandledFlashIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 21, UnhandledRccIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 22, UnhandledExti0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 23, UnhandledExti1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 24, UnhandledExti2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 25, UnhandledExti3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 26, UnhandledExti4Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 27, UnhandledDma1Ch1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 28, UnhandledDma1Ch2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 29, UnhandledDma1Ch3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 30, UnhandledDma1Ch4Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 31, UnhandledDma1Ch5Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 32, UnhandledDma1Ch6Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 33, UnhandledDma1Ch7Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 34, UnhandledAdc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 35, UnhandledCan1TxIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 36, UnhandledCan1Rx0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 37, UnhandledCan1Rx1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 38, UnhandledCan1SceIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 39, UnhandledExti9_5Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 40, UnhandledTim1BrkTim15Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 41, UnhandledTim1UpTim16Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 42, UnhandledTim1TrgComIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 43, UnhandledTim1CcIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 44, UnhandledTim2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 45, UnhandledUnavailableTim3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 46, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 47, UnhandledI2c1EvIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 48, UnhandledI2c1ErIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 49, UnhandledUnavailableI2c2EvIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 50, UnhandledUnavailableI2c2ErIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 51, UnhandledSpi1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 52, UnhandledUnavailableSpi2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 53, UnhandledUsart1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 54, UnhandledUsart2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 55, UnhandledUnavailableUsart3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 56, UnhandledExti15_10Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 57, UnhandledRtcAlarmIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 58, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 59, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 60, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 61, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 62, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 63, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 64, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 65, UnhandledUnavailableSdmmc1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 66, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 67, UnhandledSpi3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 68, UnhandledUnavailableUart4Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 69, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 70, UnhandledTim6DacUnder>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 71, UnhandledTim7Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 72, UnhandledDma2Ch1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 73, UnhandledDma2Ch2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 74, UnhandledDma2Ch3Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 75, UnhandledDma2Ch4Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 76, UnhandledDma2Ch5Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 77, UnhandledUnavailableDfsdm1Flt0Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 78, UnhandledUnavailableDfsdm1Flt1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 79, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 80, UnhandledCompIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 81, UnhandledLpTim1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 82, UnhandledLpTim2Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 83, UnhandledUsbFsIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 84, UnhandledDma2Ch6Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 85, UnhandledDma2Ch7Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 86, UnhandledLpUart1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 87, UnhandledQuadSpiIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 88, UnhandledI2c3EvIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 89, UnhandledI2c3ErIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 90, UnhandledSai1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 91, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 92, UnhandledSwpmi1Isr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 93, UnhandledTscIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 94, UnhandledUnavailableLcdIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 95, UnhandledAesIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 96, UnhandledRngIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 97, UnhandledFpuIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 98, UnhandledCrsIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 99, UnhandledUnavailableI2c4EvIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 100, UnhandledUnavailableI2c4ErIsr>::Handler::onInterrupt
	};

	static_assert(sizeof(isrVectorTable) == 85 * sizeof(IsrVector), "The STM32L432KC ISR Vector Table must consist of 85 vectors");
};
