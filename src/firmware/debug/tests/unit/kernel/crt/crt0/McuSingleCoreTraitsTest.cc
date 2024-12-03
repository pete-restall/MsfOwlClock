#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/McuSingleCoreTraits.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0;

namespace smeg::tests::unit::kernel::crt::crt0
{
	suite<> mcuSingleCoreTraitsTest("McuSingleCoreTraits Test Suite", [](auto &unit)
	{
		unit.test("numberOfMcuCores_get_expectOne", []()
		{
			expect(McuSingleCoreTraits::numberOfMcuCores, equal_to(1));
		});

		unit.test("getMcuCoreId_called_expectZero", []()
		{
			expect(McuSingleCoreTraits::getMcuCoreId(), equal_to(0));
		});
	});
}
