#ifndef __SMEG_TESTS_UNIT_VIEWUTILITIES_HH
#define __SMEG_TESTS_UNIT_VIEWUTILITIES_HH
#include <ranges>
#include <vector>

namespace smeg::tests::unit
{
	template <std::ranges::range TRange>
	auto asVector(TRange &&range)
	{
		auto rangeAsCommon = range | std::views::common;
		return std::vector(rangeAsCommon.begin(), rangeAsCommon.end());
	}
}

#endif
