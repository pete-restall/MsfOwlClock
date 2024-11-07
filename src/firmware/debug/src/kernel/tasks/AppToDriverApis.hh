#ifndef __SMEG_KERNEL_TASKS_APPTODRIVERAPIS_HH
#define __SMEG_KERNEL_TASKS_APPTODRIVERAPIS_HH
#include "IAppToDriverApi.hh"

namespace smeg::kernel::tasks
{
	template <IAppToDriverApi... TApis>
	class AppToDriverApis
	{
	};
}

#endif
