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

		template <template <IAppToDriverApi...> typename TApiFactory>
		AppToDriverApis(TApiFactory<TApis...> apiFactory) :
			apis((apiFactory.template create<TApis>(), ...))
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
