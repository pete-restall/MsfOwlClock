#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISRFACTORY_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISRFACTORY_HH
#include <cstddef>
#include <tuple>

#include "kernel/drivers/ISyscallApi.hh"
#include "kernel/drivers/SyscallApis.hh"
#include "kernel/drivers/config/IProvidedIsrConfig.hh"

#include "PortableSyscallPerCoreIsr.hh"

namespace smeg::kernel::drivers::kernel::syscall
{
	using namespace smeg::kernel::drivers;
	using namespace smeg::kernel::drivers::config;

	template <
		IProvidedIsrConfig TIsrConfig,
		std::size_t McuCoreId,
		template <typename, std::size_t, typename...> typename TApiFactory,
		template <typename, std::size_t> typename THandlerFactory,
		typename THandlerConfigs>
	class PortableSyscallPerCoreIsrFactory;

	template <
		IProvidedIsrConfig TIsrConfig,
		std::size_t McuCoreId,
		template <typename, std::size_t, typename...> typename TApiFactory,
		template <typename, std::size_t> typename THandlerFactory,
		typename... THandlerConfigs>
	class PortableSyscallPerCoreIsrFactory<TIsrConfig, McuCoreId, TApiFactory, THandlerFactory, std::tuple<THandlerConfigs...>>
	{
	private:
		template <typename... TApis>
		struct ApiFactoryFor;

		template <typename... TApis>
		struct ApiFactoryFor<SyscallApis<TApis...>>
		{
			using Type = TApiFactory<TIsrConfig, McuCoreId, TApis...>;
		};

	public:
		static auto createPortableSyscallPerCoreIsr(void) noexcept
		{
			using SyscallHandlers = std::tuple<typename THandlerConfigs::Handler ...>;
			using SyscallIsr = PortableSyscallPerCoreIsr<SyscallHandlers>;
			using IsrRequiredApis = SyscallIsr::RequiredApis;
			using IsrApiFactory = ApiFactoryFor<IsrRequiredApis>::Type;
			static_assert(
				noexcept(SyscallIsr(
					IsrRequiredApis(IsrApiFactory()),
					SyscallHandlers(
						THandlerFactory<THandlerConfigs, McuCoreId>::createSyscallHandler()
						...))),
				"Syscall / ISR constructors must not throw exceptions because they are used to initialise global variables");

			return SyscallIsr(
				IsrRequiredApis(IsrApiFactory()),
				SyscallHandlers(
					THandlerFactory<THandlerConfigs, McuCoreId>::createSyscallHandler()
					...));
		}
	};
}

#endif
