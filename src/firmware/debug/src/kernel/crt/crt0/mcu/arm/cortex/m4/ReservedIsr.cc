#include "ReservedIsr.hh"

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	[[gnu::general_regs_only]] // TODO: general_regs_only doesn't seem to work; GCC bug ?  Manual says the attribute is 'general-regs-only', but that is not syntactically valid for a C++ attribute.  Use the old-style attribute for this instead ?
	void ReservedIsr::onInterrupt(void) noexcept
	{
		// TODO: ABORT WITH REASON
		while (1)
			;;
	}
}
