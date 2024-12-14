#ifndef __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLISR_HH
#define __SMEG_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLISR_HH
#include <array>
#include <cstdint>
#include <utility>

#include "kernel/IMcuCoreTraits.hh"

namespace smeg::kernel::drivers::kernel::syscall
{
	using namespace smeg::kernel;

	template <IMcuCoreTraits TMcuCoreTraits, template <auto> typename TPerCoreIsrFactory>
	class PortableSyscallIsr
	{
	private:
		using McuCoreIds = std::make_index_sequence<TMcuCoreTraits::numberOfMcuCores>;

		template <auto... McuCoreIds>
		static auto createIsrForEachMcuCoreUsingFactory(std::index_sequence<McuCoreIds...>) noexcept
		{
			static_assert(
				noexcept(std::array{TPerCoreIsrFactory<McuCoreIds>::createPortableSyscallPerCoreIsr() ...}),
				"ISR factories must not throw exceptions because they are used to initialise global variables");

			return std::array{TPerCoreIsrFactory<McuCoreIds>::createPortableSyscallPerCoreIsr() ...};
		}

		[[gnu::section(".bss.isrs.syscalls.per_core")]]
		static inline std::array perCoreIsrs{createIsrForEachMcuCoreUsingFactory(McuCoreIds())};

	public:
		static void onInterrupt(void *argsPtr, std::uint32_t id) noexcept
		{
			perCoreIsrs[TMcuCoreTraits::getMcuCoreId()].onInterrupt(argsPtr, id);
		}
	};
}

#endif
