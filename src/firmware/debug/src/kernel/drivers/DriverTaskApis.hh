#ifndef __SMEG_KERNEL_DRIVERS_DRIVERTASKAPIS_HH
#define __SMEG_KERNEL_DRIVERS_DRIVERTASKAPIS_HH
#include <tuple>

#include "IDriverTaskApi.hh"

namespace smeg::kernel::drivers
{
	template <IDriverTaskApi... TApis>
	class DriverTaskApis
	{
	private:
		std::tuple<TApis...> apis;

	public:
		using AsTuple = decltype(apis);

		template <typename TConfig, template <typename, IDriverTaskApi...> typename TApiFactory>
		DriverTaskApis(TApiFactory<TConfig, TApis...> apiFactory) :
			apis((apiFactory.template createApi<TApis>(), ...))
		{
		}

		template <IDriverTaskApi TApi>
		auto &get(void)
		{
			return std::get<TApi>(this->apis);
		}
	};
}

#endif
