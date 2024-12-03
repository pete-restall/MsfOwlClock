#include "ReservedIsr.hh"

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	[[gnu::interrupt, general_regs_only]]
	void ReservedIsr::onInterrupt(void) noexcept
	{
		// TODO: ABORT WITH REASON
		while (1)
			;;
	}
}
