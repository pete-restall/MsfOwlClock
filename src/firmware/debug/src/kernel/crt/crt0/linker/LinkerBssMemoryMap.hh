#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERBSSMEMORYMAP_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_LINKERBSSMEMORYMAP_HH
#include <algorithm>
#include <tuple>

#include "ILinkerBssSection.hh"

namespace smeg::kernel::crt::crt0::linker
{
	template<ILinkerBssSection TFirstBssSection, ILinkerBssSection... TMoreBssSections>
	class LinkerBssMemoryMap
	{
private:
		std::tuple<TFirstBssSection, TMoreBssSections...> sections;

public:
		LinkerBssMemoryMap(TFirstBssSection bssSection, TMoreBssSections... moreBssSections)
			: sections{bssSection, moreBssSections...}
		{
		}

		void initialise(void) const
		{
			auto fillSection = [](auto &...section) { (std::fill(section.begin(), section.end(), 0), ...); };
			std::apply(fillSection, this->sections);
		}
	};
}

#endif
