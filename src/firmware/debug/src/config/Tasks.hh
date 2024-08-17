#ifndef __RESTALL_MSFOWLCLOCK_CONFIG_TASKS_HH
#define __RESTALL_MSFOWLCLOCK_CONFIG_TASKS_HH
#include <tuple>
#include "../kernel/confing/dsl.hh"

namespace restall::msf_owl_clock::config
{
	struct Tasks
	{
		// TODO: Just some rubber-ducking of potential task declarations...
		struct FirstTask
		{
			using Type = app::FirstTask;
			using Stack = DefaultTaskStack<32>;
		};

		struct AnOverlay
		{
			using Types = std::tuple<SecondTask, ThirdTask>;
			using Stack = DefaultTaskStack<32>;
		};
	};
}

#endif
