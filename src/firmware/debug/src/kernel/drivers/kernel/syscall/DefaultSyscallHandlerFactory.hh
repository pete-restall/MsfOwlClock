#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_DEFAULTSYSCALLHANDLERFACTORY_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_DEFAULTSYSCALLHANDLERFACTORY_HH
#include <cstddef>
#include <tuple>

#include "kernel/IHaveRequiredApis.hh"
#include "kernel/drivers/ISyscallApi.hh"
#include "kernel/drivers/SyscallApis.hh"
#include "kernel/drivers/config/IProvidedSyscallConfig.hh"

namespace smeg::kernel::drivers::kernel::syscall
{
	using namespace smeg::kernel::drivers::config;

	template <
		IProvidedSyscallConfig TSyscallConfig,
		std::size_t McuCoreId,
		template <IProvidedSyscallConfig, std::size_t, ISyscallApi...> typename TApiFactory>
	class DefaultSyscallHandlerFactory
	{
	private:
		template <typename... TApis>
		struct ApiFactory;

		template <typename... TApis>
		struct ApiFactory<std::tuple<TApis...>>
		{
			using Type = TApiFactory<TSyscallConfig, McuCoreId, TApis...>;
		};

	public:
		static auto createSyscallHandler(void) noexcept
		{
			using SyscallHandler = TSyscallConfig::Handler;
			// TODO: if TSyscallConfig::Factory, then return TSyscallConfig::Factory<TSyscallConfig, McuCoreId, TApiFactory>::createSyscallHandler()
			if constexpr (IHaveRequiredApis<SyscallHandler, SyscallApis>)
			{
				using RequiredApis = SyscallHandler::RequiredApis;
				using TupleOfApis = RequiredApis::AsTuple;
				static_assert(
					noexcept(SyscallHandler(RequiredApis(typename ApiFactory<TupleOfApis>::Type()))),
					"Syscall Handler constructors must not throw exceptions because they are used to initialise global variables");

				return SyscallHandler(RequiredApis(typename ApiFactory<TupleOfApis>::Type()));
			}
			else
			{
				static_assert(
					noexcept(SyscallHandler()),
					"Syscall Handler constructors must not throw exceptions because they are used to initialise global variables");

				return SyscallHandler();
			}
		}
	};
}

#endif
