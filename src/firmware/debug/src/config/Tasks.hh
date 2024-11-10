#ifndef __RESTALL_MSFOWLCLOCK_CONFIG_TASKS_HH
#define __RESTALL_MSFOWLCLOCK_CONFIG_TASKS_HH
#include <cstddef>
#include <tuple>

#include "../kernel/public/config.hh"

namespace restall::msf_owl_clock::debug { struct NopTask { void run(void) {  } }; } // TODO: TEMPORARY DEBUGGING...

namespace restall::msf_owl_clock::config
{
	// TODO: Just some rubber-ducking of potential task declarations...

	struct Tasks
	{
		template <std::size_t N, typename TMemorySection = DefaultMemorySection> // TODO: Include this (TaskStack) from the kernel via the public 'config.hh' header ?
		struct TaskStack
		{
			static constexpr std::size_t numberOfSlots = N;
			using MemorySection = TMemorySection;
		};

		struct FirstTask
		{
			using Type = restall::msf_owl_clock::debug::NopTask;
			using Stack = TaskStack<32>;
		};
/*
		struct AnOverlay
		{
			using Types = std::tuple<app::SecondTask, app::ThirdTask>;
			using Stack = TaskStack<32, RetainedMemorySection>;
		};
*/
	};
}

#endif
