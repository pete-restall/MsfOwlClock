#include <array>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/config/TaskStackConfigToRamBlock.hh"

using namespace mettle;

using namespace smeg::kernel::tasks::config;

namespace smeg::tests::unit::kernel::tasks::config
{
	struct DummyConfig
	{
		using Tasks = std::tuple<>;
	};

	struct DummyMemorySection
	{
	};

	template <auto N>
	using RamBlockWithStackid = TaskStackRamBlock<DummyConfig, N, DummyMemorySection, 1>;

	template <auto N>
	using RamBlockWithNumberOfSlots = TaskStackRamBlock<DummyConfig, 0, DummyMemorySection, N>;

	suite<> taskStackRamBlockTest("TaskStackRamBlock Test Suite", [](auto &unit)
	{
		unit.test("Config_get_expectSameConfigAsTemplateArgument", []()
		{
			using RamBlock = TaskStackRamBlock<DummyConfig, 0, DummyMemorySection, 1>;
			expect(typeid(typename RamBlock::Config) == typeid(DummyConfig), equal_to(true));
		});

		unit.test("MemorySection_get_expectSameMemorySectionAsTemplateArgument", []()
		{
			using RamBlock = TaskStackRamBlock<DummyConfig, 0, DummyMemorySection, 1>;
			expect(typeid(typename RamBlock::MemorySection) == typeid(DummyMemorySection), equal_to(true));
		});

		unit.test("stackId_get_expectSameValueAsTemplateArgument", []()
		{
			expect(RamBlockWithStackid<0>::stackId, equal_to(0));
			expect(RamBlockWithStackid<35>::stackId, equal_to(35));
			expect(RamBlockWithStackid<167529>::stackId, equal_to(167529));
		});

		unit.test("numberOfSlots_get_expectSameValueAsTemplateArgument", []()
		{
			expect(RamBlockWithNumberOfSlots<1>::numberOfSlots, equal_to(1));
			expect(RamBlockWithNumberOfSlots<13>::numberOfSlots, equal_to(13));
			expect(RamBlockWithNumberOfSlots<871>::numberOfSlots, equal_to(871));
		});

		unit.test("ramBlock_get_expectArrayOfUnsigned32BitIntegersForSpecifiedNumberOfSlots", []()
		{
			expect(typeid(RamBlockWithNumberOfSlots<1>::ramBlock) == typeid(std::array<std::uint32_t, 1>), equal_to(true));
			expect(typeid(RamBlockWithNumberOfSlots<2>::ramBlock) == typeid(std::array<std::uint32_t, 2>), equal_to(true));
			expect(typeid(RamBlockWithNumberOfSlots<1871>::ramBlock) == typeid(std::array<std::uint32_t, 1871>), equal_to(true));
		});
	});
}
