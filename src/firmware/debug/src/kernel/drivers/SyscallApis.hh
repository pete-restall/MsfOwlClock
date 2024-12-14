#ifndef __SMEG_KERNEL_DRIVERS_SYSCALLAPIS_HH
#define __SMEG_KERNEL_DRIVERS_SYSCALLAPIS_HH
#include <cstddef>
#include <tuple>

#include "ISyscallApi.hh"

namespace smeg::kernel::drivers
{
	template <ISyscallApi... TApis>
	class SyscallApis
	{
	private:
		std::tuple<TApis...> apis;

	public:
		using AsTuple = decltype(apis);

		template <typename TConfig, std::size_t McuCoreId, template <typename, std::size_t, ISyscallApi...> typename TApiFactory>
		SyscallApis(TApiFactory<TConfig, McuCoreId, TApis...> apiFactory) noexcept :
			apis(apiFactory.template createApi<TApis>() ...)
		{
			static_assert(
				(noexcept(apiFactory.template createApi<TApis>()) && ...),
				"Syscall API factories must not throw exceptions because they are used to initialise global variables");
		}

		template <ISyscallApi TApi>
		auto &get(void)
		{
			return std::get<TApi>(this->apis);
		}
	};
}

#endif
