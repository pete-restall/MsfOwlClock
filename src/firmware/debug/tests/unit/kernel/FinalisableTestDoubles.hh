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
		using FinaliseCallRecorder = CallRecorder<>;
		using CallCountInt = FinaliseCallRecorder::CallCountInt;
		std::atomic<CallCountInt> &callSequence;

	public:
		FinalisableTestDoubles(std::atomic<CallCountInt> &callSequenceCounter) :
			callSequence(callSequenceCounter)
		{
		}

		auto mockNonConst(void)
		{
			auto callRecorder = std::make_shared<FinaliseCallRecorder>(this->callSequence);
			return MockNonConstFinalisable(callRecorder);
		}

		auto mockConst(void)
		{
			auto callRecorder = std::make_shared<FinaliseCallRecorder>(this->callSequence);
			return MockConstFinalisable(callRecorder);
		}

		auto dummy(void) const
		{
			struct Dummy
			{
				void finalise(void) const
				{
				}
			};

			return Dummy();
		}
	};
}

#endif
