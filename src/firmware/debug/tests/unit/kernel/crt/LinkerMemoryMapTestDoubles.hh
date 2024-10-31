#ifndef __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERMEMORYMAPTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_CRT_LINKERMEMORYMAPTESTDOUBLES_HH
#include "LinkerAppMemoryMapTestDoubles.hh"
#include "LinkerKernelMemoryMapTestDoubles.hh"
#include "LinkerMemoryMapSubstitute.hh"

namespace smeg::tests::unit::kernel::crt
{
	class LinkerMemoryMapTestDoubles
	{
	private:
		LinkerKernelMemoryMapTestDoubles &kernelMemoryMapTestDoubles;
		LinkerAppMemoryMapTestDoubles &appMemoryMapTestDoubles;

	public:
		LinkerMemoryMapTestDoubles(
			LinkerKernelMemoryMapTestDoubles &kernelMemoryMapTestDoubles,
			LinkerAppMemoryMapTestDoubles &appMemoryMapTestDoubles) :
			kernelMemoryMapTestDoubles(kernelMemoryMapTestDoubles),
			appMemoryMapTestDoubles(appMemoryMapTestDoubles)
		{
		}

		auto stub(void) const
		{
			return LinkerMemoryMapSubstitute(this->kernelMemoryMapTestDoubles, this->appMemoryMapTestDoubles);
		}

		auto dummy(void) const
		{
			return this->stub();
		}
	};
}

#endif
