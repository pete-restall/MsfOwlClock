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

	public:
		InitialisableTestDoubles(std::atomic<CallCountInt> &callSequenceCounter) :
			callSequence(callSequenceCounter)
		{
		}

		auto mockNonConst(void)
		{
			auto callRecorder = std::make_shared<InitialiseCallRecorder>(this->callSequence);
			return MockNonConstInitialisable(callRecorder);
		}

		auto mockConst(void)
		{
			auto callRecorder = std::make_shared<InitialiseCallRecorder>(this->callSequence);
			return MockConstInitialisable(callRecorder);
		}

		auto dummy(void) const
		{
			struct Dummy
			{
				void initialise(void) const
				{
				}
			};

			return Dummy();
		}
	};
}

#endif
