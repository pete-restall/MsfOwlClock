#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_ISRS_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_ISRS_HH
#include "../../../../../../drivers/DefaultPerCoreIsrFactory.hh"
#include "../../../../../../drivers/IIsr.hh"
#include "../../../../../../drivers/config/IProvidedIsrConfig.hh"
#include "../../../../../../drivers/config/ITupleOfProvidedIsrConfigs.hh"
#include "../../../../../../drivers/config/IsrOrDefaultByIrqFrom.hh"
#include "../../../../../../drivers/config/IsrWithDefaultTrampoline.hh"
#include "../../../../../../drivers/config/ProvidedIsrConfigsFrom.hh"
#include "../../../../../../drivers/config/RequiredDriverConfigsFrom.hh"
#include "../../../../KernelConfigs.hh"
#include "../../../../McuCoreTraits.hh"
#include "NakedToPerCoreIsrTrampoline.hh"

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	using namespace smeg::kernel::drivers::config;

	using IsrVector = void (*const)(void) noexcept;

	template <IProvidedIsrConfig TConfig, auto McuCoreId>
	using PerCoreIsrFactory = DefaultPerCoreIsrFactory<TConfig, McuCoreId, DefaultApiFactory>;

	template <IProvidedIsrConfig TIsrConfig>
	using NakedToPerCoreIsrTrampolineWithMcuCoreTraits = NakedToPerCoreIsrTrampoline<McuCoreTraits, TIsrConfig, PerCoreIsrFactory>;

	template <ITupleOfProvidedIsrConfigs TIsrConfigs, auto Irq, IIsr TDefaultIsr>
	using IsrConfigOrDefaultByIrqFrom = IsrOrDefaultByIrqFrom<TIsrConfigs, Irq, TDefaultIsr>::Config;

	using RequiredDriverConfigs = RequiredDriverConfigsFrom<KernelConfigs>::PerConfig;
	using IsrConfigs = ProvidedIsrConfigsFrom<RequiredDriverConfigs>::PerConfig;

	template <auto Irq, IIsr TDefaultIsr>
	using IsrOrDefaultByIrq =
		IsrWithDefaultTrampoline<NakedToPerCoreIsrTrampolineWithMcuCoreTraits>
		::ForConfig<IsrConfigOrDefaultByIrqFrom<IsrConfigs, Irq, TDefaultIsr>>;
}

#endif
