#ifndef __SMEG_KERNEL_CRT_CRT0_MCUSINGLECORETRAITS_HH
#define __SMEG_KERNEL_CRT_CRT0_MCUSINGLECORETRAITS_HH
#include "../../IMcuCoreTraits.hh"

namespace smeg::kernel::crt::crt0
{
	struct McuSingleCoreTraits
	{
		static constexpr auto numberOfMcuCores = 1;

		static consteval auto getMcuCoreId(void) noexcept
		{
			return 0;
		}
	};

	static_assert(IMcuCoreTraits<McuSingleCoreTraits>, "McuSingleCoreTraits does not match the IMcuCoreTraits concept");
}

#endif
