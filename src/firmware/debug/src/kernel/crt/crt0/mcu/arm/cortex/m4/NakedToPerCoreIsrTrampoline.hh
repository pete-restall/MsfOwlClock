#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_NAKEDTOPERCOREISRTRAMPOLINE_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_NAKEDTOPERCOREISRTRAMPOLINE_HH
#include <cstddef>

#include "../../../../../../IMcuCoreTraits.hh"
#include "../../../../../../drivers/IIsr.hh"
#include "../../../../../../drivers/config/IProvidedIsrConfig.hh"
#include "../../../../../../drivers/config/composition/NakedToPerCoreIsrAdapter.hh"

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	using namespace smeg::kernel::drivers;
	using namespace smeg::kernel::drivers::config;
	using namespace smeg::kernel::drivers::config::composition;

	template <IMcuCoreTraits TMcuCoreTraits, IProvidedIsrConfig TIsrConfig, template <IProvidedIsrConfig, std::size_t> typename TPerCoreIsrFactory>
	class NakedToPerCoreIsrTrampoline
	{
	public:
		[[gnu::general_regs_only]] // TODO: general_regs_only doesn't seem to work; GCC bug ?  Manual says the attribute is 'general-regs-only', but that is not syntactically valid for a C++ attribute.  Use the old-style attribute for this instead ?
		static void onInterrupt(void) noexcept
		{
			NakedToPerCoreIsrAdapter<TMcuCoreTraits, TIsrConfig, TPerCoreIsrFactory>::onInterrupt();
		}
	};
}

#endif
