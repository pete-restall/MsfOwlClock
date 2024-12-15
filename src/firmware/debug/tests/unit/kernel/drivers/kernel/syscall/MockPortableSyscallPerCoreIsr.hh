#ifndef __SMEG_TESTS_UNIT_KERNEL_DRIVERS_KERNEL_SYSCALL_MOCKPORTABLESYSCALLPERCOREISR_HH
#define __SMEG_TESTS_UNIT_KERNEL_DRIVERS_KERNEL_SYSCALL_MOCKPORTABLESYSCALLPERCOREISR_HH
#include <cstdint>
#include <memory>

#include "../../../../CallRecorder.hh"

namespace smeg::tests::unit::kernel::drivers::kernel::syscall
{
	class MockPortableSyscallPerCoreIsr
	{
	private:
		std::shared_ptr<CallRecorder<void *, std::uint32_t>> onInterruptCalls;

	public:
		MockPortableSyscallPerCoreIsr(std::shared_ptr<CallRecorder<void *, std::uint32_t>> onInterruptCalls) :
			onInterruptCalls(onInterruptCalls)
		{
		}

		void onInterrupt(void *argPtr, std::uint32_t id) noexcept
		{
			if (!this->onInterruptCalls)
				return;

			this->onInterruptCalls->calledWith(argPtr, id);
		}

		const CallRecorder<void *, std::uint32_t> &callsToOnInterrupt(void) const
		{
			return *this->onInterruptCalls;
		}

		void resetMock(void)
		{
			this->onInterruptCalls->resetCalls();
		}
	};
}

#endif
