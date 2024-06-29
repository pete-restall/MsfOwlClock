#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/mcu/st/stm32/stm32l432kc/linker/LinkerAppSramRetained16kData.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker;

extern "C"
{
	std::uint32_t __linker_sram_retained16k_data_app_start = 0;
	std::uint32_t __linker_sram_retained16k_data_app_pastEnd = 0;
	const std::uint32_t __linker_sram_retained16k_data_app_lmaStart = 0;
}	const std::uint32_t __linker_sram_retained16k_data_app_lmaPastEnd = 0;

namespace smeg::tests::unit::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	suite<> linkerAppSramRetained16kDataTest("LinkerAppSramRetained16kData Test Suite", [](auto &unit)
	{
		unit.test("ramBegin_called_expectStartVirtualAddressOfSramRetained16kDataFromLinkerScript", []()
		{
			const LinkerAppSramRetained16kData section;
			expect(section.ramBegin(), equal_to(&__linker_sram_retained16k_data_app_start));
		});

		unit.test("ramEnd_called_expectPastEndVirtualAddressOfSramRetained16kDataFromLinkerScript", []()
		{
			const LinkerAppSramRetained16kData section;
			expect(section.ramEnd(), equal_to(&__linker_sram_retained16k_data_app_pastEnd));
		});

		unit.test("romBegin_called_expectStartLoadAddressOfSramRetained16kDataFromLinkerScript", []()
		{
			const LinkerAppSramRetained16kData section;
			expect(section.romBegin(), equal_to(&__linker_sram_retained16k_data_app_lmaStart));
		});

		unit.test("romEnd_called_expectPastEndLoadAddressOfSramRetained16kDataFromLinkerScript", []()
		{
			const LinkerAppSramRetained16kData section;
			expect(section.romEnd(), equal_to(&__linker_sram_retained16k_data_app_lmaPastEnd));
		});
	});
}
