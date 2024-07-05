#include <cstdint>
#include <ranges>
#include <span>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "../../../../NonDeterminism.hh"
#include "kernel/crt/crt0/linker/ILinkerInitialisableMemorySection.hh"
#include "kernel/crt/crt0/linker/LinkerBssMemorySection.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::linker;

namespace smeg::tests::unit::kernel::crt::crt0::linker
{
	suite<> linkerBssMemorySectionTest("LinkerBssMemorySection Test Suite", [](auto &unit)
	{
		unit.test("class_testedAgainstILinkerInitialisableMemoryException_expectTrue", []()
		{
			expect(ILinkerInitialisableMemorySection<LinkerBssMemorySection<std::uint32_t *>>, equal_to(true));
		});

		unit.test("constructor_called_expectWordsInBssSectionAreUnchanged", []()
		{
			auto ram(anyVectorOfSize<std::uint32_t>(100));
			auto originalRam(ram);

			LinkerBssMemorySection bssSection(ram.begin(), ram.end());
			expect(ram, equal_to(originalRam));
		});

		unit.test("initialise_called_expectWordsInSectionAreZeroed", []()
		{
			auto ram(anyVectorOfSize<std::uint32_t>(100));
			auto ramBssSection(anyNonEmptySpanIn(ram));

			LinkerBssMemorySection bssSection(ramBssSection.begin(), ramBssSection.end());
			bssSection.initialise();
			expect(ramBssSection, each(equal_to(0)));
		});

		unit.test("initialise_called_expectWordsInRamBeforeBssSectionAreUnchanged", []()
		{
			auto ram(anyVectorOfSize<std::uint32_t>(100));
			auto ramBssSection(std::span(ram.begin() + anyInClosedRange(1, 10), anyInClosedRange(1, 80)));
			auto ramBeforeBssSection(ram | std::views::take(ramBssSection.data() - ram.data()));
			std::vector originalRamBeforeBssSection(ramBeforeBssSection.begin(), ramBeforeBssSection.end());

			LinkerBssMemorySection bssSection(ramBssSection.begin(), ramBssSection.end());
			bssSection.initialise();

			expect(
				"Memory before initialised section",
				std::vector(ramBeforeBssSection.begin(), ramBeforeBssSection.end()),
				equal_to(originalRamBeforeBssSection));
		});

		unit.test("initialise_called_expectWordsInRamAfterBssSectionAreUnchanged", []()
		{
			auto ram(anyVectorOfSize<std::uint32_t>(100));
			auto ramBssSection(std::span(ram.begin() + anyInClosedRange(1, 10), anyInClosedRange(1, 80)));
			auto ramAfterBssSection(ram | std::views::drop(ramBssSection.data() + ramBssSection.size() - ram.data()));
			std::vector originalRamAfterBssSection(ramAfterBssSection.begin(), ramAfterBssSection.end());

			LinkerBssMemorySection bssSection(ramBssSection.begin(), ramBssSection.end());
			bssSection.initialise();

			expect(
				"Memory after initialised section",
				std::vector(ramAfterBssSection.begin(), ramAfterBssSection.end()),
				equal_to(originalRamAfterBssSection));
		});
	});
}
