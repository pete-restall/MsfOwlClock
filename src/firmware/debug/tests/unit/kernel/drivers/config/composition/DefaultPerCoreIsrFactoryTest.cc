#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/IsrApis.hh"
#include "kernel/drivers/config/composition/DefaultPerCoreIsrFactory.hh"

#include "../../../../NonDeterminism.hh"
#include "../../PerCoreIsrTestDoubles.hh"

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

		StubRequiredApi(void) :
			token(0)
		{
		}

		StubRequiredApi(int token) :
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

	template <typename... TRequiredApis>
	struct DummyApiFactory
	{
		template <typename T>
		constexpr auto createApi(void) const;
	};

	template <typename TRequiredApis>
	struct SpyPerCoreIsrWithRequiredApisConstructor
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		RequiredApis apis;

		SpyPerCoreIsrWithRequiredApisConstructor(RequiredApis &&apis) noexcept :
			apis(apis)
		{
		}

		void onInterrupt(void) noexcept
		{
		}
	};

	template <typename TConfig, typename... TRequiredApis>
	struct StubApiFactory
	{
		template <typename T>
		constexpr auto createApi(void) const
		{
			if constexpr (std::same_as<T, StubRequiredApi>)
				return StubRequiredApi(token);
			else
				throw std::runtime_error("StubApiFactory.create<T>() is only stubbed for T=StubRequiredApi");
		}

		static thread_local int token;
	};

	template <typename TConfig, typename... TRequiredApis>
	thread_local int StubApiFactory<TConfig, TRequiredApis...>::token(anyValueOf<int>());

	template <typename TIsr>
	struct ConfigFor
	{
		using Handler = TIsr;
		static constexpr auto irq = 0;
	};

	static constexpr auto DummyMcuCoreId = 0;

	suite<Stub<IsrApis>> defaultPerCoreIsrFactoryTest("DefaultPerCoreIsrFactory (Default API Factory) Test Suite", [](auto &unit)
	{
		unit.test("createPerCoreIsr_calledWhenIsrHasNoRequiredApisAndHasDefaultConstructor_expectIsrCanBeCreated", [](auto)
		{
			using IsrConfig = ConfigFor<StubPerCoreIsrWithDefaultConstructor>;
			auto isr(DefaultPerCoreIsrFactory<IsrConfig, DummyMcuCoreId>::createPerCoreIsr());
			auto isIsrExpectedType(typeid(isr) == typeid(StubPerCoreIsrWithDefaultConstructor));
			expect(isIsrExpectedType, equal_to(true));
		});

		unit.test("createPerCoreIsr_calledWhenIsrHasRequiredApisAndHasMatchingConstructor_expectIsrCanBeCreated", [](auto fixture)
		{
			using StubIsr = StubPerCoreIsrWithRequiredApisConstructor<typename decltype(fixture)::Apis>;
			auto isr(DefaultPerCoreIsrFactory<ConfigFor<StubIsr>, DummyMcuCoreId>::createPerCoreIsr());
			auto isIsrExpectedType(typeid(isr) == typeid(StubIsr));
			expect(isIsrExpectedType, equal_to(true));
		});

		unit.test("createPerCoreIsr_called_expectSameInstanceOfApiIsReturnedForEachGet", [](auto fixture)
		{
			using SpyIsr = SpyPerCoreIsrWithRequiredApisConstructor<typename decltype(fixture)::Apis>;
			auto isr(DefaultPerCoreIsrFactory<ConfigFor<SpyIsr>, DummyMcuCoreId>::createPerCoreIsr());
			std::array resolvedApiPtrs{&isr.apis.template get<StubRequiredApi>(), &isr.apis.template get<StubRequiredApi>()};
			expect(resolvedApiPtrs[0], equal_to(resolvedApiPtrs[1]));
		});
	});

	suite<Stub<IsrApis>> defaultPerCoreIsrFactoryWithSpecifiedApiFactoryTest("DefaultPerCoreIsrFactory (Specified API Factory) Test Suite", [](auto &unit)
	{
		unit.test("createPerCoreIsr_calledWhenIsrHasNoRequiredApisAndHasDefaultConstructor_expectIsrCanBeCreated", [](auto)
		{
			using IsrConfig = ConfigFor<StubPerCoreIsrWithDefaultConstructor>;
			auto isr(DefaultPerCoreIsrFactory<IsrConfig, DummyMcuCoreId, DummyApiFactory>::createPerCoreIsr());
			auto isIsrExpectedType(typeid(isr) == typeid(StubPerCoreIsrWithDefaultConstructor));
			expect(isIsrExpectedType, equal_to(true));
		});

		unit.test("createPerCoreIsr_calledWhenIsrHasRequiredApisAndHasMatchingConstructor_expectIsrIsCreatedWithApisFromFactory", [](auto fixture)
		{
			using SpyIsr = SpyPerCoreIsrWithRequiredApisConstructor<typename decltype(fixture)::Apis>;
			using Config = ConfigFor<SpyIsr>;
			auto isr(DefaultPerCoreIsrFactory<Config, DummyMcuCoreId, StubApiFactory>::createPerCoreIsr());
			auto resolvedApi(isr.apis.template get<StubRequiredApi>());
			expect(resolvedApi.token, equal_to(StubApiFactory<Config, StubRequiredApi>::token));
		});

		unit.test("createPerCoreIsr_called_expectSameInstanceOfApiIsReturnedForEachGet", [](auto fixture)
		{
			using SpyIsr = SpyPerCoreIsrWithRequiredApisConstructor<typename decltype(fixture)::Apis>;
			auto isr(DefaultPerCoreIsrFactory<ConfigFor<SpyIsr>, DummyMcuCoreId, StubApiFactory>::createPerCoreIsr());
			std::array resolvedApiPtrs{&isr.apis.template get<StubRequiredApi>(), &isr.apis.template get<StubRequiredApi>()};
			expect(resolvedApiPtrs[0], equal_to(resolvedApiPtrs[1]));
		});
	});
}
