#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKCONFIGSFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKCONFIGSFROM_HH
#include <cstdint>
#include <tuple>
#include "IHaveConfigForTasks.hh"
#include "ResourceToTaskAssociation.hh"
#include "TaskConfigToResourceAssociation.hh"

namespace smeg::kernel::tasks::config
{
	template <IHaveConfigForTasks TConfig>
	class TaskConfigsFrom
	{
	private:
		template <std::size_t N, std::size_t TaskId, typename TTaskConfig>
		struct Repeated
		{
			using Tuple = decltype(std::tuple_cat(
				std::tuple<ResourceToTaskAssociation<TTaskConfig, TaskId>>{},
				typename Repeated<N - 1, TaskId + 1, TTaskConfig>::Tuple{}));
		};

		template <std::size_t TaskId, typename TTaskConfig>
		struct Repeated<0, TaskId, TTaskConfig>
		{
			using Tuple = std::tuple<>;
		};

		template <std::size_t TaskId, typename TTaskConfigHead, typename... TTaskConfigTail>
		static consteval auto configsPerTaskFrom(std::tuple<TTaskConfigHead, TTaskConfigTail...>)
		{
			using Association = TaskConfigToResourceAssociation<TaskId, TTaskConfigHead>;
			return std::tuple_cat(
				typename Repeated<Association::numberOfTasks, TaskId, TTaskConfigHead>::Tuple{},
				configsPerTaskFrom<Association::nextTaskId>(std::tuple<TTaskConfigTail...>{}));
		}

		template <std::size_t TaskId>
		static consteval auto configsPerTaskFrom(std::tuple<>)
		{
			return std::tuple<>{};
		}

		template <std::size_t TaskId, typename TTaskConfigHead, typename... TTaskConfigTail>
		static consteval auto configsPerConfigFrom(std::tuple<TTaskConfigHead, TTaskConfigTail...>)
		{
			using Association = TaskConfigToResourceAssociation<TaskId, TTaskConfigHead>;
			return std::tuple_cat(
				std::tuple<typename Association::Type>{},
				configsPerConfigFrom<Association::nextTaskId>(std::tuple<TTaskConfigTail...>{}));
		}

		template <std::size_t TaskId>
		static consteval auto configsPerConfigFrom(std::tuple<>)
		{
			return std::tuple<>{};
		}

	public:
		using PerConfig = decltype(configsPerConfigFrom<0>(std::tuple_cat(typename TConfig::Tasks{})));
		using PerTask = decltype(configsPerTaskFrom<0>(std::tuple_cat(typename TConfig::Tasks{})));
	};
}

#endif
