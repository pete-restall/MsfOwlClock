#ifndef __SMEG_KERNEL_DRIVERS_IISR_HH
#define __SMEG_KERNEL_DRIVERS_IISR_HH
#include <concepts>

namespace smeg::kernel::drivers
{
	template <typename T>
	concept IIsr = requires
	{
		{ T::onInterrupt() } noexcept -> std::same_as<void>;
	};
}

#endif
