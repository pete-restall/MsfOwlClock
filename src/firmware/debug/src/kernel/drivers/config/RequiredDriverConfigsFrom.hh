#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_REQUIREDDRIVERCONFIGSFROM_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_REQUIREDDRIVERCONFIGSFROM_HH
#include <tuple>

#include "../../config/IHaveTupleOfKernelConfigs.hh"

namespace smeg::kernel::drivers::config
{
	using namespace smeg::kernel::config;
	using namespace smeg::kernel::tuples;

	// TODO: This needs writing.  Each TKernelConfig may have a RequiredApis.  Using this list of required APIs:
	//   The DriverConfig that provides the API can found.
	//   Any Tasks and Syscalls provided by the DriverConfigs that have constructors that take APIs also need to have their DriverConfigs looked up.
	//   Any TKernelConfig that has Tasks also needs the APIs from those Tasks resolving to DriverConfigs.
	//   Etc.
	// The result should be a unique set of DriverConfigs.  May require a 'MaxDepth' parameter to avoid infinite recursion, but that will come out in the wash.
	template <IHaveTupleOfKernelConfigs TKernelConfigs>
	class RequiredDriverConfigsFrom
	{
	public:
		using PerConfig = TKernelConfigs::AsTuple; //std::tuple<>;
	};
}

#endif
