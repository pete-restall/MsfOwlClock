#ifndef __RESTALL_MSFOWLCLOCK_APPCONFIG_HH
#define __RESTALL_MSFOWLCLOCK_APPCONFIG_HH
#include "kernel/config/dsl.hh"
#include "config/Tasks.hh"

namespace smeg::config
{
	struct AppConfig
	{
		// TODO:
		// AppConfig will want to be loaded in isolation so that the kernel can be self-contained as a bootloader.  To do this, a stub
		// extern method will need to be linked with the app code so that the kernel can call it for initialisation if the bootloader
		// is not invoked.  This should also allow the potentially arduous compile-time evaluation of the config to be built relatively
		// infrequently, if all the parsing, etc. is done in a single translation unit (or module, when those become available).
		using Tasks = std::tuple<
			Tasks::FirstTask,
			Tasks::AnOverlay>;
	};
}

#endif