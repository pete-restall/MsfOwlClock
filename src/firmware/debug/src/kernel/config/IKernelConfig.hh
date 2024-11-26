#ifndef __SMEG_KERNEL_CONFIG_IKERNELCONFIG_HH
#define __SMEG_KERNEL_CONFIG_IKERNELCONFIG_HH
#include <tuple>

namespace smeg::kernel::config
{
	template <typename... T>
	struct _$IsTuple
	{
		static constexpr bool value = false;
	};

	template <typename... T>
	struct _$IsTuple<std::tuple<T...>>
	{
		static constexpr bool value = true;
	};

	// TODO !  Needs refining, once we determine what a suitable common / required / minimal kernel configuration looks like.  Probably requires
	// the other concepts like IHaveTasks, IHaveDrivers, etc. but that would involve moving this concept higher into the tree.  Think about it...
	template <typename T>
	concept IKernelConfig =
		_$IsTuple<typename T::RequiredDrivers>::value ||
		_$IsTuple<typename T::Drivers>::value ||
		_$IsTuple<typename T::Tasks>::value;
}

#endif
