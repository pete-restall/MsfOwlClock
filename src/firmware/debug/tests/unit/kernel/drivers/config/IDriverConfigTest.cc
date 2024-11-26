#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IDriverConfig.hh"

using namespace mettle;

using namespace smeg::kernel::drivers::config;
using namespace smeg::kernel::tasks;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct DummyClass
	{
	};

	struct DummyApiConfig
	{
		template <typename... T>
		struct Interface
		{
		};

		struct Type
		{
		};
	};

	struct DummyIsrConfig
	{
		struct Handler
		{
			static void onInterrupt(void) noexcept
			{
			}
		};
	};

	struct DummySyscallConfig
	{
		struct Type
		{
		};

		struct Handler
		{
			void onSyscall(DummyClass &)
			{
			}
		};
	};

	struct DummyTaskConfig
	{
		struct Type
		{
			void run(void)
			{
			}
		};

		struct Stack
		{
			static constexpr auto numberOfSlots = 0;
		};
	};

	struct DriverConfigWithOnlyProvidedApis
	{
		using ProvidedApis = std::tuple<>;
	};

	struct DriverConfigWithInvalidProvidedApis
	{
		using ProvidedApis = std::tuple<DummyClass>;
	};

	struct DriverConfigWithOnlyProvidedIsrs
	{
		using ProvidedIsrs = std::tuple<>;
	};

	struct DriverConfigWithInvalidProvidedIsrs
	{
		using ProvidedIsrs = std::tuple<DummyClass>;
	};

	struct DriverConfigWithOnlyProvidedSyscalls
	{
		using ProvidedSyscalls = std::tuple<>;
	};

	struct DriverConfigWithInvalidProvidedSyscalls
	{
		using ProvidedSyscalls = std::tuple<DummyClass>;
	};

	struct DriverConfigWithOnlyTasks
	{
		using Tasks = std::tuple<>;
	};

	struct DriverConfigWithInvalidTasks
	{
		using Tasks = std::tuple<DummyClass>;
	};

	struct DriverConfigWithAllRecognisedMembers
	{
		using ProvidedApis = std::tuple<DummyApiConfig>;
		using ProvidedIsrs = std::tuple<DummyIsrConfig>;
		using ProvidedSyscalls = std::tuple<DummySyscallConfig>;
		using Tasks = std::tuple<DummyTaskConfig>;
	};

	struct DriverConfigWithNoRecognisedMembers
	{
		using Type = DummyClass;
		using ProvidedMagic = DummyClass;
	};

	suite<> idriverConfigTest("IDriverConfig Test Suite", [](auto &unit)
	{
		unit.test("IDriverConfig_conceptPassedConfigWithOnlyProvidedApis_expectTrueIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithOnlyProvidedApis>, equal_to(true));
		});

		unit.test("IDriverConfig_conceptPassedConfigWithInvalidProvidedApis_expectFalseIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithInvalidProvidedApis>, equal_to(false));
		});

		unit.test("IDriverConfig_conceptPassedConfigWithOnlyProvidedIsrs_expectTrueIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithOnlyProvidedIsrs>, equal_to(true));
		});

		unit.test("IDriverConfig_conceptPassedConfigWithInvalidProvidedIsrs_expectFalseIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithInvalidProvidedIsrs>, equal_to(false));
		});

		unit.test("IDriverConfig_conceptPassedConfigWithOnlyProvidedSyscalls_expectTrueIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithOnlyProvidedSyscalls>, equal_to(true));
		});

		unit.test("IDriverConfig_conceptPassedConfigWithInvalidProvidedSyscalls_expectFalseIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithInvalidProvidedSyscalls>, equal_to(false));
		});

		unit.test("IDriverConfig_conceptPassedConfigWithOnlyTasks_expectTrueIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithOnlyTasks>, equal_to(true));
		});

		unit.test("IDriverConfig_conceptPassedConfigWithInvalidTasks_expectFalseIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithInvalidTasks>, equal_to(false));
		});

		unit.test("IDriverConfig_conceptPassedValidConfigWithAllRecognisedMembers_expectTrueIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithAllRecognisedMembers>, equal_to(true));
		});

		unit.test("IDriverConfig_conceptPassedValidConfigWithNoRecognisedMembers_expectFalseIsReturned", []()
		{
			expect(IDriverConfig<DriverConfigWithNoRecognisedMembers>, equal_to(false));
		});
	});
}
