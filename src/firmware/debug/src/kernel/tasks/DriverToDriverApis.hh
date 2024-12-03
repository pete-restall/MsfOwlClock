#ifndef __SMEG_KERNEL_TASKS_DRIVERTODRIVERAPIS_HH
#define __SMEG_KERNEL_TASKS_DRIVERTODRIVERAPIS_HH
#include <tuple>

#include "../IDriverToDriverApi.hh"

namespace smeg::kernel::tasks
{
	template <IDriverToDriverApi... TApis>
	class DriverToDriverApis
	{
	private:
		std::tuple<TApis...> apis;

	public:
		using AsTuple = decltype(apis);

		template <typename TConfig, template <typename, IDriverToDriverApi...> typename TApiFactory>
		DriverToDriverApis(TApiFactory<TConfig, TApis...> apiFactory) :
			apis((apiFactory.template createApi<TApis>(), ...))
		{
		}

		template <IDriverToDriverApi TApi>
		auto &get(void)
		{
			return std::get<TApi>(this->apis);
		}
	};
}

#endif
