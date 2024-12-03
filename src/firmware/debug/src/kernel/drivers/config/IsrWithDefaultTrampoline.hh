#ifndef __SMEG_KERNEL_DRIVERS_CONFIG_ISRWITHDEFAULTTRAMPOLINE_HH
#define __SMEG_KERNEL_DRIVERS_CONFIG_ISRWITHDEFAULTTRAMPOLINE_HH
#include "../IIsr.hh"
#include "IProvidedIsrConfig.hh"

namespace smeg::kernel::drivers::config
{
	template <template <IProvidedIsrConfig> typename TIsrTrampoline>
	class IsrWithDefaultTrampoline
	{
	private:
		template <typename TIsrConfig>
		struct HandlerFrom;

		template <IProvidedNakedIsrConfig TIsrConfig>
		struct HandlerFrom<TIsrConfig>
		{
			using Type = TIsrConfig::Handler;
		};

		template <IProvidedPerCoreIsrConfig TIsrConfig>
		struct HandlerFrom<TIsrConfig>
		{
			using Type = TIsrTrampoline<TIsrConfig>;
		};

	public:
		template <IProvidedIsrConfig TIsrConfig>
		using ForConfig = HandlerFrom<TIsrConfig>::Type;
	};
}

#endif
