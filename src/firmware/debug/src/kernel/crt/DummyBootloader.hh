#ifndef __SMEG_KERNEL_CRT_DUMMYBOOTLOADER_HH
#define __SMEG_KERNEL_CRT_DUMMYBOOTLOADER_HH
#include "IBootloader.hh"

namespace smeg::kernel::crt
{
	// TODO: Temporary class just to provide linkage and various notes / musings on how the whole process will work.  Almost certainly some MCU-specific
	// aspects, plus the Crt0Environment probably needs injecting, etc.
	class DummyBootloader
	{
	public:
		void onPreEntrypoint(void) const noexcept
		{
			// TODO: firmware upgrades will need to be done in stages.  If one stage fails, we can tell where.  To initiate a firmware update:
			//   1. erase a block in the application's .text (linker script provides the range)  The first two words of this block are the 'bootloader magic bytes' - if something goes wrong after erasing even the first bit, the magic bytes will be damaged
			//   2. write the intermediate bootloader into the (erased block + 16 bytes)
			//   3. write the address of the intermediate bootloader entrypoint into (erased block + 12 bytes) - the word at (erased block + 8 bytes) is reserved
			//   4. write the bootloader magic bytes (0x736d6567, 0x68656164) into (erased block + 0 bytes)
			//   5. reset ?
			//
			// On booting, we thus need to:
			//   1. if bootloader magic bytes == (0x534d4547, 0x48454144), jump to the application (onPreEntrypoint and onPostEntrypoint need to do nothing in this case, unless we've been reset to initiate a new update)
			//   2. if bootloader magic bytes == (0x534d4547, *), the new kernel bootloader is working, so call that (from onPostEntrypoint)
			//   3. if bootloader magic bytes == (*, 0x68656164), load the intermediate bootloader address (erased block + 12 bytes) and jump to it (from onPreEntrypoint - cannot guarantee the intermediate bootloader wasn't interrupted whilst trashing the kernel / after destroying the .init sections)
			//   4. if bootloader magic bytes are anything else then the application is corrupted but the kernel bootloader should still be working, so call that (from onPostEntrypoint ?)
			//
			// When the intermediate bootloader is invoked, write the kernel portion of the firmware:
			//   1. erase and write the non-vector and non-bootloader locations
			//   2. erase the vector table and bootloader and write those, then set the first magic byte to 0x534d4547
			// *** NOTE THAT IT IS POSSIBLE TO BRICK THE DEVICE IF STEP 2 FAILS, IF, FOR EXAMPLE, POWER IS LOST ***
			// *** FOR THE PIC32CX DEVICE, THERE IS SPECIFIC FUNCTIONALITY TO HELP THIS - THE 'BKSWRST' COMMAND AND BANKED FLASH, WHICH WOULD PRECLUDE THE
			//     NEED FOR THE INTERMEDIATE BOOTLOADER ENTIRELY ***
			//
			// When the kernel bootloader needs to do its work, erase and write the application portion of the firmware, then set the second magic byte to 0x48454144
			//
			// The reading of the kernel config, the app initialisation, jumping to the app, etc. all need to be done in a separate (non-inline) method so the
			// kernel doesn't try using corrupted application state during the firmware upgrade process.  This all relies on having anything in 'libkernel',
			// 'libcrt' and 'libcrt0' self-contained (including exception tables, dependent libgcc / libstdc++ library code, etc.)
		}

		void onPostEntrypoint(void) const noexcept
		{
		}
	};

	static_assert(IBootloader<DummyBootloader>, "DummyBootloader must be an IBootloader");
}

#endif
