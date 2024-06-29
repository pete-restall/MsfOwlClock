#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/mcu/st/stm32/stm32l432kc/linker/LinkerAppSramRetained16kBss.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker;

extern "C"
{
	std::uint32_t __linker_sram_bss_retained16k_app_start = 0;
	std::uint32_t __linker_sram_bss_retained16k_app_pastEnd = 0;
}

namespace smeg::tests::unit::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	suite<> linkerAppSramRetained16kBssTest("LinkerAppSramRetained16kBss Test Suite", [](auto &unit)
	{
		unit.test("begin_called_expectStartAddressOfSramRetained16kBssFromLinkerScript", []()
		{
			const LinkerAppSramRetained16kBss section;
			expect(section.begin(), equal_to(&__linker_sram_bss_retained16k_app_start));
		});

		unit.test("end_called_expectPastEndAddressOfSramRetained16kBssFromLinkerScript", []()
		{
			const LinkerAppSramRetained16kBss section;
			expect(section.end(), equal_to(&__linker_sram_bss_retained16k_app_pastEnd));
		});
	});
}
