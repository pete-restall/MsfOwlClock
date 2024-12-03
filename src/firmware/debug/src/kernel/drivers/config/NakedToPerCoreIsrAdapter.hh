#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_NAKEDTOPERCODEISRADAPTER_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_NAKEDTOPERCODEISRADAPTER_HH
#include <array>
#include <cstddef>
#include <utility>

#include "../../IMcuCoreTraits.hh"
#include "IProvidedIsrConfig.hh"

namespace smeg::kernel::drivers::config
{
	template <typename T, typename TIsrConfig>
	concept _$IHavePerCoreIsrFactory = requires
	{
		{ T::template Factory<TIsrConfig, 0>::createPerCoreIsr() } noexcept -> std::same_as<typename T::Handler>;
	};

	template <IMcuCoreTraits TMcuCoreTraits, IProvidedIsrConfig TIsrConfig, template <typename, auto> typename TPerCoreIsrFactory>
	class NakedToPerCoreIsrAdapter
	{
	private:
		using McuCoreIds = std::make_index_sequence<TMcuCoreTraits::numberOfMcuCores>;

		template <typename T, auto... McuCoreIds>
		static auto createIsrForEachMcuCoreUsingFactory(std::index_sequence<McuCoreIds...>)
		{
			return std::array{TPerCoreIsrFactory<TIsrConfig, McuCoreIds>::createPerCoreIsr() ...};
		}

		template <_$IHavePerCoreIsrFactory<TIsrConfig> T, auto... McuCoreIds>
		static auto createIsrForEachMcuCoreUsingFactory(std::index_sequence<McuCoreIds...>)
		{
			return std::array{TIsrConfig::template Factory<TIsrConfig, McuCoreIds>::createPerCoreIsr() ...};
		}

		static auto initialiser(void)
		{
			return createIsrForEachMcuCoreUsingFactory<TIsrConfig>(McuCoreIds());
		}

		static std::array<typename TIsrConfig::Handler, TMcuCoreTraits::numberOfMcuCores> perCoreIsrs;

	public:
		static void onInterrupt(void) noexcept
		{
			// TODO: potential for out-of-bounds if an incorrect TMcuCoreTraits implementation is given.  But what can we possibly do here even if we
			// handled something that should not occur in a functioning / non-corrupted application, other than std::terminate() or something similar ?
			perCoreIsrs[TMcuCoreTraits::getMcuCoreId()].onInterrupt();
		}
	};

	template <IMcuCoreTraits TMcuCoreTraits, IProvidedIsrConfig TIsrConfig, template <typename, auto> typename TPerCoreIsrFactory>
	[[gnu::section(".bss.isrs.per_core")]]
	std::array<typename TIsrConfig::Handler, TMcuCoreTraits::numberOfMcuCores> NakedToPerCoreIsrAdapter<TMcuCoreTraits, TIsrConfig, TPerCoreIsrFactory>::perCoreIsrs(
		NakedToPerCoreIsrAdapter<TMcuCoreTraits, TIsrConfig, TPerCoreIsrFactory>::initialiser());
}

#endif
