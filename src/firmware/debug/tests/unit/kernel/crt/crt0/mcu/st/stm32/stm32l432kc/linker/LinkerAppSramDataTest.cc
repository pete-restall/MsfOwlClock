#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/mcu/st/stm32/stm32l432kc/linker/LinkerAppSramData.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker;

extern "C"
{
	std::uint32_t __linker_sram_data_app_start = 0;
	std::uint32_t __linker_sram_data_app_pastEnd = 0;
	const std::uint32_t __linker_sram_data_app_lmaStart = 0;
}	const std::uint32_t __linker_sram_data_app_lmaPastEnd = 0;

namespace smeg::tests::unit::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	suite<> linkerAppSramDataTest("LinkerAppSramData Test Suite", [](auto &unit)
	{
		unit.test("ramBegin_called_expectStartVirtualAddressOfSramDataFromLinkerScript", []()
		{
			const LinkerAppSramData section;
			expect(section.ramBegin(), equal_to(&__linker_sram_data_app_start));
		});

		unit.test("ramEnd_called_expectPastEndVirtualAddressOfSramDataFromLinkerScript", []()
		{
			const LinkerAppSramData section;
			expect(section.ramEnd(), equal_to(&__linker_sram_data_app_pastEnd));
		});

		unit.test("romBegin_called_expectStartLoadAddressOfSramDataFromLinkerScript", []()
		{
			const LinkerAppSramData section;
			expect(section.romBegin(), equal_to(&__linker_sram_data_app_lmaStart));
		});

		unit.test("romEnd_called_expectPastEndLoadAddressOfSramDataFromLinkerScript", []()
		{
			const LinkerAppSramData section;
			expect(section.romEnd(), equal_to(&__linker_sram_data_app_lmaPastEnd));
		});
	});
}
