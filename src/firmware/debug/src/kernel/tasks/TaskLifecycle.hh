#ifndef __SMEG_KERNEL_TASKS_TASKLIFECYCLE_HH
#define __SMEG_KERNEL_TASKS_TASKLIFECYCLE_HH
#include <concepts>
#include "../Exception.hh"
#include "IHandleAbnormalTaskExits.hh"
#include "ITask.hh"

namespace smeg::kernel::tasks
{
	/*
		TODO: Notes for further implementation:
		The stack pointer must already be set to the top of the task's stack when this method is entered...
		The link register must already be set when this method is entered...
		The CPU must be executing in unprivileged mode when this method is entered...
	*/
	template <typename TTaskFactory, IHandleAbnormalTaskExits TAbnormalExitHandler>
	class TaskLifecycle
	{
	private:
		TAbnormalExitHandler &abnormalExitHandler;

		bool runOnceWithoutCatch(void)
		{
			auto task(TTaskFactory::createTask());
			if constexpr (!IRunBooleanTask<decltype(task)>)
			{
				task.run();
				return true;
			}
			else
				return task.run();
		}

		bool runOnce(void) noexcept
		{
			try
			{
				return this->runOnceWithoutCatch();
			}
			catch (const Exception &exception)
			{
				return abnormalExitHandler.onException(exception);
			}
			catch (const std::exception &exception)
			{
				return abnormalExitHandler.onException(exception);
			}
			catch (...)
			{
				return abnormalExitHandler.onUnknownException();
			}
		}

	public:
		TaskLifecycle(TAbnormalExitHandler &abnormalExitHandler) noexcept :
			abnormalExitHandler(abnormalExitHandler)
		{
		}

		void run(void) noexcept
		{
			while (this->runOnce())
				;;
		}
	};
}

#endif
