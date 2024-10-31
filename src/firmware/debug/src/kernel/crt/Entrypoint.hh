#ifndef __SMEG_KERNEL_CRT_ENTRYPOINT_HH
#define __SMEG_KERNEL_CRT_ENTRYPOINT_HH
#include "../IStaticVoidRunnable.hh"
#include "ICrt0Environment.hh"

#ifndef MCU_IS_NATIVE
#define NO_RETURN noreturn
#define UNREACHABLE __builtin_unreachable()
#else
#define NO_RETURN
#define UNREACHABLE
#endif

namespace smeg::kernel::crt
{
	template <ICrt0Environment TCrt0Environment, IStaticVoidNoExceptRunnable TInitialisationTaskRunner>
	class Entrypoint
	{
	private:
		const TCrt0Environment environment;

	public:
		Entrypoint(const TCrt0Environment crt0Environment) noexcept :
			environment(crt0Environment)
		{
		}

		[[NO_RETURN]]
		void run(void) const noexcept
		{
			auto bootloader(this->environment.getBootloader());
			bootloader.onPreEntrypoint();

			auto kernelMemoryMap = this->environment.getLinkerMemoryMap().getLinkerMemoryMapForKernel();
			kernelMemoryMap.getInitialiserForRamSections().initialise();
			kernelMemoryMap.getInitialiserForCodeSections().initialise();

			bootloader.onPostEntrypoint();
			TInitialisationTaskRunner::run();

			UNREACHABLE;
		}
	};
}

#endif
