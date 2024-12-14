#include <concepts>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/DefaultPerCoreApiFactory.hh"

using namespace mettle;

using namespace smeg::kernel;

namespace smeg::tests::unit::kernel
{
	struct DummyConfig
	{
	};

	suite<> defaultPerCoreApiFactoryTest("DefaultPerCoreApiFactory Test Suite", [](auto &unit)
	{
		unit.test("createApi_calledWhenTypeIsInTuple_expectInstanceCreatedByDefaultConstructor", []()
		{
			struct A { };
			struct B { };
			struct C { };
			constexpr std::size_t mcuCoreId = 7;
			const DefaultPerCoreApiFactory<DummyConfig, mcuCoreId, A, B, C> factory;
			auto createdInstance(factory.template createApi<B>());
			expect(std::same_as<B, decltype(createdInstance)>, equal_to(true));
		});

		unit.test("createApi_testNoExceptWhenDefaultConstructorIsNoExcept_expectTrueIsReturned", []()
		{
			struct ApiConstructorIsNoExcept
			{
				ApiConstructorIsNoExcept(void) noexcept
				{
				}
			};

			constexpr std::size_t mcuCoreId = 14;
			const DefaultPerCoreApiFactory<DummyConfig, mcuCoreId, ApiConstructorIsNoExcept> factory;
			expect(noexcept(factory.template createApi<ApiConstructorIsNoExcept>()), equal_to(true));
		});

		unit.test("createApi_testNoExceptWhenDefaultConstructorIsNotNoExcept_expectFalseIsReturned", []()
		{
			struct ApiConstructorCanThrow
			{
				ApiConstructorCanThrow(void)
				{
					throw "this constructor can (and will...) throw";
				}
			};

			constexpr std::size_t mcuCoreId = 21;
			const DefaultPerCoreApiFactory<DummyConfig, mcuCoreId, ApiConstructorCanThrow> factory;
			expect(noexcept(factory.template createApi<ApiConstructorCanThrow>()), equal_to(false));
		});
	});
}
