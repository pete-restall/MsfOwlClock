#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_ISRORDEFAULTBYIRQFROM_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_ISRORDEFAULTBYIRQFROM_HH
#include <concepts>
#include <tuple>
#include <type_traits>
#include <utility>

#include "../../tuples/TupleCat.hh"
#include "../../tuples/TupleProjection.hh"
#include "../IIsr.hh"
#include "IProvidedIsrConfig.hh"
#include "ITupleOfProvidedIsrConfigs.hh"

namespace smeg::kernel::drivers::config
{
	using namespace smeg::kernel::tuples;

	template <ITupleOfProvidedIsrConfigs TIsrConfigs, std::integral auto Irq, IIsr TDefaultIsr>
	class IsrOrDefaultByIrqFrom
	{
	private:
		struct DefaultIsrAsConfig
		{
			using Handler = TDefaultIsr;
			static constexpr auto irq = 12345; // TODO: NEEDS A TEST TO MAKE SURE THIS IS SET TO Irq
		};

		template <IProvidedIsrConfig TIsrConfig>
		struct WhereIrqEquals
		{
			using AsTuple = std::conditional_t<TIsrConfig::irq == Irq, std::tuple<TIsrConfig>, std::tuple<>>;
		};

		using MatchingIsrConfigs = TupleProjection<TIsrConfigs, WhereIrqEquals>::Output;
		using MatchingIsrConfigOrDefault = TupleCat<MatchingIsrConfigs, std::tuple<DefaultIsrAsConfig>>;

		static_assert(std::tuple_size_v<MatchingIsrConfigs> <= 1, "Ambiguous configuration; there cannot be more than one ISR that matches any given IRQ");

	public:
		using Config = std::tuple_element_t<0, MatchingIsrConfigOrDefault>;
	};
}

#endif
