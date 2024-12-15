#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SVCALLISR_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SVCALLISR_HH
#include <cstdint>

#include "kernel/config/IHaveTupleOfKernelConfigs.hh"

#include "../../../../PortableSyscallIsr.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4
{
	using namespace smeg::kernel::config;

	template <IMcuCoreTraits TMcuCoreTraits, template <auto> typename TPerCoreIsrFactory>
	class SvcallIsr
	{
	public:
		static void onInterrupt(void) noexcept
		{
			register void *argPtr asm("r0");
			register std::uint32_t id asm("r1");
			PortableSyscallIsr<TMcuCoreTraits, TPerCoreIsrFactory>::onInterrupt(argPtr, id);
		}
	};
}

#endif
