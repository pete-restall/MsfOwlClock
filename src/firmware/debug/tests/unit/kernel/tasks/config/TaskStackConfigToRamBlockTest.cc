#include <cstdint>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/config/dsl/DefaultMemorySection.hh"
#include "kernel/tasks/config/IHaveConfigForTasks.hh"
#include "kernel/tasks/config/ResourceToTaskAssociation.hh"
#include "kernel/tasks/config/TaskStackConfigsFrom.hh"
#include "kernel/tasks/config/TaskStackConfigToRamBlock.hh"
#include "kernel/tuples/TupleProjection.hh"

#include "DummyTask.hh"

using namespace mettle;

using namespace smeg::kernel::tasks::config;
using namespace smeg::kernel::tasks::config::dsl;
using namespace smeg::kernel::tuples;

namespace smeg::tests::unit::kernel::tasks::config
{
	template <typename TStackConfig>
	struct TaskWith
	{
		using Type = DummyTask<0>;
		using Stack = TStackConfig;
	};

	template <typename TStackConfig>
	struct OverlaidTaskWith
	{
		using Types = std::tuple<DummyTask<1>, DummyTask<2>, DummyTask<3>, DummyTask<5>>;
		using Stack = TStackConfig;
	};

	struct DummyMemorySection
	{
	};

	template <auto NumberOfSlots>
	struct StackConfigWithMemorySection
	{
		static constexpr auto numberOfSlots = NumberOfSlots;
		using MemorySection = DummyMemorySection;
	};

	template <auto NumberOfSlots>
	struct StackConfigWithoutMemorySection
	{
		static constexpr auto numberOfSlots = NumberOfSlots;
	};

	template <auto Value>
	struct StubTaskStackNumberOfSlotsFor
	{
		template <typename TConfig, typename TTaskStackConfig>
		struct Stub
		{
			static constexpr auto value = Value;
		};
	};

	template <typename TConfig, typename TTaskStackConfig>
	using DummyTaskStackNumberOfSlotsFor = typename StubTaskStackNumberOfSlotsFor<1>::Stub<TConfig, TTaskStackConfig>;

	template <typename TConfig, template <typename, typename> typename TTaskStackNumberOfSlotsFor = DummyTaskStackNumberOfSlotsFor>
	struct FixtureFor
	{
		template <typename TTaskStackConfig, auto StackIndex>
		using TaskStackConfigToRamBlockForStubConfig = TaskStackConfigToRamBlock<TConfig, TTaskStackConfig, StackIndex, TTaskStackNumberOfSlotsFor>;

		using ProjectedTupleOfRamBlocks = TupleProjection<typename TaskStackConfigsFrom<TConfig>::PerStack, TaskStackConfigToRamBlockForStubConfig>::Output;
	};

