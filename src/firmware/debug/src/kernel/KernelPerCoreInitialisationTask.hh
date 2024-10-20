#ifndef __SMEG_KERNEL_KERNELPERCOREINITIALISATIONTASK_HH
#define __SMEG_KERNEL_KERNELPERCOREINITIALISATIONTASK_HH

namespace smeg::kernel
{
	class KernelPerCoreInitialisationTask
	{
	private:

	public:
		void run(void)
		{
			// TODO: This task will run on each core as the first kernel task; it is possible an MCU-specific task runs before this (for example, to
			// set per-core stack pointers and enable cores so they can start executing from the reset handler), but that is an implementation detail
			// for the crt0 configuration.  This class deals with kernel-specific initialisation, not MCU-specific initialisation.
		}
	};
}

#endif
