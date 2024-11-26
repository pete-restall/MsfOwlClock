#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IHaveConfigForProvidedSyscalls.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct DummyContext
	{
	};

	struct DummySyscall
	{
	};

	template <auto X>
	struct StubSyscallConfig
	{
		struct Handler
		{
			void onSyscall(DummyContext &, DummySyscall &)
			{
			}
		};
	};

	suite<> iHaveConfigForProvidedSyscallsTest("IHaveConfigForProvidedSyscalls Test Suite", [](auto &unit)
	{
		unit.test("IHaveConfigForProvidedSyscalls_conceptPassedConfigWithoutSyscalls_expectFalseIsReturned", []()
		{
			struct ConfigWithoutSyscalls
			{
			};

			expect(IHaveConfigForProvidedSyscalls<ConfigWithoutSyscalls>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedSyscalls_conceptPassedConfigWithEmptyTuple_expectTrueIsReturned", []()
		{
			struct ConfigWithEmptySyscalls
			{
				using ProvidedSyscalls = std::tuple<>;
			};

			expect(IHaveConfigForProvidedSyscalls<ConfigWithEmptySyscalls>, equal_to(true));
		});

		unit.test("IHaveConfigForProvidedSyscalls_conceptPassedConfigWithSingleProvidedSyscall_expectTrueIsReturned", []()
		{
			struct ConfigWithSingleSyscall
			{
				using ProvidedSyscalls = std::tuple<StubSyscallConfig<1>>;
			};

			expect(IHaveConfigForProvidedSyscalls<ConfigWithSingleSyscall>, equal_to(true));
		});

		unit.test("IHaveConfigForProvidedSyscalls_conceptPassedConfigWithSingleInvalidSyscall_expectFalseIsReturned", []()
		{
			struct ConfigWithSingleInvalidSyscall
			{
				struct NonSyscallConfig
				{
					struct Handler
					{
						void onSyscall(DummyContext &)
						{
						}
					};
				};

				using ProvidedSyscalls = std::tuple<NonSyscallConfig>;
			};

			expect(IHaveConfigForProvidedSyscalls<ConfigWithSingleInvalidSyscall>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedSyscalls_conceptPassedConfigWithMultipleSyscalls_expectTrueIsReturned", []()
		{
			struct ConfigWithMultipleSyscalls
			{
				using ProvidedSyscalls = std::tuple<StubSyscallConfig<1>, StubSyscallConfig<2>, StubSyscallConfig<3>>;
			};

			expect(IHaveConfigForProvidedSyscalls<ConfigWithMultipleSyscalls>, equal_to(true));
		});

		unit.test("IHaveConfigForProvidedSyscalls_conceptPassedConfigWithMultipleSyscallsIncludingNonSyscallConfig_expectFalseIsReturned", []()
		{
			struct ConfigWithInvalidSyscall
			{
				struct NonSyscallConfig
				{
					struct Handler
					{
						void onSyscall(void)
						{
						}
					};
				};

				using ProvidedSyscalls = std::tuple<
					StubSyscallConfig<1>,
					StubSyscallConfig<2>,
					NonSyscallConfig,
					StubSyscallConfig<3>>;
			};

			expect(IHaveConfigForProvidedSyscalls<ConfigWithInvalidSyscall>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedSyscalls_conceptPassedConfigWithArrayOfSyscalls_expectFalseIsReturned", []()
		{
			struct ConfigWithArrayOfSyscalls
			{
				using ProvidedSyscalls = std::array<StubSyscallConfig<1>, 3>;
			};

			expect(IHaveConfigForProvidedSyscalls<ConfigWithArrayOfSyscalls>, equal_to(false));
		});

		unit.test("IHaveConfigForProvidedSyscalls_conceptPassedConfigWithPairOfSyscalls_expectFalseIsReturned", []()
		{
			struct ConfigWithPairOfSyscalls
			{
				using ProvidedSyscalls = std::pair<StubSyscallConfig<1>, StubSyscallConfig<2>>;
			};

			expect(IHaveConfigForProvidedSyscalls<ConfigWithPairOfSyscalls>, equal_to(false));
		});
	});
}
