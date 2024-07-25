#include "../../../arm/cortex/m4/IsrVectorTable.hh"

using namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4;

namespace smeg::kernel::crt::crt0::mcu::microchip::pic32c::pic32cx1025sg41100
{
	[[gnu::used]]
	[[gnu::section(".isr_vector_table.mcu")]]
	static const IsrVector isrVectorTable[138] =
	{
		// TODO: Awaiting a response from Microchip support; the vectors aren't in the datasheets / reference manuals...???
		// ...
	};

	static_assert(sizeof(isrVectorTable) == 138 * sizeof(IsrVector), "The PIC32CX1025SG41100 ISR Vector Table must consist of 138 vectors");
};
