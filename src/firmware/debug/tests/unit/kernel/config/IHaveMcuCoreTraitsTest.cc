#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/config/IHaveMcuCoreTraits.hh"

using namespace mettle;

using namespace smeg::kernel::config;

namespace smeg::tests::unit::kernel::config
{
	struct EmptyConfig
	{
	};

	struct ConfigWithMcuCoreTraits
	{
		struct McuCoreTraits
		{
			static constexpr auto numberOfMcuCores = 1;

			static auto getMcuCoreId(void) noexcept
			{
				return 0;
			}
		};
	};

	struct ConfigWithInvalidMcuCoreTraits
	{
		struct McuCoreTraits
		{
			static constexpr auto somethingNotMcuCoreRelated = 666;
		};
	};

	suite<> iHaveMcuCoreTraitsTest("IHaveMcuCoreTraits Test Suite", [](auto &unit)
	{
		unit.test("IHaveMcuCoreTraits_conceptPassedNonClass_expectFalseIsReturned", []()
		{
			expect(IHaveMcuCoreTraits<int>, equal_to(false));
			expect(IHaveMcuCoreTraits<double>, equal_to(false));
			expect(IHaveMcuCoreTraits<bool>, equal_to(false));
		});

		unit.test("IHaveMcuCoreTraits_conceptPassedEmptyConfig_expectFalseIsReturned", []()
		{
			expect(IHaveMcuCoreTraits<EmptyConfig>, equal_to(false));
		});

		unit.test("IHaveMcuCoreTraits_conceptPassedConfigWithMcuCoreTraits_expectTrueIsReturned", []()
		{
			expect(IHaveMcuCoreTraits<ConfigWithMcuCoreTraits>, equal_to(true));
		});

		unit.test("IHaveMcuCoreTraits_conceptPassedConfigWithInvalidMcuCoreTraits_expectFalseIsReturned", []()
		{
			expect(IHaveMcuCoreTraits<ConfigWithInvalidMcuCoreTraits>, equal_to(false));
		});
	});
}
