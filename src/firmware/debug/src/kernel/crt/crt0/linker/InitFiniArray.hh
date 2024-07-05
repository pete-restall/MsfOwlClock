#ifndef __SMEG_KERNEL_CRT_CRT0_LINKER_INITFINIARRAY_HH
#define __SMEG_KERNEL_CRT_CRT0_LINKER_INITFINIARRAY_HH

namespace smeg::kernel::crt::crt0::linker
{
	typedef void (*InitArrayEntry)(void); // TODO: PROBABLY noexcept TO ENFORCE abort() ON EXCEPTIONS
	typedef void (*FiniArrayEntry)(void); // TODO: PROBABLY noexcept TO ENFORCE abort() ON EXCEPTIONS
}

#endif
