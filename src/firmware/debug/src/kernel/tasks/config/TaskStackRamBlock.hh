#ifndef __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKRAMBLOCK_HH
#define __SMEG_KERNEL_TASKS_CONFIG_TASKSTACKRAMBLOCK_HH
#include <array>
#include <cstdint>
#include <cstddef>

#include "IHaveConfigForTasks.hh"

namespace smeg::kernel::tasks::config
{
	template <IHaveConfigForTasks TConfig, std::size_t StackId, typename TMemorySection, std::size_t NumberOfSlots>
	struct TaskStackRamBlock
	{
		static_assert(NumberOfSlots > 0, "Task Stack's block of RAM cannot be degenerate; it must have at least one slot");

		using Config = TConfig;
		using MemorySection = TMemorySection;
		static constexpr auto stackId = StackId;
		static constexpr auto numberOfSlots = NumberOfSlots;
		static std::array<std::uint32_t, NumberOfSlots> ramBlock;
	};
}

namespace smeg::config
{
	struct AppConfig;
	struct KernelConfig;
}

#define DEFINE_TASK_STACK_LINKER_SECTION_FOR(TConfig, TMemorySection, linkerSectionName) \
	namespace smeg::kernel::tasks::config \
	{ \
		template <std::size_t StackId, std::size_t NumberOfSlots> \
		struct TaskStackRamBlock<TConfig, StackId, TMemorySection, NumberOfSlots> \
		{ \
			static std::array<std::uint32_t, NumberOfSlots> ramBlock; \
		}; \
		\
		template <std::size_t StackId, std::size_t NumberOfSlots> \
		[[gnu::section(linkerSectionName)]] \
		std::array<std::uint32_t, NumberOfSlots> TaskStackRamBlock<TConfig, StackId, TMemorySection, NumberOfSlots>::ramBlock; \
	}

#define DEFINE_TASK_STACK_LINKER_SECTION_FOR_KERNEL(TMemorySection, linkerSectionName) \
	DEFINE_TASK_STACK_LINKER_SECTION_FOR(::smeg::config::KernelConfig, TMemorySection, linkerSectionName)

#define DEFINE_TASK_STACK_LINKER_SECTION_FOR_APP(TMemorySection, linkerSectionName) \
	DEFINE_TASK_STACK_LINKER_SECTION_FOR(::smeg::config::AppConfig, TMemorySection, linkerSectionName)

#endif
