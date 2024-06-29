#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/mcu/st/stm32/stm32l432kc/linker/LinkerKernelSramData.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker;

extern "C"
{
	std::uint32_t __linker_sram_data_kernel_start = 0;
	std::uint32_t __linker_sram_data_kernel_pastEnd = 0;
	const std::uint32_t __linker_sram_data_kernel_lmaStart = 0;
}	const std::uint32_t __linker_sram_data_kernel_lmaPastEnd = 0;

namespace smeg::tests::unit::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	suite<> linkerKernelSramDataTest("LinkerKernelSramData Test Suite", [](auto &unit)
	{
		unit.test("ramBegin_called_expectStartVirtualAddressOfSramDataFromLinkerScript", []()
		{
			const LinkerKernelSramData section;
			expect(section.ramBegin(), equal_to(&__linker_sram_data_kernel_start));
		});

		unit.test("ramEnd_called_expectPastEndVirtualAddressOfSramDataFromLinkerScript", []()
		{
			const LinkerKernelSramData section;
			expect(section.ramEnd(), equal_to(&__linker_sram_data_kernel_pastEnd));
		});

		unit.test("romBegin_called_expectStartLoadAddressOfSramDataFromLinkerScript", []()
		{
			const LinkerKernelSramData section;
			expect(section.romBegin(), equal_to(&__linker_sram_data_kernel_lmaStart));
		});

		unit.test("romEnd_called_expectPastEndLoadAddressOfSramDataFromLinkerScript", []()
		{
			const LinkerKernelSramData section;
			expect(section.romEnd(), equal_to(&__linker_sram_data_kernel_lmaPastEnd));
		});
	});
}
