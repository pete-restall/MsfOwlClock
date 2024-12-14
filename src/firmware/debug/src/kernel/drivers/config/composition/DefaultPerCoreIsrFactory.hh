#ifndef __SMEG_KERNEL_DRIVERS_COMPOSITION_DEFAULTPERCOREISRFACTORY_HH
#define __SMEG_KERNEL_DRIVERS_COMPOSITION_DEFAULTPERCOREISRFACTORY_HH
#include <cstddef>
#include <tuple>

#include "../../../DefaultPerCoreApiFactory.hh"
#include "../../IIsr.hh"
#include "../IProvidedIsrConfig.hh"

namespace smeg::kernel::drivers::config::composition
{
	template <
		IProvidedIsrConfig TIsrConfig,
		std::size_t McuCoreId,
		template <IProvidedIsrConfig, std::size_t, typename...> typename TApiFactory = DefaultPerCoreApiFactory>
	class DefaultPerCoreIsrFactory
	{
	private:
		template <typename... TApis>
		struct ApiFactory;

		template <typename... TApis>
		struct ApiFactory<std::tuple<TApis...>>
		{
			using Type = TApiFactory<TIsrConfig, McuCoreId, TApis...>;
		};

	public:
		static auto createPerCoreIsr(void) noexcept // TODO: THIS OUGHT TO BE DETERMINED BASED ON ALL OF THE noexcepts OF THE APIs...
		{
			using Isr = TIsrConfig::Handler;
			if constexpr (IPerCoreIsrWithRequiredApis<Isr>)
			{
				using RequiredApis = Isr::RequiredApis;
				using TupleOfApis = RequiredApis::AsTuple;
				return Isr((RequiredApis(typename ApiFactory<TupleOfApis>::Type())));
			}
			else
				return Isr();
		}
	};
}

#endif
