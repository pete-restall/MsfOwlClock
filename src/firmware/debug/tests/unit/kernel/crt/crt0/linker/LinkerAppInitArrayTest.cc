#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/linker/LinkerAppInitArray.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::linker;

extern "C"
{
	const FiniArrayEntry __linker_code_flash_app_initArray_start = nullptr;
	const FiniArrayEntry __linker_code_flash_app_initArray_pastEnd = nullptr;
}

namespace smeg::tests::unit::kernel::crt::crt0::linker
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
