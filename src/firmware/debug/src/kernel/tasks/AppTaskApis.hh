#ifndef __SMEG_KERNEL_TASKS_APPTASKAPIS_HH
#define __SMEG_KERNEL_TASKS_APPTASKAPIS_HH
#include <tuple>

#include "IAppTaskApi.hh"

namespace smeg::kernel::tasks
{
	template <IAppTaskApi... TApis>
	class AppTaskApis
	{
	private:
		std::tuple<TApis...> apis;

	public:
		using AsTuple = decltype(apis);

		template <typename TConfig, template <typename, IAppTaskApi...> typename TApiFactory>
		AppTaskApis(TApiFactory<TConfig, TApis...> apiFactory) :
			apis(apiFactory.template createApi<TApis>() ...)
		{
		}

		template <IAppTaskApi TApi>
		auto &get(void)
		{
			return std::get<TApi>(this->apis);
		}
	};
}

#endif
