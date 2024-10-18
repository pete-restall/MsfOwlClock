#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSFROM_HH
#include <cstdint>
#include <tuple>
#include "../../tuples/TupleProjection.hh"
#include "IHaveConfigForTasks.hh"
#include "ResourceToTaskAssociation.hh"
#include "TaskConfigsFrom.hh"

namespace smeg::kernel::tasks::config
{
	using namespace smeg::kernel::tuples;

	template <IHaveConfigForTasks TConfig>
	class TasksFrom
	{
	private:
		template <typename TTaskConfig, std::size_t InputIndex, std::size_t OutputIndex>
		struct TaskConfigsToAssociations;

		template <IHaveConfigForSimpleTask TTaskConfig, std::size_t InputIndex, std::size_t OutputIndex>
		struct TaskConfigsToAssociations<TTaskConfig, InputIndex, OutputIndex>
		{
			using AsTuple = std::tuple<ResourceToTaskAssociation<typename TTaskConfig::Type, OutputIndex>>;
		};

		template <IHaveConfigForOverlaidTasks TTaskConfig, std::size_t InputIndex, std::size_t OutputIndex>
		struct TaskConfigsToAssociations<TTaskConfig, InputIndex, OutputIndex>
		{
			template <typename TOverlayTask, std::size_t OverlayIndex>
			struct OverlayToAssociation
			{
				using AsTuple = std::tuple<ResourceToTaskAssociation<TOverlayTask, OutputIndex + OverlayIndex>>;
			};

			using AsTuple = TupleProjection<typename TTaskConfig::Types, OverlayToAssociation>::Output;
		};

		template <typename TTaskAssociation>
		struct AssociationsToTypes
		{
			using AsTuple = std::tuple<typename TTaskAssociation::Resource>;
		};

	public:
		using Associations = TupleProjection<typename TConfig::Tasks, TaskConfigsToAssociations>::Output;
		using Types = TupleProjection<Associations, AssociationsToTypes>::Output;
	};
}

#endif
