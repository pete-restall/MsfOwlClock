#ifndef __SMEG_KERNEL_CURRENTTASKSYSCALLAPI_HH
#define __SMEG_KERNEL_CURRENTTASKSYSCALLAPI_HH

namespace smeg::kernel
{
	class CurrentTaskSyscallApi
	{
		// TODO: This class needs to be written.  It also needs a proper place to live, possibly the 'scheduler' driver or somesuch.
		// The idea is this API is available to be injected into Syscalls so that they can query, control and manipulate the Task that's
		// currently running on the core they're executing on, for example to terminate it, change its priority or its state.
	};
}

#endif
