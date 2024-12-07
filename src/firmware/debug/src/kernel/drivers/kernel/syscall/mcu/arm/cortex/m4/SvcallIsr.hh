#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SVCALLISR_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SVCALLISR_HH
#include <cstdint>

#include "kernel/config/IHaveTupleOfKernelConfigs.hh"

#include "../../../../PortableSyscallIsr.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4
{
	using namespace smeg::kernel::config;

	template <IHaveTupleOfKernelConfigs TKernelConfigs>
	class SvcallIsr
	{
	public:
		static void onInterrupt(void) noexcept
		{
			register void *argsPtr asm("r0");
			register std::uint32_t id asm("r1");
			PortableSyscallIsr<TKernelConfigs>::onInterrupt(argsPtr, id);
		}
	};
}

#endif
