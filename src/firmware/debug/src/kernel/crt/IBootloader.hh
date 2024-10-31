#ifndef __SMEG_KERNEL_CRT_IBOOTLOADER_HH
#define __SMEG_KERNEL_CRT_IBOOTLOADER_HH
#include <concepts>

namespace smeg::kernel::crt
{
	template <typename T>
	concept IBootloader = requires(const T &bootloader)
	{
		{ bootloader.onPreEntrypoint() } -> std::same_as<void>;
		{ noexcept(bootloader.onPreEntrypoint()) };

		{ bootloader.onPostEntrypoint() } -> std::same_as<void>;
		{ noexcept(bootloader.onPostEntrypoint()) };
	};
}

#endif
