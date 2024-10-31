#ifndef __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERAPPMEMORYMAPTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERAPPMEMORYMAPTESTDOUBLES_HH
#include "../FinalisableTestDoubles.hh"
#include "../InitialisableTestDoubles.hh"
#include "LinkerAppMemoryMapSubstitute.hh"

namespace smeg::tests::unit::kernel::crt
{
	class LinkerAppMemoryMapTestDoubles
	{
	private:
		InitialisableTestDoubles &initialisableTestDoubles;
		FinalisableTestDoubles &finalisableTestDoubles;

	public:
		LinkerAppMemoryMapTestDoubles(InitialisableTestDoubles &initialisableTestDoubles, FinalisableTestDoubles &finalisableTestDoubles) :
			initialisableTestDoubles(initialisableTestDoubles),
			finalisableTestDoubles(finalisableTestDoubles)
		{
		}

		auto stub(void) const
		{
			return LinkerAppMemoryMapSubstitute(this->initialisableTestDoubles, this->initialisableTestDoubles, this->finalisableTestDoubles);
		}

		auto dummy(void) const
		{
			return this->stub();
		}
	};
}

#endif
