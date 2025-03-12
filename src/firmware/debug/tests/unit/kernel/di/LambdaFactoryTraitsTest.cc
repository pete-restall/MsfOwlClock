#include <concepts>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/di/LambdaFactoryTraits.hh"

using namespace mettle;
using namespace smeg::kernel::di;

namespace smeg::tests::unit::kernel::di
{
	template <typename TLambda, typename TExpectedType>
	struct LambdaFactoryTypeIs
	{
		using Lambda = TLambda;
		using ExpectedType = TExpectedType;
	};

	struct Dummy
	{
	};

	static Dummy dummy;

	suite<
		LambdaFactoryTypeIs<decltype([]() -> auto { return 123; }), int>,
		LambdaFactoryTypeIs<decltype([]() -> auto { return "hello"; }), const char *>,
		LambdaFactoryTypeIs<decltype([]() -> auto & { return dummy; }), Dummy &>,
		LambdaFactoryTypeIs<decltype([]() -> const auto & { return dummy; }), const Dummy &>,
		LambdaFactoryTypeIs<decltype([]() -> const volatile Dummy * { return &dummy; }), const volatile Dummy *>,
		LambdaFactoryTypeIs<decltype([]() static -> auto { return 123; }), int>,
		LambdaFactoryTypeIs<decltype([]() static -> auto { return "hello"; }), const char *>,
		LambdaFactoryTypeIs<decltype([]() static -> auto & { return dummy; }), Dummy &>,
		LambdaFactoryTypeIs<decltype([]() static -> const auto & { return dummy; }), const Dummy &>,
		LambdaFactoryTypeIs<decltype([]() static -> const volatile Dummy * { return &dummy; }), const volatile Dummy *>> lambdaFactoryTraitsTest("LambdaFactoryTraits Test Suite", [](auto &unit)
	{
		unit.test("Type_get_expectTypeOfInstanceCreatedByFactoryIsReturned", [](auto fixture)
		{
			using Fixture = decltype(fixture);
			using Traits = LambdaFactoryTraits<typename Fixture::Lambda>;
			expect(typeid(Fixture).name(), std::same_as<typename Traits::Type, typename Fixture::ExpectedType>, equal_to(true));
		});
	});
}
