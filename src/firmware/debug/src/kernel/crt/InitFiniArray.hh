#ifndef __SMEG_KERNEL_CRT_INITFINIARRAY_HH
#define __SMEG_KERNEL_CRT_INITFINIARRAY_HH

namespace smeg::kernel::crt
{
	typedef void (*InitArrayEntry)(void);
	typedef void (*FiniArrayEntry)(void);
}

#endif
