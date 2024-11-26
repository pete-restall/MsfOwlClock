#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_DRIVERISRCONFIGSFROM_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_DRIVERISRCONFIGSFROM_HH
#include <tuple>

#include "../../config/ITupleOfKernelConfigs.hh"

namespace smeg::kernel::drivers::config
{
	using namespace smeg::kernel::config;

	// TODO: This needs writing.  Each TKernelConfig may have a tuple<IIsrConfig...> called ProvidedIsrs.
	template <ITupleOfKernelConfigs TKernelConfigs>
	class DriverIsrConfigsFrom
	{
	public:
		using PerConfig = std::tuple<>;
	};
}

#endif
