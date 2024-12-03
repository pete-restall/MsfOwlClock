#ifndef __SMEG_KERNEL_TASKS_APPTODRIVERAPIS_HH
#define __SMEG_KERNEL_TASKS_APPTODRIVERAPIS_HH
#include <tuple>

#include "../IAppToDriverApi.hh"

namespace smeg::kernel::tasks
{
	template <IAppToDriverApi... TApis>
	class AppToDriverApis
	{
	private:
		std::tuple<TApis...> apis;

	public:
		using AsTuple = decltype(apis);

		template <typename TConfig, template <typename, IAppToDriverApi...> typename TApiFactory>
		AppToDriverApis(TApiFactory<TConfig, TApis...> apiFactory) :
			apis((apiFactory.template createApi<TApis>(), ...))
		{
		}

		template <IAppToDriverApi TApi>
		auto &get(void)
		{
			return std::get<TApi>(this->apis);
		}
	};
}

#endif
