#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKSFROM_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKSFROM_HH
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
	class TaskStacksFrom
	{
	private:
		template <typename TTaskConfig>
		struct StackConfigFromTaskConfig
		{
			using AsTuple = std::tuple<typename TTaskConfig::WithResource<typename TTaskConfig::ResourceType::Stack>>;
		};

	public:
		using PerStack = TupleProjection<typename TaskConfigsFrom<TConfig>::PerConfig, StackConfigFromTaskConfig>::Output;
	};
}

#endif
