#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/InitFiniArray.hh"
#include "kernel/crt/crt0/mcu/st/stm32/stm32l432kc/LinkerKernelFiniArray.hh"

using namespace mettle;

using namespace smeg::kernel::crt;
using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc;

extern "C"
{
	const FiniArrayEntry __linker_code_flash_kernel_finiArray_start = nullptr;
	const FiniArrayEntry __linker_code_flash_kernel_finiArray_pastEnd = nullptr;
}

namespace smeg::tests::unit::kernel::crt::crt0::mcu::st::stm32::stm32l432kc
{
	suite<> linkerKernelFiniArrayTest("LinkerKernelFiniArray Test Suite", [](auto &unit)
	{
		unit.test("begin_called_expectStartAddressOfFiniArrayFromLinkerScript", []()
		{
			const LinkerKernelFiniArray section;
			expect(section.begin(), equal_to(&__linker_code_flash_kernel_finiArray_start));
		});

		unit.test("end_called_expectPastEndAddressOfFiniArrayFromLinkerScript", []()
		{
			const LinkerKernelFiniArray section;
			expect(section.end(), equal_to(&__linker_code_flash_kernel_finiArray_pastEnd));
		});
	});
}
