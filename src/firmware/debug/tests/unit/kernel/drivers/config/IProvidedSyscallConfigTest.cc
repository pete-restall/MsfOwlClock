#include <type_traits>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/config/IProvidedSyscallConfig.hh"

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

	template <typename... T>
	struct FromPairFixture;

	template <typename TContext, typename TSyscall>
	struct FromPairFixture<std::pair<TContext, TSyscall>>
	{
		using Context = TContext;
		using Syscall = TSyscall;
	};

	suite<
		std::pair<DummyContext, DummySyscall>,
		std::pair<const DummyContext, DummySyscall>,
		std::pair<DummyContext, const DummySyscall>,
		std::pair<const DummyContext, const DummySyscall>
	> iprovidedSyscallConfigValidConfigsTest("IProvidedSyscallConfig (Valid Configs) Test Suite", [](auto &unit)
	{
		unit.test("IProvidedSyscallConfig_conceptPassedValidSyscallWithStructArgumentConfig_expectTrueIsReturned", [](auto &fixture)
		{
			using TContext = FromPairFixture<std::decay_t<decltype(fixture)>>::Context;
			using TSyscall = FromPairFixture<std::decay_t<decltype(fixture)>>::Syscall;

			struct ValidSyscallConfig
			{
				struct Handler
				{
					void onSyscall(TContext &, TSyscall &)
					{
					}
				};
			};

			expect(IProvidedSyscallConfig<ValidSyscallConfig>, equal_to(true));
		});
	});

	struct SyscallWithNoHandlerConfig
	{
		static constexpr auto reason = "SyscallWithNoHandlerConfig";
	};

	struct SyscallWithNoArgConfig
	{
		static constexpr auto reason = "SyscallWithNoArgConfig";

		struct Handler
		{
			void onSyscall(DummyContext &)
			{
			}
		};
	};

	template <typename T>
	struct SyscallWithNonStructArgConfig
	{
		static constexpr auto reason = "SyscallWithNonStructArgConfig";

		struct Handler
		{
			void onSyscall(DummyContext &, T)
			{
			}
		};
	};

	struct SyscallWithStaticHandlerConfig
	{
		static constexpr auto reason = "SyscallWithStaticHandlerConfig";

		struct Handler
		{
			static void onSyscall(DummyContext &, DummySyscall &)
			{
			}
		};
	};

	struct SyscallWithRvalueContextConfig
	{
		static constexpr auto reason = "SyscallWithRvalueContextConfig";

		struct Handler
		{
			void onSyscall(DummyContext &&, DummySyscall &)
			{
			}
		};
	};

	struct SyscallWithNonReferenceContextConfig
	{
		static constexpr auto reason = "SyscallWithNonReferenceContextConfig";

		struct Handler
		{
			void onSyscall(DummyContext, DummySyscall &)
			{
			}
		};
	};

	struct SyscallWithRvalueArgConfig
	{
		static constexpr auto reason = "SyscallWithRvalueArgConfig";

		struct Handler
		{
			void onSyscall(DummyContext &, DummySyscall &&)
			{
			}
		};
	};

	struct SyscallWithNonReferenceArgConfig
	{
		static constexpr auto reason = "SyscallWithNonReferenceArgConfig";

		struct Handler
		{
			void onSyscall(DummyContext &, DummySyscall)
			{
			}
		};
	};

	suite<
		SyscallWithNoHandlerConfig,
		SyscallWithNoArgConfig,
		SyscallWithNonStructArgConfig<int>,
		SyscallWithNonStructArgConfig<float>,
		SyscallWithNonStructArgConfig<bool>,
		SyscallWithStaticHandlerConfig,
		SyscallWithRvalueContextConfig,
		SyscallWithNonReferenceContextConfig,
		SyscallWithRvalueArgConfig,
		SyscallWithNonReferenceArgConfig
	> iprovidedSyscallConfigInvalidConfigsTest("IProvidedSyscallConfig (Invalid Configs) Test Suite", [](auto &unit)
	{
		unit.test("IProvidedSyscallConfig_conceptPassedInvalidSyscallConfig_expectFalseIsReturned", [](auto &fixture)
		{
			using InvalidSyscallConfig = std::decay_t<decltype(fixture)>;
			expect(InvalidSyscallConfig::reason, IProvidedSyscallConfig<InvalidSyscallConfig>, equal_to(false));
		});
	});
}
