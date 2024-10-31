#ifndef __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERKERNELMEMORYMAPTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERKERNELMEMORYMAPTESTDOUBLES_HH
#include "../FinalisableTestDoubles.hh"
#include "../InitialisableTestDoubles.hh"
#include "LinkerKernelMemoryMapSubstitute.hh"

namespace smeg::tests::unit::kernel::crt
{
	class LinkerKernelMemoryMapTestDoubles
	{
	private:
		InitialisableTestDoubles &initialisableTestDoubles;
		FinalisableTestDoubles &finalisableTestDoubles;

	public:
		LinkerKernelMemoryMapTestDoubles(InitialisableTestDoubles &initialisableTestDoubles, FinalisableTestDoubles &finalisableTestDoubles) :
			initialisableTestDoubles(initialisableTestDoubles),
			finalisableTestDoubles(finalisableTestDoubles)
		{
		}

		auto stub(void) const
		{
			return LinkerKernelMemoryMapSubstitute(this->initialisableTestDoubles, this->initialisableTestDoubles, this->finalisableTestDoubles);
		}

		auto dummy(void) const
		{
			return this->stub();
		}
	};
}

#endif
