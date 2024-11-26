#ifndef __SMEG_TESTS_UNIT_KERNEL_CRT_CRT0ENVIRONMENTTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_CRT_CRT0ENVIRONMENTTESTDOUBLES_HH
#include "BootloaderTestDoubles.hh"
#include "Crt0EnvironmentSubstitute.hh"
#include "LinkerMemoryMapTestDoubles.hh"

namespace smeg::tests::unit::kernel::crt
{
	class Crt0EnvironmentTestDoubles
	{
	private:
		LinkerMemoryMapTestDoubles &linkerMemoryMapTestDoubles;
		BootloaderTestDoubles &bootloaderTestDoubles;

	public:
		Crt0EnvironmentTestDoubles(
			LinkerMemoryMapTestDoubles &linkerMemoryMapTestDoubles,
			BootloaderTestDoubles &bootloaderTestDoubles) :
			linkerMemoryMapTestDoubles(linkerMemoryMapTestDoubles),
			bootloaderTestDoubles(bootloaderTestDoubles)
		{
		}

		auto stub(void) const
		{
			return Crt0EnvironmentSubstitute(this->linkerMemoryMapTestDoubles, this->bootloaderTestDoubles);
		}

		auto dummy(void) const
		{
			return this->stub();
		}
	};
}

#endif
