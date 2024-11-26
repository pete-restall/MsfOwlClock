#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IDRIVERCONFIG_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IDRIVERCONFIG_HH
#include "../../tasks/config/IHaveConfigForTasks.hh"
#include "IHaveConfigForProvidedApis.hh"
#include "IHaveConfigForProvidedIsrs.hh"
#include "IHaveConfigForProvidedSyscalls.hh"

namespace smeg::kernel::drivers::config
{
	using namespace smeg::kernel::tasks::config;

	template <typename T>
	concept IDriverConfig =
		IHaveConfigForProvidedApis<T> ||
		IHaveConfigForProvidedIsrs<T> ||
		IHaveConfigForProvidedSyscalls<T> ||
		IHaveConfigForTasks<T>;
}

#endif
