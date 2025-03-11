#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/di/ILambdaFactory.hh"

using namespace mettle;
using namespace smeg::kernel::di;

namespace smeg::tests::unit::kernel::di
{
	template <typename T>
	struct IsStaticLambdaFactory
	{
		using Type = T;
		static constexpr bool isStaticLambdaFactory = true;
	};

	template <typename T>
	struct IsNotStaticLambdaFactory
	{
		using Type = T;
		static constexpr bool isStaticLambdaFactory = false;
	};

	template <typename T>
	struct IsInstanceLambdaFactory
	{
		using Type = T;
		static constexpr bool isInstanceLambdaFactory = true;
	};

	template <typename T>
	struct IsNotInstanceLambdaFactory
	{
		using Type = T;
		static constexpr bool isInstanceLambdaFactory = false;
	};

	template <typename T>
	struct IsLambdaFactory
	{
		using Type = T;
		static constexpr bool isLambdaFactory = true;
	};

	template <typename T>
	struct IsNotLambdaFactory
	{
		using Type = T;
		static constexpr bool isLambdaFactory = false;
	};

	struct Dummy
	{
	};

	static Dummy dummy;

	suite<
		IsNotStaticLambdaFactory<decltype([]() -> auto { return 123; })>,
		IsNotStaticLambdaFactory<decltype([]() -> auto { return "hello"; })>,
		IsNotStaticLambdaFactory<decltype([]() -> auto & { return dummy; })>,
		IsNotStaticLambdaFactory<decltype([]() -> const auto & { return dummy; })>,
		IsNotStaticLambdaFactory<decltype([]() static { })>,
		IsStaticLambdaFactory<decltype([]() static -> auto { return 123; })>,
		IsStaticLambdaFactory<decltype([]() static -> auto { return "hello"; })>,
		IsStaticLambdaFactory<decltype([]() static -> auto & { return dummy; })>,
		IsStaticLambdaFactory<decltype([]() static -> const auto & { return dummy; })>> iStaticLambdaFactoryTest("IStaticLambdaFactory Test Suite", [](auto &unit)
	{
		unit.test("IStaticLambdaFactory_conceptPassedStaticLambdaFactorylikeType_expectTrueIsReturned", [](auto potentialFactory)
		{
			using Factory = decltype(potentialFactory);
			if constexpr (Factory::isStaticLambdaFactory)
				expect(typeid(typename Factory::Type).name(), IStaticLambdaFactory<typename Factory::Type>, equal_to(true));
		});

		unit.test("IStaticLambdaFactory_conceptPassedNonStaticLambdaFactorylikeType_expectFalseIsReturned", [](auto potentialFactory)
		{
			using Factory = decltype(potentialFactory);
			if constexpr (!Factory::isStaticLambdaFactory)
				expect(typeid(typename Factory::Type).name(), IStaticLambdaFactory<typename Factory::Type>, equal_to(false));
		});
	});

	suite<
		IsNotInstanceLambdaFactory<decltype([]() static -> auto { return 123; })>,
		IsNotInstanceLambdaFactory<decltype([]() static -> auto { return "hello"; })>,
		IsNotInstanceLambdaFactory<decltype([]() static -> auto & { return dummy; })>,
		IsNotInstanceLambdaFactory<decltype([]() static -> const auto & { return dummy; })>,
		IsNotInstanceLambdaFactory<decltype([]() { })>,
		IsInstanceLambdaFactory<decltype([]() -> auto { return 123; })>,
		IsInstanceLambdaFactory<decltype([]() -> auto { return "hello"; })>,
		IsInstanceLambdaFactory<decltype([]() -> auto & { return dummy; })>,
		IsInstanceLambdaFactory<decltype([]() -> const auto & { return dummy; })>> iInstanceLambdaFactoryTest("IInstanceLambdaFactory Test Suite", [](auto &unit)
	{
		unit.test("IInstanceLambdaFactory_conceptPassedInstanceLambdaFactorylikeType_expectTrueIsReturned", [](auto potentialFactory)
		{
			using Factory = decltype(potentialFactory);
			if constexpr (Factory::isInstanceLambdaFactory)
				expect(typeid(typename Factory::Type).name(), IInstanceLambdaFactory<typename Factory::Type>, equal_to(true));
		});

		unit.test("IInstanceLambdaFactory_conceptPassedNonInstanceLambdaFactorylikeType_expectFalseIsReturned", [](auto potentialFactory)
		{
			using Factory = decltype(potentialFactory);
			if constexpr (!Factory::isInstanceLambdaFactory)
				expect(typeid(typename Factory::Type).name(), IInstanceLambdaFactory<typename Factory::Type>, equal_to(false));
		});
	});

	suite<
		IsNotLambdaFactory<decltype([]() { })>,
		IsLambdaFactory<decltype([]() static -> auto { return 123; })>,
		IsLambdaFactory<decltype([]() static -> auto { return "hello"; })>,
		IsLambdaFactory<decltype([]() static -> auto & { return dummy; })>,
		IsLambdaFactory<decltype([]() static -> const auto & { return dummy; })>,
		IsLambdaFactory<decltype([]() -> auto { return 123; })>,
		IsLambdaFactory<decltype([]() -> auto { return "hello"; })>,
		IsLambdaFactory<decltype([]() -> auto & { return dummy; })>,
		IsLambdaFactory<decltype([]() -> const auto & { return dummy; })>> iLambdaFactoryTest("ILambdaFactory Test Suite", [](auto &unit)
	{
		unit.test("ILambdaFactory_conceptPassedLambdaFactorylikeType_expectTrueIsReturned", [](auto potentialFactory)
		{
			using Factory = decltype(potentialFactory);
			if constexpr (Factory::isLambdaFactory)
				expect(typeid(typename Factory::Type).name(), ILambdaFactory<typename Factory::Type>, equal_to(true));
		});

		unit.test("ILambdaFactory_conceptPassedNonLambdaFactorylikeType_expectFalseIsReturned", [](auto potentialFactory)
		{
			using Factory = decltype(potentialFactory);
			if constexpr (!Factory::isLambdaFactory)
				expect(typeid(typename Factory::Type).name(), ILambdaFactory<typename Factory::Type>, equal_to(false));
		});
	});
}
