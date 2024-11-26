#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IHaveConfigForProvidedIsrs.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	template <auto X>
	struct StubIsrConfig
	{
		struct Handler
		{
			static void onInterrupt(void) noexcept
			{
			}
		};

		static constexpr auto irq = X;
	};

	struct StubNonIsrConfig
	{
		struct Handler
		{
			static void onInterrupt(void)
			{
			}
		};

		static constexpr auto irq = 123;
	};

	suite<> iHaveConfigForProvidedIsrsTest("IHaveConfigForProvidedIsrs Test Suite", [](auto &unit)
	{
		unit.test("IHaveConfigForProvidedIsrs_conceptPassedConfigWithoutIsrs_expectFalseIsReturned", []()
		{
			struct ConfigWithoutIsrs
			{
			};

			expect(IHaveConfigForProvidedIsrs<ConfigWithoutIsrs>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedIsrs_conceptPassedConfigWithEmptyTuple_expectTrueIsReturned", []()
		{
			struct ConfigWithEmptyIsrs
			{
				using ProvidedIsrs = std::tuple<>;
			};

			expect(IHaveConfigForProvidedIsrs<ConfigWithEmptyIsrs>, equal_to(true));
		});

		unit.test("IHaveConfigForProvidedIsrs_conceptPassedConfigWithSingleProvidedIsr_expectTrueIsReturned", []()
		{
			struct ConfigWithSingleIsr
			{
				using ProvidedIsrs = std::tuple<StubIsrConfig<1>>;
			};

			expect(IHaveConfigForProvidedIsrs<ConfigWithSingleIsr>, equal_to(true));
		});

		unit.test("IHaveConfigForProvidedIsrs_conceptPassedConfigWithSingleInvalidIsr_expectFalseIsReturned", []()
		{
			struct ConfigWithSingleInvalidIsr
			{
				using ProvidedIsrs = std::tuple<StubNonIsrConfig>;
			};

			expect(IHaveConfigForProvidedIsrs<ConfigWithSingleInvalidIsr>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedIsrs_conceptPassedConfigWithMultipleIsrs_expectTrueIsReturned", []()
		{
			struct ConfigWithMultipleIsrs
			{
				using ProvidedIsrs = std::tuple<StubIsrConfig<1>, StubIsrConfig<2>, StubIsrConfig<3>>;
			};

			expect(IHaveConfigForProvidedIsrs<ConfigWithMultipleIsrs>, equal_to(true));
		});

		unit.test("IHaveConfigForProvidedIsrs_conceptPassedConfigWithMultipleIsrsIncludingNonIsrConfig_expectFalseIsReturned", []()
		{
			struct ConfigWithInvalidIsr
			{
				using ProvidedIsrs = std::tuple<StubIsrConfig<1>, StubIsrConfig<2>, StubNonIsrConfig, StubIsrConfig<3>>;
			};

			expect(IHaveConfigForProvidedIsrs<ConfigWithInvalidIsr>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedIsrs_conceptPassedConfigWithArrayOfIsrs_expectFalseIsReturned", []()
		{
			struct ConfigWithArrayOfIsrs
			{
				using ProvidedIsrs = std::array<StubIsrConfig<1>, 3>;
			};

			expect(IHaveConfigForProvidedIsrs<ConfigWithArrayOfIsrs>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedIsrs_conceptPassedConfigWithPairOfIsrs_expectFalseIsReturned", []()
		{
			struct ConfigWithPairOfIsrs
			{
				using ProvidedIsrs = std::pair<StubIsrConfig<1>, StubIsrConfig<2>>;
			};

			expect(IHaveConfigForProvidedIsrs<ConfigWithPairOfIsrs>, equal_to(false));
		});
	});
}
