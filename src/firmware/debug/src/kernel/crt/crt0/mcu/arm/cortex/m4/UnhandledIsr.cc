#include "UnhandledIsr.hh"

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	[[gnu::used]]
	[[gnu::interrupt]]
	void UnhandledIsr::onInterrupt(void) noexcept
	{
		// TODO: ABORT WITH REASON
		while (1)
			;;
	}
}
