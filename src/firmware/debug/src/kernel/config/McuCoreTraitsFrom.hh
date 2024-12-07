#ifndef __SMEG_KERNEL_CONFIG_MCUCORETRAITSFROM_HH
#define __SMEG_KERNEL_CONFIG_MCUCORETRAITSFROM_HH
#include <tuple>

#include "../tuples/TupleProjection.hh"
#include "IHaveMcuCoreTraits.hh"
#include "IHaveTupleOfKernelConfigs.hh"

namespace smeg::kernel::config
{
	using namespace smeg::kernel::tuples;

	template <typename>
	class _$McuCoreTraitsFrom;

	template <typename... TKernelConfigs>
	class _$McuCoreTraitsFrom<std::tuple<TKernelConfigs...>>
	{
	private:
		template <typename>
		struct FilterMcuCoreTraits
		{
			using AsTuple = std::tuple<>;
		};

		template <IHaveMcuCoreTraits TKernelConfig>
		struct FilterMcuCoreTraits<TKernelConfig>
		{
			using AsTuple = std::tuple<typename TKernelConfig::McuCoreTraits>;
		};

		using AsTuple = TupleProjection<std::tuple<TKernelConfigs...>, FilterMcuCoreTraits>::Output;
		static_assert(std::tuple_size_v<AsTuple> != 0, "No McuCoreTraits member matching concept IMcuCoreTraits was found in the given KernelConfigs");
		static_assert(std::tuple_size_v<AsTuple> <= 1, "More than one McuCoreTraits member matching concept IMcuCoreTraits was found in the given KernelConfigs, which is ambiguous");

	public:
		using Type = std::tuple_element_t<0, AsTuple>;
	};

	template <typename TConfig>
	class _$McuCoreTraitsFrom
	{
	public:
		using Type = _$McuCoreTraitsFrom<std::tuple<TConfig>>::Type;
	};

	template <IHaveTupleOfKernelConfigs TConfig>
	class _$McuCoreTraitsFrom<TConfig>
	{
	public:
		using Type = _$McuCoreTraitsFrom<typename TConfig::AsTuple>::Type;
	};

	template <typename TConfig>
	using McuCoreTraitsFrom = _$McuCoreTraitsFrom<TConfig>::Type;
}

#endif
