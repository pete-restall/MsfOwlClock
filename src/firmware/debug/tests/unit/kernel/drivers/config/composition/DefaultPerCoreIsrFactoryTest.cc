#include <concepts>
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/IsrApis.hh"
#include "kernel/drivers/config/composition/DefaultPerCoreIsrFactory.hh"

#include "../../../../NonDeterminism.hh"

using namespace mettle;

using namespace smeg::kernel::drivers;
using namespace smeg::kernel::drivers::config::composition;

namespace smeg::tests::unit::kernel::drivers::config::composition
{
	struct DummyRequiredApi
	{
	};

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
	struct Dummy
	{
		using Apis = TApis<DummyRequiredApi>;
	};

	template <template <typename...> typename TApis>
	struct Stub
	{
		using Apis = TApis<StubRequiredApi>;
	};

	template <typename, std::size_t>
	struct StubPerCoreIsrWithDefaultConstructor
	{
		void onInterrupt(void) noexcept
		{
		}
	};

	template <typename, std::size_t, typename TRequiredApis>
	struct StubPerCoreIsrWithRequiredApisConstructor
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		RequiredApis apis;

		StubPerCoreIsrWithRequiredApisConstructor(RequiredApis &&apis) noexcept :
			apis(apis)
		{
		}

		void onInterrupt(void) noexcept
		{
		}
	};

	template <typename TConfig, std::size_t McuCoreId, typename TRequiredApis>
	using SpyPerCoreIsrWithRequiredApisConstructor = StubPerCoreIsrWithRequiredApisConstructor<TConfig, McuCoreId, TRequiredApis>;

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

	template <template <typename, std::size_t, typename...> typename TIsr, std::size_t McuCoreId, typename...>
	struct ConfigFor;

	template <template <typename, std::size_t> typename TIsr, std::size_t McuCoreId>
	struct ConfigFor<TIsr, McuCoreId>
	{
		using Handler = TIsr<ConfigFor<TIsr, McuCoreId>, McuCoreId>;
		static constexpr auto irq = 0;
	};

	template <template <typename, std::size_t, typename> typename TIsr, std::size_t McuCoreId, typename TRequiredApis>
	struct ConfigFor<TIsr, McuCoreId, TRequiredApis>
	{
		using Handler = TIsr<ConfigFor<TIsr, McuCoreId, TRequiredApis>, McuCoreId, TRequiredApis>;
		static constexpr auto irq = 0;
	};

	suite<Stub<IsrApis>> defaultPerCoreIsrFactoryTest("DefaultPerCoreIsrFactory (Default API Factory) Test Suite", [](auto &unit)
	{
		unit.test("createPerCoreIsr_calledWhenIsrHasNoRequiredApisAndHasDefaultConstructor_expectIsrCanBeCreated", [](auto)
		{
			constexpr std::size_t mcuCoreId = 7;
			using IsrConfig = ConfigFor<StubPerCoreIsrWithDefaultConstructor, mcuCoreId>;
			auto isr(DefaultPerCoreIsrFactory<IsrConfig, mcuCoreId>::createPerCoreIsr());
			auto isIsrExpectedType(typeid(isr) == typeid(StubPerCoreIsrWithDefaultConstructor<IsrConfig, mcuCoreId>));
			expect(isIsrExpectedType, equal_to(true));
		});

		unit.test("createPerCoreIsr_calledWhenIsrHasRequiredApisAndHasMatchingConstructor_expectIsrCanBeCreated", [](auto fixture)
		{
			constexpr std::size_t mcuCoreId = 4;
			using RequiredApis = decltype(fixture)::Apis;
			using IsrConfig = ConfigFor<StubPerCoreIsrWithRequiredApisConstructor, mcuCoreId, RequiredApis>;
			auto isr(DefaultPerCoreIsrFactory<IsrConfig, mcuCoreId>::createPerCoreIsr());
			auto isIsrExpectedType(typeid(isr) == typeid(StubPerCoreIsrWithRequiredApisConstructor<IsrConfig, mcuCoreId, RequiredApis>));
			expect(isIsrExpectedType, equal_to(true));
		});

		unit.test("createPerCoreIsr_called_expectSameInstanceOfApiIsReturnedForEachGet", [](auto fixture)
		{
			constexpr std::size_t mcuCoreId = 3;
			using RequiredApis = decltype(fixture)::Apis;
			using IsrConfig = ConfigFor<SpyPerCoreIsrWithRequiredApisConstructor, mcuCoreId, RequiredApis>;
			auto isr(DefaultPerCoreIsrFactory<IsrConfig, mcuCoreId>::createPerCoreIsr());
			std::array resolvedApiPtrs{&isr.apis.template get<StubRequiredApi>(), &isr.apis.template get<StubRequiredApi>()};
			expect(resolvedApiPtrs[0], equal_to(resolvedApiPtrs[1]));
		});
	});

	suite<Stub<IsrApis>> defaultPerCoreIsrFactoryWithSpecifiedApiFactoryTest("DefaultPerCoreIsrFactory (Specified API Factory) Test Suite", [](auto &unit)
	{
		unit.test("createPerCoreIsr_calledWhenIsrHasNoRequiredApisAndHasDefaultConstructor_expectIsrCanBeCreated", [](auto)
		{
			constexpr std::size_t mcuCoreId = 73;
			using IsrConfig = ConfigFor<StubPerCoreIsrWithDefaultConstructor, mcuCoreId>;
			auto isr(DefaultPerCoreIsrFactory<IsrConfig, mcuCoreId, StubApiFactory>::createPerCoreIsr());
			auto isIsrExpectedType(typeid(isr) == typeid(StubPerCoreIsrWithDefaultConstructor<IsrConfig, mcuCoreId>));
			expect(isIsrExpectedType, equal_to(true));
		});

		unit.test("createPerCoreIsr_calledWhenIsrHasRequiredApisAndHasMatchingConstructor_expectIsrIsCreatedWithApisFromFactory", [](auto fixture)
		{
			constexpr std::size_t mcuCoreId = 12;
			using RequiredApis = decltype(fixture)::Apis;
			using IsrConfig = ConfigFor<SpyPerCoreIsrWithRequiredApisConstructor, mcuCoreId, RequiredApis>;
			auto isr(DefaultPerCoreIsrFactory<IsrConfig, mcuCoreId, StubApiFactory>::createPerCoreIsr());
			auto resolvedApi(isr.apis.template get<StubRequiredApi>());
			expect(resolvedApi.token, equal_to(StubApiFactory<IsrConfig, mcuCoreId, StubRequiredApi>::token));
		});

		unit.test("createPerCoreIsr_called_expectSameInstanceOfApiIsReturnedForEachGet", [](auto fixture)
		{
			constexpr std::size_t mcuCoreId = 2;
			using RequiredApis = decltype(fixture)::Apis;
			using IsrConfig = ConfigFor<SpyPerCoreIsrWithRequiredApisConstructor, mcuCoreId, RequiredApis>;
			auto isr(DefaultPerCoreIsrFactory<IsrConfig, mcuCoreId, StubApiFactory>::createPerCoreIsr());
			std::array resolvedApiPtrs{&isr.apis.template get<StubRequiredApi>(), &isr.apis.template get<StubRequiredApi>()};
			expect(resolvedApiPtrs[0], equal_to(resolvedApiPtrs[1]));
		});
	});
}
