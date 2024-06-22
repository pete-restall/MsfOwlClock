#include "Isrs.hh"
#include "IsrVectorTable.hh"

extern "C"
{
	[[noreturn]]
	[[gnu::naked]]
	void _resetHandler(void) noexcept;
}

namespace smeg::kernel::crt0::mcu::arm::cortex::m4
{
	[[gnu::used]]
	[[gnu::section(".isr_vector_table.arm")]]
	static const IsrVector isrVectorTable[15] =
	{
		&_resetHandler,
		&Isrs::nmi,
		&Isrs::hardFault,
		&Isrs::memManage,
		&Isrs::busFault,
		&Isrs::usageFault,
		&Isrs::reserved7,
		&Isrs::reserved8,
		&Isrs::reserved9,
		&Isrs::reserved10,
		&Isrs::svCall,
		&Isrs::debugMonitor,
		&Isrs::reserved13,
		&Isrs::pendsv,
		&Isrs::sysTick
	};

	static_assert(sizeof(IsrVector) == 4, "The Cortex M4 ISR Vectors must be 32-bit pointers");
	static_assert(sizeof(isrVectorTable) == 15 * sizeof(IsrVector), "The Cortex M4 ISR Vector Table must consist of 15 vectors");
}
