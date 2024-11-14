#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKCONFIGSFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKCONFIGSFROM_HH
#include <cstddef>
#include <tuple>

#include "../../tuples/AsTuple.hh"
#include "../../tuples/TupleCat.hh"
#include "IHaveConfigForTasks.hh"
#include "ResourceToTaskAssociation.hh"
#include "TaskConfigToResourceAssociation.hh"

namespace smeg::kernel::tasks::config
{
	using namespace smeg::kernel::tuples;

	template <IHaveConfigForTasks TConfig>
	class TaskConfigsFrom
	{
	private:
		template <std::size_t N, std::size_t TaskId, typename TTaskConfig>
		struct Repeated
		{
			using AsTuple = TupleCat<
				std::tuple<ResourceToTaskAssociation<TTaskConfig, TaskId>>,
				typename Repeated<N - 1, TaskId + 1, TTaskConfig>::AsTuple>;
		};

		template <std::size_t TaskId, typename TTaskConfig>
		struct Repeated<0, TaskId, TTaskConfig>
		{
			using AsTuple = std::tuple<>;
		};

		template <std::size_t TaskId, typename... TTaskConfigs>
		struct ConfigsPerConfigFrom;

		template <std::size_t TaskId, typename TTaskConfigHead, typename... TTaskConfigTail>
		struct ConfigsPerConfigFrom<TaskId, TTaskConfigHead, TTaskConfigTail...>
		{
			using Association = TaskConfigToResourceAssociation<TaskId, TTaskConfigHead>;
			using AsTuple = TupleCat<
				std::tuple<typename Association::Type>,
				typename ConfigsPerConfigFrom<Association::nextTaskId, TTaskConfigTail...>::AsTuple>;
		};

		template <std::size_t TaskId>
		struct ConfigsPerConfigFrom<TaskId>
		{
			using AsTuple = std::tuple<>;
		};

		template <typename... T>
		struct _PerConfig;

		template <typename... T>
		struct _PerConfig<std::tuple<T...>>
		{
			using AsTuple = typename ConfigsPerConfigFrom<0, T...>::AsTuple;
		};

		template <std::size_t TaskId, typename... TTaskConfigs>
		struct ConfigsPerTaskFrom;

		template <std::size_t TaskId, typename TTaskConfigHead, typename... TTaskConfigTail>
		struct ConfigsPerTaskFrom<TaskId, TTaskConfigHead, TTaskConfigTail...>
		{
			using Association = TaskConfigToResourceAssociation<TaskId, TTaskConfigHead>;
			using AsTuple = TupleCat<
				typename Repeated<Association::numberOfTasks, TaskId, TTaskConfigHead>::AsTuple,
				typename ConfigsPerTaskFrom<Association::nextTaskId, TTaskConfigTail...>::AsTuple>;
		};

		template <std::size_t TaskId>
		struct ConfigsPerTaskFrom<TaskId>
		{
			using AsTuple = std::tuple<>;
		};

		template <typename... T>
		struct _PerTask;

		template <typename... T>
		struct _PerTask<std::tuple<T...>>
		{
			using AsTuple = typename ConfigsPerTaskFrom<0, T...>::AsTuple;
		};

		using TaskConfigsAsTuple = AsTuple<typename TConfig::Tasks>;

	public:
		using PerConfig = typename _PerConfig<TaskConfigsAsTuple>::AsTuple;
		using PerTask = typename _PerTask<TaskConfigsAsTuple>::AsTuple;
	};
}

#endif
