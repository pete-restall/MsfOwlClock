#ifndef __SMEG_KERNEL_DRIVERS_ISRAPIS_HH
#define __SMEG_KERNEL_DRIVERS_ISRAPIS_HH
#include <cstddef>
#include <tuple>

#include "IIsrApi.hh"

namespace smeg::kernel::drivers
{
	template <IIsrApi... TApis>
	class IsrApis
	{
	private:
		std::tuple<TApis...> apis;

	public:
		using AsTuple = decltype(apis);

		template <typename TConfig, std::size_t McuCoreId, template <typename, std::size_t, IIsrApi...> typename TApiFactory>
		IsrApis(TApiFactory<TConfig, McuCoreId, TApis...> apiFactory) noexcept :
			apis(apiFactory.template createApi<TApis>() ...)
		{
			static_assert(
				(noexcept(apiFactory.template createApi<TApis>()) && ...),
				"ISR API factories must not throw exceptions because they are used to initialise global variables");
		}

		template <IIsrApi TApi>
		auto &get(void)
		{
			return std::get<TApi>(this->apis);
		}
	};
}

#endif
