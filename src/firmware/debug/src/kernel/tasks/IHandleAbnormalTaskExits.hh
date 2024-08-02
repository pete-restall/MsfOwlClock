#ifndef __SMEG_KERNEL_TASKS_IHANDLEABNORMALTASKEXITS_HH
#define __SMEG_KERNEL_TASKS_IHANDLEABNORMALTASKEXITS_HH
#include <concepts>
#include <exception>
#include "../Exception.hh"

namespace smeg::kernel::tasks
{
	template <typename T>
	concept IHandleAbnormalTaskExits = requires(T &handler, const std::exception &stdException, Exception smegException)
	{
		{ handler.onException(smegException) } noexcept -> std::convertible_to<bool>;
		{ handler.onException(stdException) } noexcept -> std::convertible_to<bool>;
		{ handler.onUnknownException() } noexcept -> std::convertible_to<bool>;
	};
}

#endif
