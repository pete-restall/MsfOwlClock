#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SYSCALLPRIMITIVE_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_MCU_ARM_CORTEX_M4_SYSCALLPRIMITIVE_HH
#include <cstdint>
#include <type_traits>

#include "kernel/ISyscall.hh"

namespace smeg::kernel::drivers::kernel::syscall::mcu::arm::cortex::m4
{
	template <template <typename> typename TSyscallFor>
	class SyscallPrimitive
	{
	public:
		template <ISyscall<TSyscallFor> T>
		[[gnu::always_inline]]
		static inline constexpr void invoke(T &arg) noexcept
		{
			register T *r0 asm("r0") = &arg;
			register std::uint32_t r7 asm("r7") = TSyscallFor<std::remove_cv_t<T>>::id;
			__asm__ volatile("svc #0x00"
				: /* no outputs */
				: /* inputs */
					"syscallId" "r" (r7),
					"syscallArg" "r" (r0)
				: /* clobbers */
					"cc",
					"memory");
		}
	};
}

#endif
