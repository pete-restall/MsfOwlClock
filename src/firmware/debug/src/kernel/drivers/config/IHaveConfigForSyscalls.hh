#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORSYSCALLS_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_IHAVECONFIGFORSYSCALLS_HH
#include <cstddef>
#include <tuple>

#include "IHaveConfigForSyscall.hh"

namespace smeg::kernel::drivers::config
{
	template <typename... T>
	struct _IsTupleOfSyscallConfigs
	{
		static constexpr bool value = false;
	};

	template <IHaveConfigForSyscall... T>
	struct _IsTupleOfSyscallConfigs<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	template <typename T>
	concept IHaveConfigForSyscalls = _IsTupleOfSyscallConfigs<typename T::Syscalls>::value;
}

#endif
