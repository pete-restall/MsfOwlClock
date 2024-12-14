#ifndef __SMEG_KERNEL_DRIVERS_COMPOSITION_DEFAULTPERCOREISRFACTORY_HH
#define __SMEG_KERNEL_DRIVERS_COMPOSITION_DEFAULTPERCOREISRFACTORY_HH
#include <cstddef>
#include <tuple>

#include "../../../DefaultPerCoreApiFactory.hh"
#include "../../IIsr.hh"
#include "../../IIsrApi.hh"
#include "../IProvidedIsrConfig.hh"

namespace smeg::kernel::drivers::config::composition
{
	template <
		IProvidedIsrConfig TIsrConfig,
		std::size_t McuCoreId,
		template <IProvidedIsrConfig, std::size_t, IIsrApi...> typename TApiFactory = DefaultPerCoreApiFactory>
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
		static auto createPerCoreIsr(void) noexcept
		{
			using Isr = TIsrConfig::Handler;
			if constexpr (IPerCoreIsrWithRequiredApis<Isr>)
			{
				using RequiredApis = Isr::RequiredApis;
				using TupleOfApis = RequiredApis::AsTuple;
				static_assert(
					noexcept(Isr(RequiredApis(typename ApiFactory<TupleOfApis>::Type()))),
					"ISR constructors must not throw exceptions because they are used to initialise global variables");

				return Isr(RequiredApis(typename ApiFactory<TupleOfApis>::Type()));
			}
			else
			{
				static_assert(noexcept(Isr()), "ISR constructors must not throw exceptions because they are used to initialise global variables");
				return Isr();
			}
		}
	};
}

#endif
