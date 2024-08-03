#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_STUBEXCEPTIONS_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_STUBEXCEPTIONS_HH
#include <exception>
#include "kernel/Exception.hh"

namespace smeg::tests::unit::kernel::tasks
{
	using namespace smeg::kernel;

	template <typename TBase>
	class StubExceptionWithBase : public TBase
	{
	private:
		const char *whatPtr;

	public:
		StubExceptionWithBase(void) : StubExceptionWithBase("StubExceptionWithBase")
		{
		}

		StubExceptionWithBase(const char *whatPtr) :
			whatPtr(whatPtr)
		{
		}

		StubExceptionWithBase(const StubExceptionWithBase<TBase> &other) :
			whatPtr(other.whatPtr)
		{
		}

		StubExceptionWithBase<TBase> &operator=(const StubExceptionWithBase<TBase> &other)
		{
			this->whatPtr = other.whatPtr;
			return *this;
		}

		virtual const char *what(void) const noexcept override
		{
			return this->whatPtr;
		}
	};

	using StubSmegException = StubExceptionWithBase<Exception>;

	using StubStandardException = StubExceptionWithBase<std::exception>;

	class StubUnknownException
	{
	};
}

#endif
