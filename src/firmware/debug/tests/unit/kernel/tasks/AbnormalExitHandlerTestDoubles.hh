#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_ABNORMALEXITHANDLERTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_ABNORMALEXITHANDLERTESTDOUBLES_HH
#include <atomic>
#include <memory>
#include <string>

#include "kernel/Exception.hh"

#include "../../CallRecorder.hh"
#include "AbnormalExitHandlerSubstitute.hh"

namespace smeg::tests::unit::kernel::tasks
{
	using namespace smeg::kernel;

	class AbnormalExitHandlerTestDoubles
	{
	private:
		using OnExceptionSmegExceptionOverloadCallRecorder = CallRecorder<const std::string>;
		using OnExceptionStandardExceptionOverloadCallRecorder = CallRecorder<const std::string>;
		using OnUnknownExceptionCallRecorder = CallRecorder<>;

		using CallCountInt = OnUnknownExceptionCallRecorder::CallCountInt;
		std::atomic<CallCountInt> &callSequence;

	public:
		AbnormalExitHandlerTestDoubles(std::atomic<CallCountInt> &callSequenceCounter) :
			callSequence(callSequenceCounter)
		{
		}

		AbnormalExitHandlerSubstitute mock(void)
		{
			auto onExceptionSmegExceptionOverloadCallRecorder = std::make_shared<OnExceptionSmegExceptionOverloadCallRecorder>(this->callSequence);
			auto onExceptionStandardExceptionOverloadCallRecorder = std::make_shared<OnExceptionStandardExceptionOverloadCallRecorder>(this->callSequence);
			auto onUnknownExceptionCallRecorder = std::make_shared<OnUnknownExceptionCallRecorder>(this->callSequence);
			return AbnormalExitHandlerSubstitute(
				onExceptionSmegExceptionOverloadCallRecorder,
				onExceptionStandardExceptionOverloadCallRecorder,
				onUnknownExceptionCallRecorder);
		}
	};
}

#endif
