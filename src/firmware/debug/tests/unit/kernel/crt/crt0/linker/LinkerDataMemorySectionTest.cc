#include <cstdint>
#include <ranges>
#include <span>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "../../../../NonDeterminism.hh"
#include "kernel/crt/crt0/linker/ILinkerInitialisableMemorySection.hh"
#include "kernel/crt/crt0/linker/LinkerDataMemorySection.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::linker;

namespace smeg::tests::unit::kernel::crt::crt0::linker
{
	suite<> linkerDataMemorySectionTest("LinkerDataMemorySection Test Suite", [](auto &unit)
	{
		unit.test("class_testedAgainstILinkerInitialisableMemoryException_expectTrue", []()
		{
			expect(ILinkerInitialisableMemorySection<LinkerDataMemorySection<const std::uint32_t *, std::uint32_t *>>, equal_to(true));
		});

		unit.test("constructor_called_expectWordsInRamDataSectionAreUnchanged", []()
		{
			const auto romData(anyVectorOfSize<std::uint32_t>(100));
			auto ram(anyVectorOfSize<std::uint32_t>(100));
			auto originalRam(ram);

			LinkerDataMemorySection dataSection(romData.begin(), romData.end(), ram.begin());
			expect(ram, equal_to(originalRam));
		});

		unit.test("initialise_calledWhenSectionIsZeroLength_expectWordsInDataSectionAreUnchanged", []()
		{
			const auto romData(anyVectorOfSize<std::uint32_t>(100));
			auto ram(anyVectorOfSize<std::uint32_t>(100));
			auto originalRam(ram);

			LinkerDataMemorySection dataSection(romData.begin(), romData.begin(), ram.begin());
			dataSection.initialise();
			expect(ram, equal_to(originalRam));
		});

		unit.test("initialise_called_expectWordsInRamDataSectionAreCopiedFromRom", []()
		{
			const auto romData(anyVectorOfSize<std::uint32_t>(anyInClosedRange(10, 50)));
			auto ram(anyVectorOfSize<std::uint32_t>(100));
			auto ramDataSection(anySpanInClosedRangeSize(ram, romData.size()));

			LinkerDataMemorySection dataSection(romData.begin(), romData.end(), ramDataSection.begin());
			dataSection.initialise();
			expect(ramDataSection, each(romData.begin(), romData.end(), equal_to<const std::uint32_t &>));
		});

		unit.test("initialise_called_expectWordsInRamBeforeDataSectionAreUnchanged", []()
		{
			const auto romData(anyVectorOfSize<std::uint32_t>(anyInClosedRange(10, 50)));
			auto ram(anyVectorOfSize<std::uint32_t>(100));
			auto ramDataSection(std::span(ram.begin() + anyInClosedRange(10, 40), romData.size()));
			auto ramBeforeDataSection(ram | std::views::take(ramDataSection.data() - ram.data()));
			std::vector originalRamBeforeDataSection(ramBeforeDataSection.begin(), ramBeforeDataSection.end());

			LinkerDataMemorySection dataSection(romData.begin(), romData.end(), ramDataSection.begin());
			dataSection.initialise();

			expect(
				"Memory before initialised section",
				std::vector(ramBeforeDataSection.begin(), ramBeforeDataSection.end()),
				equal_to(originalRamBeforeDataSection));
		});

		unit.test("initialise_called_expectWordsInRamAfterDataSectionAreUnchanged", []()
		{
			const auto romData(anyVectorOfSize<std::uint32_t>(anyInClosedRange(10, 50)));
			auto ram(anyVectorOfSize<std::uint32_t>(100));
			auto ramDataSection(std::span(ram.begin() + anyInClosedRange(10, 40), romData.size()));
			auto ramAfterDataSection(ram | std::views::drop(ramDataSection.data() + ramDataSection.size() - ram.data()));
			std::vector originalRamAfterDataSection(ramAfterDataSection.begin(), ramAfterDataSection.end());

			LinkerDataMemorySection dataSection(romData.begin(), romData.end(), ramDataSection.begin());
			dataSection.initialise();

			expect(
				"Memory after initialised section",
				std::vector(ramAfterDataSection.begin(), ramAfterDataSection.end()),
				equal_to(originalRamAfterDataSection));
		});
	});
}
