#ifndef __SMEG_KERNEL_CRT_IRESETMCU_HH
#define __SMEG_KERNEL_CRT_IRESETMCU_HH

namespace smeg::kernel::crt
{
	template <class T>
	concept IResetMcu = requires(const T &resetter)
	{
		{ resetter.reset() } noexcept; // TODO: PROBABLY NEEDS TO TAKE A DELEGATE FOR ENSURING IT'S EXECUTED FROM WITHIN KERNEL MODE...
	};
}

#endif
