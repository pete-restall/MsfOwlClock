#ifndef __SMEG_TESTS_UNIT_KERNEL_FINALISABLETESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_FINALISABLETESTDOUBLES_HH
#include <atomic>
#include <memory>

#include "../CallRecorder.hh"
#include "MockConstFinalisable.hh"
#include "MockNonConstFinalisable.hh"

namespace smeg::tests::unit::kernel
{
	class FinalisableTestDoubles
	{
private:
		typedef CallRecorder<> FinaliseCallRecorder;
		typedef FinaliseCallRecorder::CallCountInt CallCountInt;
		std::atomic<CallCountInt> &callSequence;

		typedef std::shared_ptr<FinaliseCallRecorder> FinaliseCallRecorderPtr;

public:
		FinalisableTestDoubles(std::atomic<CallCountInt> &callSequenceCounter) :
			callSequence(callSequenceCounter)
		{
		}

		MockNonConstFinalisable mockNonConst(void)
		{
			auto callRecorder = std::make_shared<FinaliseCallRecorder>(this->callSequence);
			return MockNonConstFinalisable(callRecorder);
		}

		MockConstFinalisable mockConst(void)
		{
			auto callRecorder = std::make_shared<FinaliseCallRecorder>(this->callSequence);
			return MockConstFinalisable(callRecorder);
		}
	};
}

#endif
