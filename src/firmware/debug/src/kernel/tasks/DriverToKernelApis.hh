#ifndef __SMEG_KERNEL_TASKS_DRIVERTOKERNELAPIS_HH
#define __SMEG_KERNEL_TASKS_DRIVERTOKERNELAPIS_HH
#include "IDriverToKernelApi.hh"

namespace smeg::kernel::tasks
{
	template <IDriverToKernelApi... TApis>
	class DriverToKernelApis
	{
	};
}

#endif
