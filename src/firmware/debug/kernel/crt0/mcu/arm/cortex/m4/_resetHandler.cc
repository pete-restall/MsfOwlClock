extern void blinkyBlinky(void) noexcept;

extern "C"
{
	[[noreturn]]
	[[gnu::naked]]
	void _resetHandler(void) noexcept
	{
		// TODO
		// load stack pointer (doesn't appear necessary, but seems other people (like ST) do - investigate why they do)
		// store reset reason (BOR, POR, MCLR, software reset, fault, etc.) / flags / whatever
		// set FPU mode for C compatibility
		// initialise various bss / data segments
		// call init sections
		// call kernel to initialise and run itself, the microcontroller, the application, any bootloaders, etc.
		// call equivalent of exit(whateverCode) to 'exit' with a successful code - if we're not in kernel mode then we'll need to just loop forever...

		blinkyBlinky();
		while (1)
			;;

		__builtin_unreachable();
	}
};
