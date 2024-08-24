#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKCONFIGTORESOURCEASSOCIATION_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKCONFIGTORESOURCEASSOCIATION_HH
#include <cstdint>
#include <tuple>
#include <utility>
#include "IHaveConfigForTasks.hh"
#include "ResourceToTaskAssociation.hh"

namespace smeg::kernel::tasks::config
{
	template <std::size_t FirstTaskId, typename TTaskConfig>
	struct TaskConfigToResourceAssociation;

	template <std::size_t FirstTaskId, IHaveConfigForSimpleTask TTaskConfig>
	struct TaskConfigToResourceAssociation<FirstTaskId, TTaskConfig>
	{
		static constexpr std::size_t numberOfTasks = 1;
		static constexpr std::size_t nextTaskId = FirstTaskId + 1;

		using Type = ResourceToTaskAssociation<TTaskConfig, FirstTaskId>;
	};

	template <std::size_t FirstTaskId, IHaveConfigForOverlaidTasks TTaskConfig>
	class TaskConfigToResourceAssociation<FirstTaskId, TTaskConfig>
	{
	private:
		template <std::size_t... Seq>
		static constexpr auto asResourceToTaskAssociation(std::index_sequence<Seq...>)
		{
			return ResourceToTaskAssociation<TTaskConfig, FirstTaskId + Seq...>();
		}

	public:
		static constexpr std::size_t numberOfTasks = std::tuple_size_v<typename TTaskConfig::Types>;
		static constexpr std::size_t nextTaskId = FirstTaskId + numberOfTasks;

		using Type = decltype(asResourceToTaskAssociation(std::make_index_sequence<numberOfTasks>{}));
	};
}

#endif
