#ifndef __SMEG_KERNEL_TASKS_DEFAULTIDLETASK_HH
#define __SMEG_KERNEL_TASKS_DEFAULTIDLETASK_HH
#include "ITask.hh"

namespace smeg::kernel::tasks
{
	class DefaultIdleTask
	{
	public:
		[[noreturn]]
		void run(void) noexcept
		{
			while (true)
				;;

			__builtin_unreachable();
		}
	};

	static_assert(IRunVoidTask<DefaultIdleTask>, "DefaultIdleTask does not match the IRunVoidTask concept");
}

#endif
