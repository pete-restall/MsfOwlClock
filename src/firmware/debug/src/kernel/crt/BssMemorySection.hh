#ifndef __SMEG_KERNEL_CRT_BSSMEMORYSECTION_HH
#define __SMEG_KERNEL_CRT_BSSMEMORYSECTION_HH
#include <cstdint>

namespace smeg::kernel::crt
{
	class BssMemorySection
	{
private:
		std::uint32_t *start;
		std::uint32_t *pastEnd;

public:
		BssMemorySection(std::uint32_t *start, std::uint32_t *pastEnd);
		void initialise(void);
	};
}

#endif
