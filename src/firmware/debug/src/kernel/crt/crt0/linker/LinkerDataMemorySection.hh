#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERDATAMEMORYSECTION_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERDATAMEMORYSECTION_HH
#include <algorithm>
#include <cstdint>

namespace smeg::kernel::crt::crt0::linker
{
	template <std::input_iterator TRomPtr, std::output_iterator<std::uint32_t> TRamPtr>
	class LinkerDataMemorySection
	{
	private:
		const TRomPtr romAlignedStart;
		const TRomPtr romAlignedPastEnd;
		const TRamPtr ramAlignedStart;

	public:
		LinkerDataMemorySection(const TRomPtr romStart, const TRomPtr romPastEnd, const TRamPtr ramStart) :
			romAlignedStart(romStart),
			romAlignedPastEnd(romPastEnd),
			ramAlignedStart(ramStart)
		{
		}

		void initialise(void)
		{
			std::copy(this->romAlignedStart, this->romAlignedPastEnd, this->ramAlignedStart);
		}
	};
}

#endif
