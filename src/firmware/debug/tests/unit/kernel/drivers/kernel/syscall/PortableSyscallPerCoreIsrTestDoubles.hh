#ifndef __SMEG_TESTS_UNIT_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISRTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_DRIVERS_KERNEL_SYSCALL_PORTABLESYSCALLPERCOREISRTESTDOUBLES_HH
#include <atomic>
#include <cstdint>
#include <memory>
#include <type_traits>

#include "../../../../CallRecorder.hh"
#include "MockPortableSyscallPerCoreIsr.hh"

namespace smeg::tests::unit::kernel::drivers::kernel::syscall
{
	class PortableSyscallPerCoreIsrTestDoubles
	{
	private:
		using OnInterruptCallRecorder = CallRecorder<void *, std::uint32_t>;
		using CallCountInt = OnInterruptCallRecorder::CallCountInt;
		std::atomic<CallCountInt> &callSequence;

	public:
		PortableSyscallPerCoreIsrTestDoubles(std::atomic<CallCountInt> &callSequenceCounter) :
			callSequence(callSequenceCounter)
		{
		}

		auto mock(void)
		{
			auto callRecorder = std::make_shared<OnInterruptCallRecorder>(this->callSequence);
			return MockPortableSyscallPerCoreIsr(callRecorder);
		}
	};

	struct StubPortableSyscallPerCoreIsrWithDefaultConstructor
	{
		void onInterrupt(void *, std::uint32_t) noexcept
		{
		}
	};

	template <typename TRequiredApis>
	struct StubPortableSyscallPerCoreIsrWithRequiredApisConstructor
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		StubPortableSyscallPerCoreIsrWithRequiredApisConstructor(RequiredApis &&) noexcept
		{
		}

		void onInterrupt(void *, std::uint32_t) noexcept
		{
		}
	};
}

#endif
