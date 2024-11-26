#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_SYSCALLFOR_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_SYSCALLFOR_HH
#include "kernel/config/IHaveTupleOfKernelConfigs.hh"

namespace smeg::kernel::drivers::kernel::syscall
{
	using namespace smeg::kernel::config;

	template <IHaveTupleOfKernelConfigs TKernelConfigs, typename TSyscall>
	class SyscallFor
	{
		// TODO: Needs writing.  Looks through all configs for a Driver with a ProvidedSyscallHandler for TSyscall.
	};
}

#endif
