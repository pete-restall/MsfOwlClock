#include <array>

#include "isrs.hh"
#include "ReservedIsr.hh"
#include "UnhandledIsr.hh"

extern "C"
{
	[[noreturn]]
	[[gnu::naked]]
	void _resetHandler(void) noexcept;
}

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
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
		&IsrOrDefaultByIrq<2, UnhandledNmiIsr>::onInterrupt,
		&IsrOrDefaultByIrq<3, UnhandledHardFaultIsr>::onInterrupt,
		&IsrOrDefaultByIrq<4, UnhandledMemManageIsr>::onInterrupt,
		&IsrOrDefaultByIrq<5, UnhandledBusFaultIsr>::onInterrupt,
		&IsrOrDefaultByIrq<6, UnhandledUsageFaultIsr>::onInterrupt,
		&IsrOrDefaultByIrq<7, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<8, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<9, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<10, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<11, UnhandledSvcallIsr>::onInterrupt,
		&IsrOrDefaultByIrq<12, UnhandledDebugMonitorIsr>::onInterrupt,
		&IsrOrDefaultByIrq<13, ReservedIsr>::onInterrupt,
		&IsrOrDefaultByIrq<14, UnhandledPendsvIsr>::onInterrupt,
		&IsrOrDefaultByIrq<15, UnhandledSysTickIsr>::onInterrupt
	};

	static_assert(sizeof(IsrVector) == 4, "The Cortex M4 ISR Vectors must be 32-bit pointers");
	static_assert(sizeof(isrVectorTable) == 15 * sizeof(IsrVector), "The Cortex M4 ISR Vector Table must consist of 15 vectors");
}
