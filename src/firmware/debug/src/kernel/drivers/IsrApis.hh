#ifndef __SMEG_KERNEL_DRIVERS_ISRAPIS_HH
#define __SMEG_KERNEL_DRIVERS_ISRAPIS_HH
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

		template <typename TConfig, template <typename, IIsrApi...> typename TApiFactory>
		IsrApis(TApiFactory<TConfig, TApis...> apiFactory) :
			apis((apiFactory.template createApi<TApis>(), ...))
		{
		}

		template <IIsrApi TApi>
		auto &get(void)
		{
			return std::get<TApi>(this->apis);
		}
	};
}

#endif
