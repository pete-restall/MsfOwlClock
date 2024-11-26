#include <array>

#include "../../../../../../drivers/config/DriverProvidedIsrConfigsFrom.hh"
#include "../../../../../../drivers/config/IsrOrDefaultByIrqFrom.hh"
#include "../../../../../../drivers/config/RequiredDriverConfigsFrom.hh"
#include "../../../../KernelConfigs.hh"
#include "IsrVectorTable.hh"
#include "ReservedIsr.hh"
#include "UnhandledIsr.hh"

using namespace smeg::kernel::drivers::config;

extern "C"
{
	[[noreturn]]
	[[gnu::naked]]
	void _resetHandler(void) noexcept;
}

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	using RequiredDriverConfigs = RequiredDriverConfigsFrom<KernelConfigs>::PerConfig;
	using IsrConfigs = DriverProvidedIsrConfigsFrom<RequiredDriverConfigs>::PerConfig;

	using UnhandledNmiIsr = UnhandledIsr;
	using UnhandledHardFaultIsr = UnhandledIsr;
	using UnhandledMemManageIsr = UnhandledIsr;
	using UnhandledBusFaultIsr = UnhandledIsr;
	using UnhandledUsageFaultIsr = UnhandledIsr;
	using UnhandledSvcallIsr = UnhandledIsr;
	using UnhandledDebugMonitorIsr = UnhandledIsr;
	using UnhandledPendsvIsr = UnhandledIsr;
	using UnhandledSysTickIsr = UnhandledIsr;

	[[gnu::used]]
	[[gnu::section(".isr_vector_table.arm")]]
	static const std::array<IsrVector, 15> isrVectorTable
	{
		&_resetHandler,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 2, UnhandledNmiIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 3, UnhandledHardFaultIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 4, UnhandledMemManageIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 5, UnhandledBusFaultIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 6, UnhandledUsageFaultIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 7, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 8, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 9, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 10, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 11, UnhandledSvcallIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 12, UnhandledDebugMonitorIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 13, ReservedIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 14, UnhandledPendsvIsr>::Handler::onInterrupt,
		&IsrOrDefaultByIrqFrom<IsrConfigs, 15, UnhandledSysTickIsr>::Handler::onInterrupt
	};

	static_assert(sizeof(IsrVector) == 4, "The Cortex M4 ISR Vectors must be 32-bit pointers");
	static_assert(sizeof(isrVectorTable) == 15 * sizeof(IsrVector), "The Cortex M4 ISR Vector Table must consist of 15 vectors");
}
