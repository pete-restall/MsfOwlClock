#include <concepts>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/SyscallApis.hh"
#include "kernel/drivers/kernel/syscall/DefaultSyscallHandlerFactory.hh"

#include "../../../../NonDeterminism.hh"

using namespace mettle;

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

	struct DummySyscallContext
	{
	};

	struct DummySyscallArg
	{
	};

	template <typename, std::size_t>
	struct StubSyscallWithDefaultConstructor
	{
		void onSyscall(DummySyscallContext &, DummySyscallArg &)
		{
		}
	};

	template <typename, std::size_t, typename TRequiredApis>
	struct StubSyscallWithRequiredApisConstructor
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		RequiredApis apis;

		StubSyscallWithRequiredApisConstructor(RequiredApis &&apis) noexcept :
			apis(apis)
		{
		}

		void onSyscall(DummySyscallContext &, DummySyscallArg &)
		{
		}
	};

	template <typename TConfig, std::size_t McuCoreId, typename TRequiredApis>
	using SpySyscallWithRequiredApisConstructor = StubSyscallWithRequiredApisConstructor<TConfig, McuCoreId, TRequiredApis>;

	template <typename, std::size_t, typename... TRequiredApis>
	struct StubApiFactory
	{
		template <typename T>
		constexpr auto createApi(void) const noexcept(std::same_as<T, StubRequiredApi>)
		{
			if constexpr (std::same_as<T, StubRequiredApi>)
				return StubRequiredApi(token);
			else
				throw std::runtime_error("StubApiFactory.create<T>() is only stubbed for T=StubRequiredApi");
		}

		static thread_local inline int token = anyValueOf<int>();
	};

	template <typename TSyscallConfig, std::size_t McuCoreId, typename... TRequiredApis>
	using DummyApiFactory = StubApiFactory<TSyscallConfig, McuCoreId, TRequiredApis...>;

	template <template <typename, std::size_t, typename...> typename TSyscall, std::size_t McuCoreId, typename...>
	struct ConfigFor;

	template <template <typename, std::size_t> typename TSyscall, std::size_t McuCoreId>
	struct ConfigFor<TSyscall, McuCoreId>
	{
		using Handler = TSyscall<ConfigFor<TSyscall, McuCoreId>, McuCoreId>;
	};

	template <template <typename, std::size_t, typename> typename TSyscall, std::size_t McuCoreId, typename TRequiredApis>
	struct ConfigFor<TSyscall, McuCoreId, TRequiredApis>
	{
		using Handler = TSyscall<ConfigFor<TSyscall, McuCoreId, TRequiredApis>, McuCoreId, TRequiredApis>;
	};

	suite<Stub<SyscallApis>> defaultSyscallHandlerFactoryTest("DefaultSyscallHandlerFactory Test Suite", [](auto &unit)
	{
		unit.test("createSyscallHandler_testedForExceptions_expectQualifiedWithNoexcept", [](auto)
		{
			constexpr std::size_t mcuCoreId = 3;
			using DummySyscallConfig = ConfigFor<StubSyscallWithDefaultConstructor, mcuCoreId>;
			using Factory = DefaultSyscallHandlerFactory<DummySyscallConfig, mcuCoreId, DummyApiFactory>;
			expect(noexcept(Factory::createSyscallHandler()), equal_to(true));
		});

		unit.test("createSyscallHandler_calledWhenSyscallHasNoRequiredApisAndHasDefaultConstructor_expectSyscallCanBeCreated", [](auto)
		{
			constexpr std::size_t mcuCoreId = 73;
			using SyscallConfig = ConfigFor<StubSyscallWithDefaultConstructor, mcuCoreId>;
			auto syscall(DefaultSyscallHandlerFactory<SyscallConfig, mcuCoreId, StubApiFactory>::createSyscallHandler());
			auto isSyscallExpectedType(typeid(syscall) == typeid(StubSyscallWithDefaultConstructor<SyscallConfig, mcuCoreId>));
			expect(isSyscallExpectedType, equal_to(true));
		});

		unit.test("createSyscallHandler_calledWhenSyscallHasRequiredApisAndHasMatchingConstructor_expectSyscallIsCreatedWithApisFromFactory", [](auto fixture)
		{
			constexpr std::size_t mcuCoreId = 12;
			using RequiredApis = decltype(fixture)::Apis;
			using SyscallConfig = ConfigFor<SpySyscallWithRequiredApisConstructor, mcuCoreId, RequiredApis>;
			auto syscall(DefaultSyscallHandlerFactory<SyscallConfig, mcuCoreId, StubApiFactory>::createSyscallHandler());
			auto resolvedApi(syscall.apis.template get<StubRequiredApi>());
			expect(resolvedApi.token, equal_to(StubApiFactory<SyscallConfig, mcuCoreId, StubRequiredApi>::token));
		});

		unit.test("createSyscallHandler_called_expectSameInstanceOfApiIsReturnedForEachGet", [](auto fixture)
		{
			constexpr std::size_t mcuCoreId = 2;
			using RequiredApis = decltype(fixture)::Apis;
			using SyscallConfig = ConfigFor<SpySyscallWithRequiredApisConstructor, mcuCoreId, RequiredApis>;
			auto syscall(DefaultSyscallHandlerFactory<SyscallConfig, mcuCoreId, StubApiFactory>::createSyscallHandler());
			std::array resolvedApiPtrs{&syscall.apis.template get<StubRequiredApi>(), &syscall.apis.template get<StubRequiredApi>()};
			expect(resolvedApiPtrs[0], equal_to(resolvedApiPtrs[1]));
		});
	});
}
