#include "../../../arm/cortex/m4/IsrVectorTable.hh"

using namespace smeg::kernel::crt0::mcu::arm::cortex::m4;

namespace smeg::kernel::crt0::mcu::microchip::pic32c::pic32cx1025sg41100
{
	[[gnu::used]]
	[[gnu::section(".isr_vector_table.mcu")]]
	static const IsrVector isrVectorTable[137] =
	{
		// ...
	};

	static_assert(sizeof(isrVectorTable) == 137 * sizeof(IsrVector), "The PIC32CX1025SG41100 ISR Vector Table must consist of 137 vectors");
};
