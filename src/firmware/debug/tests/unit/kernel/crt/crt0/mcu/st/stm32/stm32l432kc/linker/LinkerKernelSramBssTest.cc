#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/mcu/st/stm32/stm32l432kc/linker/LinkerKernelSramBss.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker;

extern "C"
{
	const std::uint32_t __linker_sram_bss_kernel_start = 0;
	const std::uint32_t __linker_sram_bss_kernel_pastEnd = 0;
}

namespace smeg::tests::unit::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	suite<> linkerKernelSramBssTest("LinkerKernelSramBss Test Suite", [](auto &unit)
	{
		unit.test("begin_called_expectStartAddressOfSramBssFromLinkerScript", []()
		{
			const LinkerKernelSramBss section;
			expect(section.begin(), equal_to(&__linker_sram_bss_kernel_start));
		});

		unit.test("end_called_expectPastEndAddressOfSramBssFromLinkerScript", []()
		{
			const LinkerKernelSramBss section;
			expect(section.end(), equal_to(&__linker_sram_bss_kernel_pastEnd));
		});
	});
}
