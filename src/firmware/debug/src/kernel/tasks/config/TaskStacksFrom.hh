#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKSFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKSFROM_HH
#include <cstdint>
#include <tuple>
#include "IHaveConfigForTasks.hh"
#include "ResourceToTaskAssociation.hh"
#include "TaskConfigsFrom.hh"

namespace smeg::kernel::tasks::config
{
	template <IHaveConfigForTasks TConfig>
	class TaskStacksFrom
	{
	private:
		template <typename TTaskConfig, std::size_t... TaskIds>
		static consteval auto stackToTaskAssociationFrom(ResourceToTaskAssociation<TTaskConfig, TaskIds...>)
		{
			return std::make_tuple(ResourceToTaskAssociation<typename TTaskConfig::Stack, TaskIds...>{});
		}

		template <typename... TTaskConfigs>
		static consteval auto stackToTaskAssociationsFrom(std::tuple<TTaskConfigs...>)
		{
			return std::tuple_cat(stackToTaskAssociationFrom(TTaskConfigs{})...);
		}

	public:
		using PerStack = decltype(stackToTaskAssociationsFrom(typename TaskConfigsFrom<TConfig>::PerConfig{}));
	};
}

#endif
