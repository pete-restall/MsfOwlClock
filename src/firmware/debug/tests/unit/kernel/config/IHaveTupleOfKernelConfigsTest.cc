#include <array>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/config/IHaveTupleOfKernelConfigs.hh"

using namespace mettle;

using namespace smeg::kernel::config;

namespace smeg::tests::unit::kernel::config
{
	template <auto X>
	struct StubKernelConfig
	{
		using Drivers = std::tuple<>;
	};

	struct StubNonKernelConfig
	{
	};

	suite<> iHaveTupleOfKernelConfigsTest("IHaveTupleOfKernelConfigs Test Suite", [](auto &unit)
	{
		unit.test("IHaveTupleOfKernelConfigs_conceptPassedClassWithoutTuple_expectFalseIsReturned", []()
		{
			struct ClassWithoutTuple
			{
			};

			expect(IHaveTupleOfKernelConfigs<ClassWithoutTuple>, equal_to(false));
		});

		unit.test("IHaveTupleOfKernelConfigs_conceptPassedClassWithEmptyTuple_expectTrueIsReturned", []()
		{
			struct ClassWithEmptyTuple
			{
				using AsTuple = std::tuple<>;
			};

			expect(IHaveTupleOfKernelConfigs<ClassWithEmptyTuple>, equal_to(true));
		});

		unit.test("IHaveTupleOfKernelConfigs_conceptPassedClassWithSingleProvidedKernelConfig_expectTrueIsReturned", []()
		{
			struct ClassWithSingleKernelConfig
			{
				using AsTuple = std::tuple<StubKernelConfig<1>>;
			};

			expect(IHaveTupleOfKernelConfigs<ClassWithSingleKernelConfig>, equal_to(true));
		});

		unit.test("IHaveTupleOfKernelConfigs_conceptPassedClassWithSingleInvalidKernelConfig_expectFalseIsReturned", []()
		{
			struct ClassWithSingleInvalidKernelConfig
			{
				using AsTuple = std::tuple<StubNonKernelConfig>;
			};

			expect(IHaveTupleOfKernelConfigs<ClassWithSingleInvalidKernelConfig>, equal_to(false));
		});

		unit.test("IHaveTupleOfKernelConfigs_conceptPassedClassWithMultipleTuple_expectTrueIsReturned", []()
		{
			struct ClassWithMultipleTuple
			{
				using AsTuple = std::tuple<StubKernelConfig<1>, StubKernelConfig<2>, StubKernelConfig<3>>;
			};

			expect(IHaveTupleOfKernelConfigs<ClassWithMultipleTuple>, equal_to(true));
		});

		unit.test("IHaveTupleOfKernelConfigs_conceptPassedClassWithMultipleTupleIncludingNonKernelConfig_expectFalseIsReturned", []()
		{
			struct ClassWithInvalidKernelConfig
			{
				using AsTuple = std::tuple<StubKernelConfig<1>, StubKernelConfig<2>, StubNonKernelConfig, StubKernelConfig<3>>;
			};

			expect(IHaveTupleOfKernelConfigs<ClassWithInvalidKernelConfig>, equal_to(false));
		});

		unit.test("IHaveTupleOfKernelConfigs_conceptPassedClassWithArrayOfKernelConfigs_expectFalseIsReturned", []()
		{
			struct ClassWithArrayOfKernelConfigs
			{
				using AsTuple = std::array<StubKernelConfig<1>, 3>;
			};

			expect(IHaveTupleOfKernelConfigs<ClassWithArrayOfKernelConfigs>, equal_to(false));
		});

		unit.test("IHaveTupleOfKernelConfigs_conceptPassedClassWithPairOfKernelConfigs_expectFalseIsReturned", []()
		{
			struct ClassWithPairOfKernelConfigs
			{
				using AsTuple = std::pair<StubKernelConfig<1>, StubKernelConfig<2>>;
			};

			expect(IHaveTupleOfKernelConfigs<ClassWithPairOfKernelConfigs>, equal_to(false));
		});
	});
}
