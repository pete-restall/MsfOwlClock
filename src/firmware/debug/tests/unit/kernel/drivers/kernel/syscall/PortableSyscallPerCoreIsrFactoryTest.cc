#include <concepts>
#include <cstddef>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/IHandleSyscall.hh"
#include "kernel/drivers/ISyscallApi.hh"
#include "kernel/drivers/SyscallApis.hh"
#include "kernel/drivers/kernel/syscall/PortableSyscallPerCoreIsrFactory.hh"

using namespace mettle;

using namespace smeg::kernel;
using namespace smeg::kernel::drivers;
using namespace smeg::kernel::drivers::kernel::syscall;

namespace smeg::tests::unit::kernel::drivers::kernel::syscall
{
	struct StubRequiredApi
	{
		const int token;

		StubRequiredApi(void) noexcept :
			token(0)
		{
		}

		StubRequiredApi(int token) noexcept :
			token(token)
		{
		}
	};

	template <template <typename...> typename TApis>
	struct Stub
	{
		using Apis = TApis<StubRequiredApi>;
	};

	template <typename, std::size_t, typename...>
	struct DummyApiFactory
	{
		template <typename T>
		constexpr T createApi(void) const noexcept
		{
			return T();
		}
	};

	static constexpr auto DummyMcuCoreId = 0;

	struct DummyIsrConfig
	{
		struct Handler
		{
			static void onInterrupt(void) noexcept
			{
			}
		};

		static constexpr auto irq = 0;
	};

	template <typename TConfig, std::size_t>
	struct DummyHandlerFactory
	{
		static auto createSyscallHandler(void) noexcept
		{
			return typename TConfig::Handler();
		}
	};

	using DummyHandlerConfigs = std::tuple<>;

	template <IHandleSyscallWithAnyArg THandler>
	struct HandlerConfigFor
	{
		using Handler = THandler;
	};

	struct DummySyscallContext
	{
	};

	struct DummySyscallArg
	{
	};

	template <auto>
	struct DummyHandler
	{
		void onSyscall(DummySyscallContext &, DummySyscallArg &)
		{
		}
	};

	suite<> portableSyscallPerCoreIsrFactoryTest("PortableSyscallPerCoreIsrFactory Test Suite", [](auto &unit)
	{
		unit.test("createPortableSyscallPerCoreIsr_testedForExceptions_expectQualifiedWithNoexcept", []()
		{
			using Factory = PortableSyscallPerCoreIsrFactory<
				DummyIsrConfig,
				DummyMcuCoreId,
				DummyApiFactory,
				DummyHandlerFactory,
				DummyHandlerConfigs>;

			expect(noexcept(Factory::createPortableSyscallPerCoreIsr()), equal_to(true));
		});

		unit.test("createPortableSyscallPerCoreIsr_calledWhenNoHandlerConfigs_expectInstanceOfIsrWithEmptyTupleOfHandlersIsReturned", []()
		{
			using NoHandlerConfigs = std::tuple<>;
			using Factory = PortableSyscallPerCoreIsrFactory<
				DummyIsrConfig,
				DummyMcuCoreId,
				DummyApiFactory,
				DummyHandlerFactory,
				NoHandlerConfigs>;

			using ReturnedIsr = decltype(Factory::createPortableSyscallPerCoreIsr());
			expect(std::same_as<ReturnedIsr, PortableSyscallPerCoreIsr<std::tuple<>>>, equal_to(true));
		});

		unit.test("createPortableSyscallPerCoreIsr_calledWhenHandlerConfigs_expectInstanceOfIsrWithTupleOfHandlersIsReturned", []()
		{
			using Handlers = std::tuple<DummyHandler<-17>, DummyHandler<2>, DummyHandler<0>>;
			using HandlerConfigs = std::tuple<
				HandlerConfigFor<std::tuple_element_t<0, Handlers>>,
				HandlerConfigFor<std::tuple_element_t<1, Handlers>>,
				HandlerConfigFor<std::tuple_element_t<2, Handlers>>>;

			using Factory = PortableSyscallPerCoreIsrFactory<
				DummyIsrConfig,
				DummyMcuCoreId,
				DummyApiFactory,
				DummyHandlerFactory,
				HandlerConfigs>;

			using ReturnedIsr = decltype(Factory::createPortableSyscallPerCoreIsr());
			expect(std::same_as<ReturnedIsr, PortableSyscallPerCoreIsr<Handlers>>, equal_to(true));
		});
	});
}
