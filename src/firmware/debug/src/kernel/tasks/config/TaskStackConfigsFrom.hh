#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKCONFIGSFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKCONFIGSFROM_HH
#include <tuple>
#include "../../tuples/TupleProjection.hh"
#include "IHaveConfigForTasks.hh"
#include "ResourceToTaskAssociation.hh"
#include "TaskConfigsFrom.hh"

namespace smeg::kernel::tasks::config
{
	using namespace smeg::kernel::tuples;

	template <IHaveConfigForTasks TConfig>
	class TaskStackConfigsFrom
	{
	private:
		template <typename TTaskConfig>
		struct StackConfigFromTaskConfig
		{
			using AsTuple = std::tuple<typename TTaskConfig::WithResource<typename TTaskConfig::Resource::Stack>>;
		};

	public:
		using PerStack = TupleProjection<typename TaskConfigsFrom<TConfig>::PerConfig, StackConfigFromTaskConfig>::Output;
		// TODO: We need a PerTask, too.  This will allow us to build up a list of Task Control Blocks.  This is true of most (all ?) task-based
		// resources - we need a PerResource for instantiation purposes and a PerTask for referencing those resource instances based on a task ID
	};
}

#endif
