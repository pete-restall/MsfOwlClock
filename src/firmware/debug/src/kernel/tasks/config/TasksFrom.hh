#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSFROM_HH
#include <cstdint>
#include <tuple>
#include "IHaveConfigForTasks.hh"
#include "ResourceToTaskAssociation.hh"
#include "TaskConfigsFrom.hh"

namespace smeg::kernel::tasks::config
{
	template <IHaveConfigForTasks TConfig>
	class TasksFrom
	{
	private:
		template <std::size_t TaskId, typename T>
		struct AsTuple;

		template <std::size_t TaskId, IHaveConfigForSimpleTask TTaskConfig>
		struct AsTuple<TaskId, TTaskConfig>
		{
			using Associations = std::tuple<ResourceToTaskAssociation<typename TTaskConfig::Type, TaskId>>;
		};

		template <std::size_t FirstTaskId, IHaveConfigForOverlaidTasks TTaskConfig>
		class AsTuple<FirstTaskId, TTaskConfig>
		{
		private:
			template <std::size_t TaskId, typename TTaskHead, typename... TTaskTail>
			static consteval auto typesFromOverlayConfig(std::tuple<TTaskHead, TTaskTail...>)
			{
				return std::tuple_cat(
					std::tuple<ResourceToTaskAssociation<TTaskHead, TaskId>>{},
					typesFromOverlayConfig<TaskId + 1>(std::tuple<TTaskTail...>{}));
			}

			template <std::size_t TaskId>
			static consteval auto typesFromOverlayConfig(std::tuple<>)
			{
				return std::tuple<>{};
			}

		public:
			using Associations = decltype(typesFromOverlayConfig<FirstTaskId>(typename TTaskConfig::Types{}));
		};

		template <std::size_t TaskId, typename TTaskConfigHead, typename... TTaskConfigTail>
		static consteval auto taskAssociationsFrom(std::tuple<TTaskConfigHead, TTaskConfigTail...>)
		{
			using TaskConfigHeadAssociations = typename AsTuple<TaskId, TTaskConfigHead>::Associations;
			constexpr auto nextTaskId = TaskId + std::tuple_size_v<TaskConfigHeadAssociations>;
			return std::tuple_cat(
				TaskConfigHeadAssociations{},
				taskAssociationsFrom<nextTaskId>(std::tuple<TTaskConfigTail...>{}));
		}

		template <std::size_t TaskId>
		static consteval auto taskAssociationsFrom(std::tuple<>)
		{
			return std::tuple<>{};
		}

		template <typename TTaskAssociationHead, typename... TTaskAssociationTail>
		static consteval auto tasksFrom(std::tuple<TTaskAssociationHead, TTaskAssociationTail...>)
		{
			return std::tuple_cat(
				std::tuple<typename TTaskAssociationHead::ResourceType>{},
				tasksFrom(std::tuple<TTaskAssociationTail...>{}));
		}

		static consteval auto tasksFrom(std::tuple<>)
		{
			return std::tuple<>{};
		}

	public:
		using Associations = decltype(taskAssociationsFrom<0>(typename TConfig::Tasks{}));
		using Types = decltype(tasksFrom(Associations{}));
	};
}

#endif
