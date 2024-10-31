#ifndef __SMEG_KERNEL_CRT_NOBOOTLOADER_HH
#define __SMEG_KERNEL_CRT_NOBOOTLOADER_HH
#include "IBootloader.hh"

namespace smeg::kernel::crt
{
	class NoBootloader
	{
	public:
		void onPreEntrypoint(void) const noexcept
		{
		}

		void onPostEntrypoint(void) const noexcept
		{
		}
	};

	static_assert(IBootloader<NoBootloader>, "NoBootloader must be an IBootloader");
}

#endif
