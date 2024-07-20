#ifndef __SMEG_TESTS_UNIT_KERNEL_INITIALISABLETESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_INITIALISABLETESTDOUBLES_HH
#include <atomic>
#include <memory>

#include "../CallRecorder.hh"
#include "MockConstInitialisable.hh"
#include "MockNonConstInitialisable.hh"

namespace smeg::tests::unit::kernel
{
	class InitialisableTestDoubles
	{
	private:
		using InitialiseCallRecorder = CallRecorder<>;
		using CallCountInt = InitialiseCallRecorder::CallCountInt;
		std::atomic<CallCountInt> &callSequence;

		using InitialiseCallRecorderPtr = std::shared_ptr<InitialiseCallRecorder>;

	public:
		InitialisableTestDoubles(std::atomic<CallCountInt> &callSequenceCounter) :
			callSequence(callSequenceCounter)
		{
		}

		MockNonConstInitialisable mockNonConst(void)
		{
			auto callRecorder = std::make_shared<InitialiseCallRecorder>(this->callSequence);
			return MockNonConstInitialisable(callRecorder);
		}

		MockConstInitialisable mockConst(void)
		{
			auto callRecorder = std::make_shared<InitialiseCallRecorder>(this->callSequence);
			return MockConstInitialisable(callRecorder);
		}
	};
}

#endif
