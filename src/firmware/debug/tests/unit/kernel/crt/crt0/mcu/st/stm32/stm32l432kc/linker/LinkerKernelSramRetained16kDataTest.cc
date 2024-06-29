#include <cstdint>
#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/mcu/st/stm32/stm32l432kc/linker/LinkerKernelSramRetained16kData.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker;

extern "C"
{
	std::uint32_t __linker_sram_retained16k_data_kernel_start = 0;
	std::uint32_t __linker_sram_retained16k_data_kernel_pastEnd = 0;
	const std::uint32_t __linker_sram_retained16k_data_kernel_lmaStart = 0;
}	const std::uint32_t __linker_sram_retained16k_data_kernel_lmaPastEnd = 0;

namespace smeg::tests::unit::kernel::crt::crt0::mcu::st::stm32::stm32l432kc::linker
{
	suite<> linkerKernelSramRetained16kDataTest("LinkerKernelSramRetained16kData Test Suite", [](auto &unit)
	{
		unit.test("ramBegin_called_expectStartVirtualAddressOfSramRetained16kDataFromLinkerScript", []()
		{
			const LinkerKernelSramRetained16kData section;
			expect(section.ramBegin(), equal_to(&__linker_sram_retained16k_data_kernel_start));
		});

		unit.test("ramEnd_called_expectPastEndVirtualAddressOfSramRetained16kDataFromLinkerScript", []()
		{
			const LinkerKernelSramRetained16kData section;
			expect(section.ramEnd(), equal_to(&__linker_sram_retained16k_data_kernel_pastEnd));
		});

		unit.test("romBegin_called_expectStartLoadAddressOfSramRetained16kDataFromLinkerScript", []()
		{
			const LinkerKernelSramRetained16kData section;
			expect(section.romBegin(), equal_to(&__linker_sram_retained16k_data_kernel_lmaStart));
		});

		unit.test("romEnd_called_expectPastEndLoadAddressOfSramRetained16kDataFromLinkerScript", []()
		{
			const LinkerKernelSramRetained16kData section;
			expect(section.romEnd(), equal_to(&__linker_sram_retained16k_data_kernel_lmaPastEnd));
		});
	});
}
