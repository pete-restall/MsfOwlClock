#ifndef __SMEG_KERNEL_TASKS_DRIVERTODRIVERAPIS_HH
#define __SMEG_KERNEL_TASKS_DRIVERTODRIVERAPIS_HH
#include "IDriverToDriverApi.hh"

namespace smeg::kernel::tasks
{
	template <IDriverToDriverApi... TApis>
	class DriverToDriverApis
	{
	};
}

#endif
