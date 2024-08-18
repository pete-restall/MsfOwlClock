#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKSFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKSFROM_HH
#include <cstdint>
#include <tuple>
#include "IHaveConfigForTasks.hh"
#include "ResourceToTaskAssociation.hh"

namespace smeg::kernel::tasks::config
{
	// TODO: This needs to be moved to another file and tested in isolation - currently tested via TaskStacksFrom...
	template <std::size_t FirstTaskId, typename TTaskConfig>
	struct TaskConfigToResourceAssociation;

	template <std::size_t FirstTaskId, IHaveConfigForSimpleTask TTaskConfig>
	struct TaskConfigToResourceAssociation<FirstTaskId, TTaskConfig>
	{
		using Type = ResourceToTaskAssociation<TTaskConfig, FirstTaskId>;

		static constexpr std::size_t nextTaskId = FirstTaskId + 1;
	};

	// TODO: This needs to be moved to another file and tested in isolation - currently tested via TaskStacksFrom...
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


	// TODO: This needs to be moved to another file and tested in isolation - currently tested via TaskStacksFrom...
	template <IHaveConfigForTasks TConfig>
	class TaskConfigsFrom
	{
	private:
		template <std::size_t N, typename T>
		struct RepeatedAsTuple
		{
			using Type = decltype(std::tuple_cat(std::tuple<T>{}, typename RepeatedAsTuple<N - 1, T>::Type{}));
		};

		template <typename T>
		struct RepeatedAsTuple<0, T>
		{
			using Type = std::tuple<>;
		};

		template <typename T>
		struct AsTuple;

		template <IHaveConfigForSimpleTask T>
		struct AsTuple<T>
		{
			using Type = std::tuple<T>;
		};

		template <IHaveConfigForOverlaidTasks T>
		struct AsTuple<T>
		{
			using Type = typename RepeatedAsTuple<std::tuple_size_v<typename T::Types>, T>::Type;
		};

		template <typename... TTaskConfigs>
		static constexpr auto configsPerTaskFrom(std::tuple<TTaskConfigs...>)
		{
			return std::tuple_cat((typename AsTuple<TTaskConfigs>::Type{}) ...);
		}

		template <std::size_t TaskId, typename TTaskConfigHead, typename... TTaskConfigTail>
		static consteval auto configsPerConfigFrom(std::tuple<TTaskConfigHead, TTaskConfigTail...>)
		{
			using Association = TaskConfigToResourceAssociation<TaskId, TTaskConfigHead>;
			if constexpr (sizeof...(TTaskConfigTail) == 0)
				return std::tuple<typename Association::Type>{};
			else
				return std::tuple_cat(std::tuple<typename Association::Type>{}, configsPerConfigFrom<Association::nextTaskId>(std::tuple<TTaskConfigTail...>{}));
		}

		template <std::size_t TaskId>
		static consteval auto configsPerConfigFrom(std::tuple<>)
		{
			return std::tuple<>{};
		}

	public:
		using PerConfig = decltype(configsPerConfigFrom<0>(typename TConfig::Tasks{}));
		using PerTask = decltype(configsPerTaskFrom(typename TConfig::Tasks{}));
	};

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
