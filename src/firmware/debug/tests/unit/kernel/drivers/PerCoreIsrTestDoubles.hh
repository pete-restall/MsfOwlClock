#ifndef __SMEG_TESTS_UNIT_KERNEL_DRIVERS_PERCOREISRTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_DRIVERS_PERCOREISRTESTDOUBLES_HH
#include <atomic>
#include <memory>
#include <type_traits>

#include "../../CallRecorder.hh"
#include "MockPerCoreIsr.hh"

namespace smeg::tests::unit::kernel::drivers
{
	class PerCoreIsrTestDoubles
	{
	private:
		using OnInterruptCallRecorder = CallRecorder<>;
		using CallCountInt = OnInterruptCallRecorder::CallCountInt;
		std::atomic<CallCountInt> &callSequence;

	public:
		PerCoreIsrTestDoubles(std::atomic<CallCountInt> &callSequenceCounter) :
			callSequence(callSequenceCounter)
		{
		}

		auto mock(void)
		{
			auto callRecorder = std::make_shared<OnInterruptCallRecorder>(this->callSequence);
			return MockPerCoreIsr(callRecorder);
		}
	};

	struct StubPerCoreIsrWithDefaultConstructor
	{
		void onInterrupt(void) noexcept
		{
		}
	};

	template <typename TRequiredApis>
	struct StubPerCoreIsrWithRequiredApisConstructor
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		StubPerCoreIsrWithRequiredApisConstructor(RequiredApis &&) noexcept
		{
		}

		void onInterrupt(void) noexcept
		{
		}
	};
}

#endif