	suite<> taskStackConfigToRamBlockWithMemorySectionTest("TaskStackConfigToRamBlock (with MemorySection) Test Suite", [](auto &unit)
	{
		struct Config
		{
			using Tasks = std::tuple<TaskWith<StackConfigWithMemorySection<123>>>;
		};

		unit.test("TaskStackRamBlock_projected_expectRamBlockHasSameConfig", []()
		{
			using Projection = typename FixtureFor<Config>::ProjectedTupleOfRamBlocks;
			using ProjectedConfig = typename std::tuple_element_t<0, Projection>::Config;
			expect(typeid(ProjectedConfig) == typeid(Config), equal_to(true));
		});

		unit.test("TaskStackRamBlock_projected_expectRamBlockHasSameMemorySection", []()
		{
			using Projection = typename FixtureFor<Config>::ProjectedTupleOfRamBlocks;
			using ProjectedMemorySection = typename std::tuple_element_t<0, Projection>::MemorySection;
			expect(typeid(ProjectedMemorySection) == typeid(DummyMemorySection), equal_to(true));
		});

		unit.test("TaskStackRamBlock_projected_expectRamBlockNumberOfSlotsIsFromTemplateArgumentTTaskStackNumberOfSlotsFor", []()
		{
			constexpr auto expectedNumberOfSlots = 873897;
			using Projection = typename FixtureFor<Config, StubTaskStackNumberOfSlotsFor<expectedNumberOfSlots>::Stub>::ProjectedTupleOfRamBlocks;
			using ProjectedRamBlock = typename std::tuple_element_t<0, Projection>;
			expect(ProjectedRamBlock::numberOfSlots, equal_to(expectedNumberOfSlots));
		});

		unit.test("TaskStackRamBlock_projected_expectRamBlockStackIdsCorrespondsToElementPositionsInTuple", []()
		{
			struct Config
			{
				using Tasks = std::tuple<
					TaskWith<StackConfigWithMemorySection<123>>,
					OverlaidTaskWith<StackConfigWithMemorySection<456>>,
					TaskWith<StackConfigWithMemorySection<789>>>;
			};

			using Projection = typename FixtureFor<Config>::ProjectedTupleOfRamBlocks;
			std::array stackIds
			{
				std::tuple_element_t<0, Projection>::stackId,
				std::tuple_element_t<1, Projection>::stackId,
				std::tuple_element_t<2, Projection>::stackId
			};
			expect(stackIds, array(0, 1, 2));
		});
	});

	suite<> taskStackConfigToRamBlockWithoutMemorySectionTest("TaskStackConfigToRamBlock (without MemorySection) Test Suite", [](auto &unit)
	{
		struct Config
		{
			using Tasks = std::tuple<TaskWith<StackConfigWithoutMemorySection<456>>>;
		};

		unit.test("TaskStackRamBlock_projected_expectRamBlockHasSameConfig", []()
		{
			using Projection = typename FixtureFor<Config>::ProjectedTupleOfRamBlocks;
			using ProjectedConfig = typename std::tuple_element_t<0, Projection>::Config;
			expect(typeid(ProjectedConfig) == typeid(Config), equal_to(true));
		});

		unit.test("TaskStackRamBlock_projected_expectRamBlockWithDefaultMemorySection", []()
		{
			using Projection = typename FixtureFor<Config>::ProjectedTupleOfRamBlocks;
			using ProjectedMemorySection = typename std::tuple_element_t<0, Projection>::MemorySection;
			expect(typeid(ProjectedMemorySection) == typeid(DefaultMemorySection), equal_to(true));
		});

		unit.test("TaskStackRamBlock_projected_expectRamBlockNumberOfSlotsIsFromTemplateArgumentTTaskStackNumberOfSlotsFor", []()
		{
			constexpr auto expectedNumberOfSlots = 1265782;
			using Projection = typename FixtureFor<Config, StubTaskStackNumberOfSlotsFor<expectedNumberOfSlots>::Stub>::ProjectedTupleOfRamBlocks;
			using ProjectedRamBlock = typename std::tuple_element_t<0, Projection>;
			expect(ProjectedRamBlock::numberOfSlots, equal_to(expectedNumberOfSlots));
		});

		unit.test("TaskStackRamBlock_projected_expectRamBlockStackIdsCorrespondsToElementPositionsInTuple", []()
		{
			struct Config
			{
				using Tasks = std::tuple<
					OverlaidTaskWith<StackConfigWithoutMemorySection<123>>,
					TaskWith<StackConfigWithoutMemorySection<456>>,
					TaskWith<StackConfigWithoutMemorySection<789>>>;
			};

			using Projection = typename FixtureFor<Config>::ProjectedTupleOfRamBlocks;
			std::array stackIds
			{
				std::tuple_element_t<2, Projection>::stackId,
				std::tuple_element_t<1, Projection>::stackId,
				std::tuple_element_t<0, Projection>::stackId
			};
			expect(stackIds, array(2, 1, 0));
		});
	});
}
