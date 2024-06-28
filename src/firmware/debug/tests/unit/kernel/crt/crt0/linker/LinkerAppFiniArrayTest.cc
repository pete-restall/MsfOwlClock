#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/linker/LinkerAppFiniArray.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::linker;

extern "C"
{
	const FiniArrayEntry __linker_code_flash_app_finiArray_start = nullptr;
	const FiniArrayEntry __linker_code_flash_app_finiArray_pastEnd = nullptr;
}

namespace smeg::tests::unit::kernel::crt::crt0::linker
{
	suite<> linkerAppFiniArrayTest("LinkerAppFiniArray Test Suite", [](auto &unit)
	{
		unit.test("begin_called_expectStartAddressOfFiniArrayFromLinkerScript", []()
		{
			const LinkerAppFiniArray section;
			expect(section.begin(), equal_to(&__linker_code_flash_app_finiArray_start));
		});

		unit.test("end_called_expectPastEndAddressOfFiniArrayFromLinkerScript", []()
		{
			const LinkerAppFiniArray section;
			expect(section.end(), equal_to(&__linker_code_flash_app_finiArray_pastEnd));
		});
	});
}
