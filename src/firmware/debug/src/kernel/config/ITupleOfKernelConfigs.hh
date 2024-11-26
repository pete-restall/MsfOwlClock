#ifndef __SMEG_KERNEL_CONFIG_ITUPLEOFKERNELCONFIGS_HH
#define __SMEG_KERNEL_CONFIG_ITUPLEOFKERNELCONFIGS_HH
#include <tuple>

#include "IKernelConfig.hh"

namespace smeg::kernel::config
{
	template <typename T>
	struct _$IsTupleOfKernelConfigs
	{
		static constexpr bool value = false;
	};

	template <IKernelConfig... T>
	struct _$IsTupleOfKernelConfigs<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept ITupleOfKernelConfigs = _$IsTupleOfKernelConfigs<T>::value;
}

#endif
