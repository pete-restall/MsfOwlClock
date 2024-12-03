#ifndef __SMEG_TESTS_UNIT_KERNEL_DRIVERS_MOCKPERCOREISR_HH
#define __SMEG_TESTS_UNIT_KERNEL_DRIVERS_MOCKPERCOREISR_HH
#include <memory>
#include <stdexcept>

#include "../../CallRecorder.hh"

namespace smeg::tests::unit::kernel::drivers
{
	class MockPerCoreIsr
	{
	private:
		std::shared_ptr<CallRecorder<>> onInterruptCalls;

	public:
		MockPerCoreIsr(std::shared_ptr<CallRecorder<>> initialiseCallRecorder) :
			onInterruptCalls(initialiseCallRecorder)
		{
		}

		MockPerCoreIsr(void) noexcept :
			onInterruptCalls(nullptr)
		{
		}

		void onInterrupt(void) noexcept
		{
			if (!this->onInterruptCalls)
				return;

			this->onInterruptCalls->calledWith();
		}

		const CallRecorder<> &callsToOnInterrupt(void) const
		{
			this->ensureMockWasConstructedProperly();
			return *this->onInterruptCalls;
		}

	private:
		void ensureMockWasConstructedProperly(void) const
		{
			if (!this->onInterruptCalls)
				throw new std::runtime_error("MockPerCoreIsr was not constructed properly; the default constructor is purely to conform with the IIsr concept");
		}

	public:
		void resetMock(void)
		{
			this->ensureMockWasConstructedProperly();
			this->onInterruptCalls->resetCalls();
		}
	};
}

#endif
