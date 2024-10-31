#ifndef __SMEG_TESTS_UNIT_KERNEL_CRT_BOOTLOADERSUBSTITUTE_HH
#define __SMEG_TESTS_UNIT_KERNEL_CRT_BOOTLOADERSUBSTITUTE_HH
#include <memory>

#include "../../CallRecorder.hh"

namespace smeg::tests::unit::kernel::crt
{
	class BootloaderSubstitute
	{
	private:
		std::shared_ptr<CallRecorder<>> onPreEntrypointCalls;
		std::shared_ptr<CallRecorder<>> onPostEntrypointCalls;

	public:
		BootloaderSubstitute(
			std::shared_ptr<CallRecorder<>> onPreEntrypointCallRecorder,
			std::shared_ptr<CallRecorder<>> onPostEntrypointCallRecorder) :
			onPreEntrypointCalls(onPreEntrypointCallRecorder),
			onPostEntrypointCalls(onPostEntrypointCallRecorder)
		{
		}

		void onPreEntrypoint(void) const noexcept { this->onPreEntrypointCalls->calledWith(); }
		const CallRecorder<> &callsToOnPreEntrypoint(void) const { return *this->onPreEntrypointCalls; }

		void onPostEntrypoint(void) const noexcept { this->onPostEntrypointCalls->calledWith(); }
		const CallRecorder<> &callsToOnPostEntrypoint(void) const { return *this->onPostEntrypointCalls; }
	};
}

#endif
