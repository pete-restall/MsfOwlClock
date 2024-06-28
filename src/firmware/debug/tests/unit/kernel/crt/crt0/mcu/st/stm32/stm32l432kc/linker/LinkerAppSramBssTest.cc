#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/mcu/st/stm32/stm32l432kc/linker/LinkerAppSramBss.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker;

extern "C"
{
	const std::uint32_t __linker_sram_bss_app_start = 0;
	const std::uint32_t __linker_sram_bss_app_pastEnd = 0;
}

namespace smeg::tests::unit::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	suite<> linkerAppSramBssTest("LinkerAppSramBss Test Suite", [](auto &unit)
	{
		unit.test("begin_called_expectStartAddressOfSramBssFromLinkerScript", []()
		{
			const LinkerAppSramBss section;
			expect(section.begin(), equal_to(&__linker_sram_bss_app_start));
		});

		unit.test("end_called_expectPastEndAddressOfSramBssFromLinkerScript", []()
		{
			const LinkerAppSramBss section;
			expect(section.end(), equal_to(&__linker_sram_bss_app_pastEnd));
		});
	});
}
