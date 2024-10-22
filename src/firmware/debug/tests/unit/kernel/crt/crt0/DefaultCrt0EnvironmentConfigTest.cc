#include <array>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/DefaultCrt0EnvironmentConfig.hh"
#include "kernel/crt/crt0/IsrStackMemorySection.hh"
#include "kernel/tuples/TupleProjection.hh"

using namespace mettle;

using namespace smeg::kernel::crt::crt0;
using namespace smeg::kernel::tuples;

namespace smeg::tests::unit::kernel::crt::crt0
{
	template <typename... T>
	static auto allStacksNumberOfSlots(std::tuple<T...>)
	{
		return std::array{(T::Stack::numberOfSlots) ...};
	}

	template <typename T, auto N>
	static auto allStacksNumberOfSlots(std::array<T, N> tasks)
	{
		return allStacksNumberOfSlots(std::tuple_cat(tasks));
	}

	template <typename T>
	struct StackMemorySection
	{
		using AsTuple = std::tuple<typename T::Stack::MemorySection>;
	};

	template <typename T>
	using AllStacksMemorySections = typename TupleProjection<T, StackMemorySection>::Output;

	suite<> defaultCrt0EnvironmentConfigTest("DefaultCrt0EnvironmentConfig Test Suite", [](auto &unit)
	{
		unit.test("Tasks_getNumberOfElementsInTuple_expectSameAsNumberOfCores", []()
		{
			expect(std::tuple_size_v<typename DefaultCrt0EnvironmentConfig<1, 0>::Tasks>, equal_to(1));
			expect(std::tuple_size_v<typename DefaultCrt0EnvironmentConfig<2, 0>::Tasks>, equal_to(2));
			expect(std::tuple_size_v<typename DefaultCrt0EnvironmentConfig<10, 0>::Tasks>, equal_to(10));
		});

		unit.test("Tasks_getStackNumberOfSlots_expectEachIsSameAsTemplateArgument", []()
		{
			expect(allStacksNumberOfSlots(typename DefaultCrt0EnvironmentConfig<1, 123>::Tasks{}), array(123));
			expect(allStacksNumberOfSlots(typename DefaultCrt0EnvironmentConfig<2, 456>::Tasks{}), array(456, 456));
			expect(allStacksNumberOfSlots(typename DefaultCrt0EnvironmentConfig<3, 789>::Tasks{}), array(789, 789, 789));
		});

		unit.test("Tasks_getStackMemorySections_expectEachIsPlacedInSpaceReservedForNestedInterruptHandlers", []()
		{
			expect(
				typeid(AllStacksMemorySections<typename DefaultCrt0EnvironmentConfig<1, 0>::Tasks>) == typeid(std::tuple<IsrStackMemorySection>),
				equal_to(true));

			expect(
				typeid(AllStacksMemorySections<typename DefaultCrt0EnvironmentConfig<3, 0>::Tasks>) == typeid(std::tuple<
					IsrStackMemorySection,
					IsrStackMemorySection,
					IsrStackMemorySection>),
				equal_to(true));
		});
	});
}
