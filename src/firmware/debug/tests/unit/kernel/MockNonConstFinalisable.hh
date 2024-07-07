#ifndef __SMEG_TESTS_UNIT_KERNEL_MOCKNONCONSTFINALISABLE_HH
#define __SMEG_TESTS_UNIT_KERNEL_MOCKNONCONSTFINALISABLE_HH
#include <memory>
#include "../CallRecorder.hh"

namespace smeg::tests::unit::kernel
{
	class MockNonConstFinalisable
	{
private:
		std::shared_ptr<CallRecorder<>> finaliseCalls;

public:
		MockNonConstFinalisable(std::shared_ptr<CallRecorder<>> finaliseCallRecorder) :
			finaliseCalls(finaliseCallRecorder)
		{
		}

		void finalise(void) { this->finaliseCalls->calledWith(); }
		const CallRecorder<> &callsToNonConstFinalise(void) const { return *this->finaliseCalls; }
	};
}

#endif
