extern "C"
{
// exit() calls __call_exitprocs and then _exit(); we need to trap __call_exitprocs() to only destroy application-created stuff methinks, so the kernel can continue running to shutdown properly.  Although should be fine if not using global objects, so maybe just provide a hook for it so it's not hidden away ?
// Can't override __call_exitprocs (unless we __wrap it), so maybe just making sure the kernel uses no statics is sufficient...
// Overriding exit() is also not possible as it's not weak.  However, __call_exitprocs() is weak if picolibc is built with '_LITE_EXIT'.  Investigate at some point...

	[[noreturn]]
	void _exit(void)
	{
		// TODO
		// Can probably make this a generic crt0 function; the reset is the only MCU-specific bit, so that's the code we need to specialise.
		//
		// if !kernel mode then will have to svcall to get into kernel mode to abort - presuming the kernel wasn't the aborter; in which case, loop forever if the MCU is not already in kernel mode
		// set the SYSRESETREQ bit in the AIRCR register; maybe store a 'software reset reason' struct in a few words of non-bss (ie. non-zeroed) ram for this
		// after the bit is set, enter a forever-loop, since it's not guaranteed that the reset is immediate; see p602 of the ARMv7 reference manual; 0xe000ed0c

		while (1)
			;;

		__builtin_unreachable();
	}
};
