#ifndef __SMEG_KERNEL_TASKS_TASKLIFECYCLE_HH
#define __SMEG_KERNEL_TASKS_TASKLIFECYCLE_HH
#include <concepts>
#include "../Exception.hh"
#include "IHandleAbnormalTaskExits.hh"
#include "ITask.hh"

namespace smeg::kernel::tasks
{
	template <typename TTaskFactory, IHandleAbnormalTaskExits TAbnormalExitHandler>
	class TaskLifecycle
	{
	private:
		TAbnormalExitHandler &abnormalExitHandler;

	public:
		TaskLifecycle(TAbnormalExitHandler &abnormalExitHandler) noexcept :
			abnormalExitHandler(abnormalExitHandler)
		{
		}

		void run(void) noexcept
		{
			try
			{
				auto task(TTaskFactory::createTask());
				task.run();
			}
			catch (const Exception &exception)
			{
				abnormalExitHandler.onException(exception);
			}
			catch (const std::exception &exception)
			{
				abnormalExitHandler.onException(exception);
			}
			catch (...)
			{
				abnormalExitHandler.onUnknownException();
			}
			// the stack pointer must already be set to the top of the task's stack when this method is entered...
			// the link register must already be set when this method is entered...
			// the CPU must be executing in unprivileged mode when this method is entered...

			// inside try...catch, we'll need to TTask((TKernelApi())).run();
			// after the run(), we'll loop (ie. immediately restart the task); the task can terminate or yield by using the kernelApi passed to it
			// in the catch(uint32_t), we'll need to call 'abnormalExitHandler.onException(uint32_t) noexcept', which will return 'true' to restart the task, 'false' to return
			// in the catch(std::exception), we'll need to call 'abnormalExitHandler.onException(std::exception) noexcept', which will return 'true' to restart the task, 'false' to return
			// in the catch(...), we'll need to call 'abnormalExitHandler.onUnknownException() noexcept', which will return 'true' to restart the task, 'false' to return
		}
	};
}

#endif
