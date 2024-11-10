#ifndef __SMEG_KERNEL_TASKS_DRIVERTOKERNELAPIS_HH
#define __SMEG_KERNEL_TASKS_DRIVERTOKERNELAPIS_HH
#include <tuple>

#include "../IDriverToKernelApi.hh"

namespace smeg::kernel::tasks
{
	template <IDriverToKernelApi... TApis>
	class DriverToKernelApis
	{
	private:
		std::tuple<TApis...> apis;

	public:
		using AsTuple = decltype(apis);

		template <template <IDriverToKernelApi...> typename TApiFactory>
		DriverToKernelApis(TApiFactory<TApis...> apiFactory) :
			apis((apiFactory.template create<TApis>(), ...))
		{
		}

		template <IDriverToKernelApi TApi>
		auto &get(void)
		{
			return std::get<TApi>(this->apis);
		}
	};
}

#endif
