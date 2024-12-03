#ifndef __SMEG_KERNEL_DRIVERS_DEFAULTPERCOREISRFACTORY_HH
#define __SMEG_KERNEL_DRIVERS_DEFAULTPERCOREISRFACTORY_HH
#include <cstddef>
#include <tuple>

#include "../DefaultApiFactory.hh"
#include "IIsr.hh"
#include "config/IProvidedIsrConfig.hh" // TODO: WRONG DIRECTION...

namespace smeg::kernel::drivers
{
	using namespace smeg::kernel::drivers::config; // TODO: SHOULDN'T BE REQUIRED ONCE DEPENDENCY DIRECTION IS FIXED
// TODO: THE FACTORY REALLY NEEDS TO TAKE CONFIG...WHICH MEANS WE ALSO NEED TO MODIFY THE LOCATION OF THIS, TO AVOID POINTING INTO 'config'.
// TODO: THE API FACTORY ALSO OUGHT TO TAKE THE CONFIG, SO THAT IT CAN EXAMINE IT IF IT NEEDS TO.
	template <IProvidedIsrConfig TIsrConfig, std::size_t McuCoreId, template <typename, typename...> typename TApiFactory = DefaultApiFactory>
	class DefaultPerCoreIsrFactory
	{
	private:
		template <typename... TApis>
		struct ApiFactory;

		template <typename... TApis>
		struct ApiFactory<std::tuple<TApis...>>
		{
			using Type = TApiFactory<TIsrConfig, TApis...>;
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
