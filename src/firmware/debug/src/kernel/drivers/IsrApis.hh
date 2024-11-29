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

		template <template <IIsrApi...> typename TApiFactory>
		IsrApis(TApiFactory<TApis...> apiFactory) :
			apis((apiFactory.template create<TApis>(), ...))
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
