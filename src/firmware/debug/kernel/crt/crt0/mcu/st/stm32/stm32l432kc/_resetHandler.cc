#include "../../../../../Entrypoint.hh"

using namespace smeg::kernel::crt;

extern "C"
{
	[[noreturn]]
	[[gnu::naked]]
	void _resetHandler(void) noexcept
	{
		// TODO
		// load stack pointer (doesn't appear necessary, but seems other people (like ST) do - investigate why they do)

		// store reset reason (BOR, POR, MCLR, software reset, fault, etc.) / flags / whatever - pass to constructor of Entrypoint
		// set FPU mode for C compatibility
		//Entrypoint entrypoint(LinkerMemoryMap(), McuResetter());
		//entrypoint.run();
		while (1) ;;
		__builtin_unreachable();
	}
};
