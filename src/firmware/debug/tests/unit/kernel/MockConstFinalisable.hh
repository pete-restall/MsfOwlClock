#ifndef __SMEG_TESTS_UNIT_KERNEL_MOCKCONSTFINALISABLE_HH
#define __SMEG_TESTS_UNIT_KERNEL_MOCKCONSTFINALISABLE_HH
#include <memory>
#include "../CallRecorder.hh"

namespace smeg::tests::unit::kernel
{
	class MockConstFinalisable
	{
	private:
		std::shared_ptr<CallRecorder<>> finaliseCalls;

	public:
		MockConstFinalisable(std::shared_ptr<CallRecorder<>> finaliseCallRecorder) :
			finaliseCalls(finaliseCallRecorder)
		{
		}

		void finalise(void) const { this->finaliseCalls->calledWith(); }
		const CallRecorder<> &callsToConstFinalise(void) const { return *this->finaliseCalls; }
	};
}

#endif
