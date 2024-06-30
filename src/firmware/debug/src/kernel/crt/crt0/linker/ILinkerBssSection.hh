#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_ILINKERBSSSECTION_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_ILINKERBSSSECTION_HH
#include <cstdint>
#include <iterator>

namespace smeg::kernel::crt::crt0::linker
{
	template <typename T>
	concept ILinkerBssSection = requires(const T &section)
	{
		{ section.begin() } -> std::output_iterator<std::uint32_t>;
		{ section.end() } -> std::output_iterator<std::uint32_t>;
	};
}

#endif
