extern "C"
{
	[[noreturn]]
	void abort(void)
	{
		// TODO
		// Can probably make this a generic crt0 function; the reset is the only MCU-specific bit, so that's the code we need to specialise.
		// We need one for exit(whateverCode), too (this one being a normal exit, abort() being abnormal).
		//
		// if !kernel mode then will have to svcall to get into kernel mode to abort - presuming the kernel wasn't the aborter; in which case, loop forever if the MCU is not already in kernel mode
		// set the SYSRESETREQ bit in the AIRCR register; maybe store a 'software reset reason' struct in a few words of non-bss (ie. non-zeroed) ram for this
		// after the bit is set, enter a forever-loop, since it's not guaranteed that the reset is immediate; see p602 of the ARMv7 reference manual; 0xe000ed0c

		while (1)
			;;

		__builtin_unreachable();
	}
};
