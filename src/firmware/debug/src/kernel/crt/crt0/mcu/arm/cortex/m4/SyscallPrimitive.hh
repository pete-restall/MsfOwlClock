#ifndef __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_SYSCALLPRIMITIVE_HH
#define __SMEG_KERNEL_CRT_CRT0_MCU_ARM_CORTEX_M4_SYSCALLPRIMITIVE_HH
#include <cstdint>
#include <type_traits>
#include "../../../../../../ISyscall.hh"

namespace smeg::kernel::crt::crt0::mcu::arm::cortex::m4
{
	template <template <typename> typename TSyscallFor>
	class SyscallPrimitive
	{
	public:
		template <ISyscallWithConstStructArg<TSyscallFor> T>
		[[gnu::always_inline]]
		static inline constexpr void invoke(const T &arg) noexcept
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

		template <ISyscallWithStructArg<TSyscallFor> T>
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

		template <ISyscallWithIntegerArg<TSyscallFor> T>
		[[gnu::always_inline]]
		static inline constexpr void invoke(const T &arg) noexcept
		{
			register std::uint32_t r0 asm("r0") = arg.getValue();
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

		template <ISyscallWithNoArgs<TSyscallFor> T>
		[[gnu::always_inline]]
		static inline constexpr void invoke(void) noexcept
		{
			register std::uint32_t r7 asm("r7") = TSyscallFor<std::remove_cv_t<T>>::id;
			__asm__ volatile("svc #0x00"
				: /* no outputs */
				: /* inputs */
					"syscallId" "r" (r7)
				: /* clobbers */
					"cc",
					"memory");
		}
	};
}

#endif
