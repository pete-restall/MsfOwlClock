#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/linker/LinkerKernelInitArray.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::linker;

extern "C"
{
	const InitArrayEntry __linker_code_flash_kernel_initArray_start = nullptr;
	const InitArrayEntry __linker_code_flash_kernel_initArray_pastEnd = nullptr;
}

namespace smeg::tests::unit::kernel::crt::crt0::linker
{
	suite<> linkerKernelInitArrayTest("LinkerKernelInitArray Test Suite", [](auto &unit)
	{
		unit.test("begin_called_expectStartAddressOfInitArrayFromLinkerScript", []()
		{
			const LinkerKernelInitArray section;
			expect(section.begin(), equal_to(&__linker_code_flash_kernel_initArray_start));
		});

		unit.test("end_called_expectPastEndAddressOfInitArrayFromLinkerScript", []()
		{
			const LinkerKernelInitArray section;
			expect(section.end(), equal_to(&__linker_code_flash_kernel_initArray_pastEnd));
		});
	});
}