#ifndef __SMEG_KERNEL_CRT_ENTRYPOINT_HH
#define __SMEG_KERNEL_CRT_ENTRYPOINT_HH
#include "ILinkerMemoryMap.hh"
#include "IResetMcu.hh"

namespace smeg::kernel::crt
{
	template <ILinkerMemoryMap TLinkerMemoryMap, IResetMcu TResetMcu>
	class Entrypoint
	{
public:
		// TODO: ROLL THESE TWO PARAMETERS INTO A SINGLE PARAMETER, SAY, TBootstrapper OR SOMETHING
		Entrypoint(TLinkerMemoryMap linkerMemoryMap, TResetMcu resetter) noexcept
		{
		}

		[[gnu::noreturn]] // TODO: THIS SHOULD BE CONDITIONAL - IF RUNNING ON HOST (IE. TESTS) THEN IT SHOULD BE RETURNABLE...
		void run(void) const noexcept
		{
			// need a big try...catch around this to comply with noexcept
			while (1)
				;;
		}
	};
}

#endif
