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
		using Type = ResourceToTaskAssociation<TTaskConfig, FirstTaskId>;

		static constexpr std::size_t nextTaskId = FirstTaskId + 1;
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

		static constexpr std::size_t numberOfTasks = std::tuple_size_v<typename TTaskConfig::Types>;

	public:
		using Type = decltype(asResourceToTaskAssociation(std::make_index_sequence<numberOfTasks>{}));

		static constexpr std::size_t nextTaskId = FirstTaskId + numberOfTasks;
	};
}

#endif
