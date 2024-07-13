#ifndef __SMEG_TESTS_UNIT_KERNEL_MOCKNONCONSTINITIALISABLE_HH
#define __SMEG_TESTS_UNIT_KERNEL_MOCKNONCONSTINITIALISABLE_HH
#include <memory>
#include "../CallRecorder.hh"

namespace smeg::tests::unit::kernel
{
	class MockNonConstInitialisable
	{
	private:
		std::shared_ptr<CallRecorder<>> initialiseCalls;

	public:
		MockNonConstInitialisable(std::shared_ptr<CallRecorder<>> initialiseCallRecorder) :
			initialiseCalls(initialiseCallRecorder)
		{
		}

		void initialise(void) { this->initialiseCalls->calledWith(); }
		const CallRecorder<> &callsToNonConstInitialise(void) const { return *this->initialiseCalls; }
	};
}

#endif
