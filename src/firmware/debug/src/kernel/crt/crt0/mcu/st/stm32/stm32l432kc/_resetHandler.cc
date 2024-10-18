#include "../../../../EntrypointFactory.hh"

#include "Crt0Environment.hh"

using namespace smeg::kernel::crt::crt0;
using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc;

extern "C"
{
	[[noreturn]]
	[[gnu::naked]]
	void _resetHandler(void) noexcept;

	[[noreturn]]
	[[gnu::naked]]
	void _resetHandler(void) noexcept
	{
		// TODO
		// load stack pointer (doesn't appear necessary, but seems other people (like ST) do - investigate why they do)

		// store reset reason (BOR, POR, MCLR, software reset, fault, etc.) / flags / whatever - pass to constructor of Entrypoint
		// set FPU mode for C compatibility - default FPCCR is fine but CPACR (full access to CP10 and CP11; p531 for default values); set FPDSCR - p37 ?
		// necessary to set VTOR to flash ?
		auto entrypoint(EntrypointFactory::create(Crt0Environment()));
		entrypoint.run();
		__asm__ volatile ("b.n __resetHandler"); // THIS SHOULD NEVER GET HIT - MAYBE WE JUST LOOP FOREVER INSTEAD, SEEING HOW THE Entrypoint::run() OUGHT TO BE APPLYING END-OF-LIFE POLICY
		__builtin_unreachable();
	}
};
