#ifndef __SMEG_TESTS_UNIT_KERNEL_MOCKCONSTINITIALISABLE_HH
#define __SMEG_TESTS_UNIT_KERNEL_MOCKCONSTINITIALISABLE_HH
#include <memory>
#include "../CallRecorder.hh"

namespace smeg::tests::unit::kernel
{
	class MockConstInitialisable
	{
	private:
		std::shared_ptr<CallRecorder<>> initialiseCalls;

	public:
		MockConstInitialisable(std::shared_ptr<CallRecorder<>> initialiseCallRecorder) :
			initialiseCalls(initialiseCallRecorder)
		{
		}

		void initialise(void) const { this->initialiseCalls->calledWith(); }
		const CallRecorder<> &callsToConstInitialise(void) const { return *this->initialiseCalls; }
	};
}

#endif
