#ifndef __SMEG_KERNEL_CRT_ENTRYPOINT_HH
#define __SMEG_KERNEL_CRT_ENTRYPOINT_HH
#include "ICrt0Environment.hh"

extern void blinkyBlinky(void);

namespace smeg::kernel::crt
{
	template <ICrt0Environment TCrt0Environment>
	class Entrypoint
	{
	private:
		TCrt0Environment environment;

	public:
		Entrypoint(TCrt0Environment crt0Environment) noexcept :
			environment(crt0Environment)
		{
		}

		[[gnu::noreturn]] // TODO: THIS SHOULD BE CONDITIONAL - IF RUNNING ON HOST (IE. TESTS) THEN IT SHOULD BE RETURNABLE...
		void run(void) const noexcept
		{
			// TODO: WE'RE NOW AT A POINT WHERE THINGS RUN AGAIN IN HARDWARE - TIDY ALL THIS UP AND START TDD-ING IT...
			auto kernelMemoryMap = this->environment.getLinkerMemoryMap().getLinkerMemoryMapForKernel();
			auto appMemoryMap = this->environment.getLinkerMemoryMap().getLinkerMemoryMapForApp();

			kernelMemoryMap.getInitialiserForRamSections().initialise();
			appMemoryMap.getInitialiserForRamSections().initialise();

			kernelMemoryMap.getInitialiserForCodeSections().initialise();
			appMemoryMap.getInitialiserForCodeSections().initialise();
			blinkyBlinky();

			// need a big try...catch around this to comply with noexcept
			while (1)
				;;
		}
	};
}

#endif
