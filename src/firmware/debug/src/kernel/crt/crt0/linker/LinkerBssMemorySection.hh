#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERBSSMEMORYSECTION_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERBSSMEMORYSECTION_HH
#include <algorithm>
#include <cstdint>

namespace smeg::kernel::crt::crt0::linker
{
	template<std::output_iterator<std::uint32_t> TPtr>
	class LinkerBssMemorySection
	{
private:
		const TPtr alignedStart;
		const TPtr alignedPastEnd;

public:
		LinkerBssMemorySection(const TPtr start, const TPtr pastEnd) :
			alignedStart(start),
			alignedPastEnd(pastEnd)
		{
		}

		void initialise(void)
		{
			std::fill(this->alignedStart, this->alignedPastEnd, 0);
		}
	};
}

#endif
