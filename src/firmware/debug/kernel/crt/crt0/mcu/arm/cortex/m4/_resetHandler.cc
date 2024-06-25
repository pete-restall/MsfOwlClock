extern "C"
{
	[[noreturn]]
	[[gnu::naked]]
	extern void _entrypoint(void) noexcept;

	[[noreturn]]
	[[gnu::naked]]
	void _resetHandler(void) noexcept
	{
		// TODO
		// need a big try...catch around this to comply with noexcept; constructors could throw...
		// load stack pointer (doesn't appear necessary, but seems other people (like ST) do - investigate why they do)

		// to keep this entrypoint as lightweight as possible and also allow testing ([[naked]] is not conducive to this), these next two points should really be handled by a callback hook, something that _entrypoint calls, like __initialiseMcuBeforeCrt() or something
		// store reset reason (BOR, POR, MCLR, software reset, fault, etc.) / flags / whatever
		// set FPU mode for C compatibility
		_entrypoint();
		__builtin_unreachable();
	}
};
