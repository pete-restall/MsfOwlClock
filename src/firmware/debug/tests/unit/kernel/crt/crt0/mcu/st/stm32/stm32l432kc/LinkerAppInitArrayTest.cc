#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/InitFiniArray.hh"
#include "kernel/crt/crt0/mcu/st/stm32/stm32l432kc/LinkerAppInitArray.hh"

using namespace mettle;

using namespace smeg::kernel::crt;
using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc;

extern "C"
{
	const FiniArrayEntry __linker_code_flash_app_initArray_start = nullptr;
	const FiniArrayEntry __linker_code_flash_app_initArray_pastEnd = nullptr;
}

namespace smeg::tests::unit::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	suite<> linkerAppInitArrayTest("LinkerAppInitArray Test Suite", [](auto &unit)
	{
		unit.test("begin_called_expectStartAddressOfFiniArrayFromLinkerScript", []()
		{
			const LinkerAppInitArray section;
			expect(section.begin(), equal_to(&__linker_code_flash_app_initArray_start));
		});

		unit.test("end_called_expectPastEndAddressOfFiniArrayFromLinkerScript", []()
		{
			const LinkerAppInitArray section;
			expect(section.end(), equal_to(&__linker_code_flash_app_initArray_pastEnd));
		});
	});
}
