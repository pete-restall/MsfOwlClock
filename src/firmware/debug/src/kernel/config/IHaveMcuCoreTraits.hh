#ifndef __SMEG_KERNEL_CONFIG_IHAVEMCUCORETRAITS_HH
#define __SMEG_KERNEL_CONFIG_IHAVEMCUCORETRAITS_HH
#include "../IMcuCoreTraits.hh"

namespace smeg::kernel::config
{
	template <typename T>
	concept IHaveMcuCoreTraits = IMcuCoreTraits<typename T::McuCoreTraits>;
}

#endif
