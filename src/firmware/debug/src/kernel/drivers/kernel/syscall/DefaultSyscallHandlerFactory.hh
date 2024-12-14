#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_DEFAULTSYSCALLHANDLERFACTORY_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_DEFAULTSYSCALLHANDLERFACTORY_HH
#include <cstddef>

#include "kernel/drivers/config/IProvidedSyscallConfig.hh"

namespace smeg::kernel::drivers::kernel::syscall
{
	using namespace smeg::kernel::drivers::config;

	template <
		IProvidedSyscallConfig TSyscallConfig,
		std::size_t McuCoreId
//		template <typename, std::size_t, typename...> typename TApiFactory, // TODO: This will need to be part of the definition
	>
	class DefaultSyscallHandlerFactory
	{
	public:
		static auto createSyscallHandler(void) noexcept // TODO: WRITE TESTS FOR THIS - noexcept ALSO NEEDS TO BE TESTED FOR...
		{
			return typename TSyscallConfig::Handler(); // TODO: NEEDS APIS (POSSIBLY), ETC.
		}
	};
}

#endif
