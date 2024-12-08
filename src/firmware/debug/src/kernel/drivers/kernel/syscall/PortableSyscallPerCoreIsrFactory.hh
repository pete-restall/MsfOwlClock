#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISRFACTORY_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISRFACTORY_HH
#include <tuple>

#include "PortableSyscallPerCoreIsr.hh"

namespace smeg::kernel::drivers::kernel::syscall
{
	template <auto McuCoreId, typename TSyscallHandlers>
	class PortableSyscallPerCoreIsrFactory;

	template <auto McuCoreId, typename... TSyscallHandlers>
	class PortableSyscallPerCoreIsrFactory<McuCoreId, std::tuple<TSyscallHandlers...>>
	{
	public:
		static consteval auto createPortableSyscallPerCoreIsr(void) noexcept
		{
			// TODO: Write the (non-stub) functionality for this - don't forget to create a SyscallApis to allow injection as well
			return PortableSyscallPerCoreIsr<std::tuple<>>();
		}
	};
}

#endif
