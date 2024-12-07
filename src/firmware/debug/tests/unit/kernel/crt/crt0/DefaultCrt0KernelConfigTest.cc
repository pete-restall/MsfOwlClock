#include <array>
#include <concepts>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/crt0/DefaultCrt0KernelConfig.hh"
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

	template <auto NumberOfMcuCores>
	struct StubMcuCoreTraits
	{
		static constexpr auto numberOfMcuCores = NumberOfMcuCores;

		static constexpr auto getMcuCoreId(void) noexcept
		{
			return 0;
		}
	};

	using DummyMcuCoreTraits = StubMcuCoreTraits<4>;

	template <typename T>
	struct StackMemorySection
	{
		using AsTuple = std::tuple<typename T::Stack::MemorySection>;
	};

	template <typename T>
	using AllStacksMemorySections = typename TupleProjection<T, StackMemorySection>::Output;

	struct DummyMemorySection
	{
	};

	struct StubMemorySection
	{
	};

	struct StubDriverConfig
	{
		using ProvidedApis = std::tuple<>;
	};

	using DummyDriverConfigs = std::tuple<>;

	using StubDriverConfigs = std::tuple<StubDriverConfig>;

	suite<> defaultCrt0KernelConfigTest("DefaultCrt0KernelConfig Test Suite", [](auto &unit)
	{
		unit.test("Tasks_getNumberOfElementsInTuple_expectSameAsNumberOfCores", []()
		{
			expect(std::tuple_size_v<typename DefaultCrt0KernelConfig<StubMcuCoreTraits<1>, 0, DummyMemorySection, DummyDriverConfigs>::Tasks>, equal_to(1));
			expect(std::tuple_size_v<typename DefaultCrt0KernelConfig<StubMcuCoreTraits<2>, 0, DummyMemorySection, DummyDriverConfigs>::Tasks>, equal_to(2));
			expect(std::tuple_size_v<typename DefaultCrt0KernelConfig<StubMcuCoreTraits<10>, 0, DummyMemorySection, DummyDriverConfigs>::Tasks>, equal_to(10));
		});

		unit.test("Tasks_getStackNumberOfSlots_expectEachIsSameAsTemplateArgument", []()
		{
			expect(allStacksNumberOfSlots(typename DefaultCrt0KernelConfig<StubMcuCoreTraits<1>, 123, DummyMemorySection, DummyDriverConfigs>::Tasks{}), array(123));
			expect(allStacksNumberOfSlots(typename DefaultCrt0KernelConfig<StubMcuCoreTraits<2>, 456, DummyMemorySection, DummyDriverConfigs>::Tasks{}), array(456, 456));
			expect(allStacksNumberOfSlots(typename DefaultCrt0KernelConfig<StubMcuCoreTraits<3>, 789, DummyMemorySection, DummyDriverConfigs>::Tasks{}), array(789, 789, 789));
		});

		unit.test("Tasks_getStackMemorySections_expectEachIsPlacedInMemorySectionPassedAsTemplateArgument", []()
		{
			expect(
				std::same_as<
					AllStacksMemorySections<typename DefaultCrt0KernelConfig<StubMcuCoreTraits<1>, 0, StubMemorySection, DummyDriverConfigs>::Tasks>,
					std::tuple<StubMemorySection>>,
				equal_to(true));

			expect(
				std::same_as<
					AllStacksMemorySections<typename DefaultCrt0KernelConfig<StubMcuCoreTraits<3>, 0, StubMemorySection, DummyDriverConfigs>::Tasks>,
					std::tuple<
						StubMemorySection,
						StubMemorySection,
						StubMemorySection>>,
				equal_to(true));
		});

		unit.test("Drivers_get_expectSameTypeAsTemplateArgument", []()
		{
			expect(
				std::same_as<
					typename DefaultCrt0KernelConfig<DummyMcuCoreTraits, 0, DummyMemorySection, StubDriverConfigs>::Drivers,
					StubDriverConfigs>,
				equal_to(true));
		});

		unit.test("McuCoreTraits_get_expectSameTypeAsTemplateArgument", []()
		{
			expect(
				std::same_as<
					typename DefaultCrt0KernelConfig<DummyMcuCoreTraits, 0, DummyMemorySection, DummyDriverConfigs>::McuCoreTraits,
					DummyMcuCoreTraits>,
				equal_to(true));
		});
	});
}
