#include <cstdint>
#include <ranges>
#include <span>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "../../../../NonDeterminism.hh"
#include "kernel/crt/crt0/linker/LinkerBssMemoryMap.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0::linker;

namespace smeg::tests::unit::kernel::crt::crt0::linker
{
	suite<> linkerBssMemoryMapTest("LinkerBssMemoryMap Test Suite", [](auto &unit)
	{
		unit.test("constructor_called_expectWordsInSectionAreUnchanged", []()
		{
			auto bss(anyVectorOfSize<std::uint32_t>(100));
			auto originalBss(bss);

			const LinkerBssMemoryMap bssMap(anyNonEmptySpanIn(bss));
			expect(bss, equal_to(originalBss));
		});

		unit.test("initialise_calledWhenSingleSection_expectWordsInSectionAreZeroed", []()
		{
			auto bss(anyVectorOfSize<std::uint32_t>(100));
			auto section(anyNonEmptySpanIn(bss));

			const LinkerBssMemoryMap bssMap(section);
			bssMap.initialise();
			expect(section, each(equal_to(0)));
		});

		unit.test("initialise_calledWhenMultipleSections_expectWordsInEachSectionAreZeroed", []()
		{
			auto bss(anyVectorOfSize<std::uint32_t>(100));
			auto sections = std::vector{
				std::span(bss.begin() + 10, 7),
				std::span(bss.begin() + 80, 11),
				std::span(bss.begin() + 23, 4)
			};

			const LinkerBssMemoryMap bssMap(sections[0], sections[1], sections[2]);
			bssMap.initialise();
			expect(sections, each(each(equal_to(0))));
		});

		unit.test("initialise_called_expectWordsNotInSectionAreUnchanged", []()
		{
			auto bss(anyVectorOfSize<std::uint32_t>(100));
			auto section(anyNonEmptySpanIn(bss));
			auto bssBeforeSection(bss | std::views::take(section.data() - bss.data()));
			auto bssAfterSection(bss | std::views::drop(section.data() + section.size() - bss.data()));
			std::vector originalBssBeforeSection(bssBeforeSection.begin(), bssBeforeSection.end());
			std::vector originalBssAfterSection(bssAfterSection.begin(), bssAfterSection.end());

			const LinkerBssMemoryMap bssMap(section);
			bssMap.initialise();

			expect(
				"Memory before initialised section",
				std::vector(bssBeforeSection.begin(), bssBeforeSection.end()),
				equal_to(originalBssBeforeSection));

			expect(
				"Memory after initialised section",
				std::vector(bssAfterSection.begin(), bssAfterSection.end()),
				equal_to(originalBssAfterSection));
		});
	});
}
