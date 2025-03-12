#include <concepts>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/di/LambdaFactoryRegistration.hh"

using namespace mettle;
using namespace smeg::kernel::di;

namespace smeg::tests::unit::kernel::di
{
	struct DummyKey
	{
	};

	struct Dummy
	{
	};

	static Dummy dummy;

	suite<> lambdaFactoryRegistrationStaticLambdaTest("LambdaFactoryRegistration (Static Lambda) Test Suite", [](auto &unit)
	{
		unit.test("Type_get_expectReturnTypeOfLambda", []()
		{
			auto lambda([]() static -> auto & { return dummy; });
			using Registration = LambdaFactoryRegistration<DummyKey, decltype(lambda)>;
			Registration factory(lambda);
			expect(std::same_as<typename Registration::Type, Dummy &>, equal_to(true));
		});

		unit.test("create_called_expectInstanceFromLambdaIsReturned", []()
		{
			auto lambda([]() static -> auto & { return dummy; });
			LambdaFactoryRegistration<DummyKey, decltype(lambda)> factory(lambda);
			expect(&factory.create(), equal_to(&dummy));
		});
	});

	suite<> lambdaFactoryRegistrationInstanceLambdaTest("LambdaFactoryRegistration (Instance Lambda) Test Suite", [](auto &unit)
	{
		unit.test("Type_get_expectReturnTypeOfLambda", []()
		{
			auto lambda([]() -> auto & { return dummy; });
			using Registration = LambdaFactoryRegistration<DummyKey, decltype(lambda)>;
			Registration factory(lambda);
			expect(std::same_as<typename Registration::Type, Dummy &>, equal_to(true));
		});

		unit.test("create_called_expectInstanceFromLambdaIsReturned", []()
		{
			Dummy dummyLocal;
			auto lambda([&dummyLocal]() -> auto & { return dummyLocal; });
			LambdaFactoryRegistration<DummyKey, decltype(lambda)> factory(lambda);
			expect(&factory.create(), equal_to(&dummyLocal));
		});
	});
}
