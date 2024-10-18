#ifndef __SMEG_KERNEL_CRT_CRT0_ENTRYPOINTFACTORY_HH
#define __SMEG_KERNEL_CRT_CRT0_ENTRYPOINTFACTORY_HH
#include "../Entrypoint.hh"
#include "../ICrt0Environment.hh"

namespace smeg::kernel::crt::crt0
{
	struct EntrypointFactory
	{
		template <ICrt0Environment TCrt0Environment>
		static constexpr auto create(const TCrt0Environment crt0Environment) noexcept
		{
			// TODO: The factory abstraction now serves as the Composition Root and frees up the individual MCU-specific reset handlers from knowing
			// about all the other non-MCU-specific dependencies of the Entrypoint, such as those derived from the KernelConfig.  Start working those
			// into the application.
			return Entrypoint(crt0Environment);
		}
	};
}

#endif
