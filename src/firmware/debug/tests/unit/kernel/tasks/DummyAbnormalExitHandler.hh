#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_DUMMYABNORMALEXITHANDLER_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_DUMMYABNORMALEXITHANDLER_HH
#include <exception>
#include "kernel/Exception.hh"

namespace smeg::tests::unit::kernel::tasks
{
	using namespace smeg::kernel;

	class DummyAbnormalExitHandler
	{
	public:
		bool onException(const Exception &) noexcept
		{
			return false;
		}

		bool onException(const std::exception &) noexcept
		{
			return false;
		}

		bool onUnknownException(void) noexcept
		{
			return false;
		}
	};
}

#endif
