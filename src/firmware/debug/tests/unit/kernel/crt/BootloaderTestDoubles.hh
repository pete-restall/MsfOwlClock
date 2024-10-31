#ifndef __SMEG_TESTS_UNIT_KERNEL_CRT_BOOTLOADERTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_CRT_BOOTLOADERTESTDOUBLES_HH
#include <atomic>
#include <memory>

#include "kernel/crt/NoBootloader.hh"

#include "BootloaderSubstitute.hh"

namespace smeg::tests::unit::kernel::crt
{
	using namespace smeg::kernel::crt;

	class BootloaderTestDoubles
	{
	private:
		using OnPreEntrypointCallRecorder = CallRecorder<>;
		using OnPostEntrypointCallRecorder = CallRecorder<>;

		using CallCountInt = OnPreEntrypointCallRecorder::CallCountInt;
		std::atomic<CallCountInt> &callSequence;

	public:
		BootloaderTestDoubles(std::atomic<CallCountInt> &callSequenceCounter) :
			callSequence(callSequenceCounter)
		{
		}

		auto mock(void) const
		{
			return BootloaderSubstitute(
				std::make_shared<OnPreEntrypointCallRecorder>(this->callSequence),
				std::make_shared<OnPostEntrypointCallRecorder>(this->callSequence));
		}

		auto dummy(void) const
		{
			return NoBootloader();
		}
	};
}

#endif
