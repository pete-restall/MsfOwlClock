#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISRFACTORY_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISRFACTORY_HH
#include <cstdint>
#include <tuple>

namespace smeg::kernel::drivers::kernel::syscall
{
	template <auto McuCoreId, typename TSyscallHandlers>
	class PortableSyscallPerCoreIsrFactory;

	template <auto McuCoreId, typename... TSyscallHandlers>
	class PortableSyscallPerCoreIsrFactory<McuCoreId, std::tuple<TSyscallHandlers...>>
	{
	public:
//		static auto createSyscallPerCoreIsr(void) noexcept
//		{
// TODO: Don't forget to create a SyscallApis to allow injection as well
//		}
	};
}

#endif
