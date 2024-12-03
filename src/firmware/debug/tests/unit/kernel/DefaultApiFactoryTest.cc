#include <concepts>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/DefaultApiFactory.hh"

using namespace mettle;

using namespace smeg::kernel;

namespace smeg::tests::unit::kernel
{
	struct DummyConfig
	{
	};

	suite<> defaultApiFactoryTest("DefaultApiFactory Test Suite", [](auto &unit)
	{
		unit.test("createApi_calledWhenTypeIsInTuple_expectInstanceCreatedByDefaultConstructor", []()
		{
			struct A { };
			struct B { };
			struct C { };
			const DefaultApiFactory<DummyConfig, A, B, C> factory;
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

			const DefaultApiFactory<DummyConfig, ApiConstructorIsNoExcept> factory;
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

			const DefaultApiFactory<DummyConfig, ApiConstructorCanThrow> factory;
			expect(noexcept(factory.template createApi<ApiConstructorCanThrow>()), equal_to(false));
		});
	});
}
