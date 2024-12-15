#ifndef __SMEG_KERNEL_TASKS_DEFAULTTASKFACTORY_HH
#define __SMEG_KERNEL_TASKS_DEFAULTTASKFACTORY_HH
#include <tuple>

#include "../IHaveRequiredApis.hh"
#include "ITask.hh"

namespace smeg::kernel::tasks
{
	template <ITask TTask, template <typename, typename...> typename TApiFactory>
	class DefaultTaskFactory
	{
	private:
		template <typename... TApis>
		struct ApiFactory;

		template <typename... TApis>
		struct ApiFactory<std::tuple<TApis...>>
		{
			using Type = TApiFactory</* TODO: Wants to be TTaskConfig, when that is added to the DefaultTaskFactory signature */TTask, TApis...>;
		};

	public:
		static constexpr TTask createTask(void)
		{
			// TODO: if TTaskConfig::Factory, then return TTaskConfig::Factory<TTaskConfig, TApiFactory>::createTask()
			if constexpr (IHaveAnyRequiredApis<TTask>)
			{
				using RequiredApis = TTask::RequiredApis;
				using TupleOfApis = RequiredApis::AsTuple;
				return TTask(RequiredApis(typename ApiFactory<TupleOfApis>::Type()));
			}
			else
				return TTask();
		}
	};
}

#endif
