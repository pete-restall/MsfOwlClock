#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_NAKEDTOPERCOREISRTRAMPOLINE_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_NAKEDTOPERCOREISRTRAMPOLINE_HH
#include <cstddef>

#include "../../../../../../IMcuCoreTraits.hh"
#include "../../../../../../drivers/IIsr.hh"
#include "../../../../../../drivers/config/IProvidedIsrConfig.hh"
#include "../../../../../../drivers/config/NakedToPerCoreIsrAdapter.hh"

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	using namespace smeg::kernel::drivers;
	using namespace smeg::kernel::drivers::config;

	template <IMcuCoreTraits TMcuCoreTraits, IProvidedIsrConfig TIsrConfig, template </*IProvidedIsrConfig*/typename, /*std::size_t*/auto> typename TPerCoreIsrFactory>
	class NakedToPerCoreIsrTrampoline
	{
	public:
		[[gnu::interrupt, general_regs_only]]
		static void onInterrupt(void) noexcept
		{
			NakedToPerCoreIsrAdapter<TMcuCoreTraits, TIsrConfig, TPerCoreIsrFactory>::onInterrupt();
		}
	};
}

#endif
