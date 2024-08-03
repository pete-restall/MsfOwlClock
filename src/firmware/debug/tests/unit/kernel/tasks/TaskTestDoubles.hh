#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_TASKTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_TASKTESTDOUBLES_HH
#include <stdexcept>
#include "../../TypeUtilities.hh"
#include "StubExceptions.hh"

namespace smeg::tests::unit::kernel::tasks
{
	struct StubTaskWithDefaultConstructor
	{
		void run(void)
		{
		}
	};

	template <typename TKernelApi>
	struct StubTaskWithKernelApiConstructor
	{
		StubTaskWithKernelApiConstructor(TKernelApi &&)
		{
		}

		void run(void)
		{
		}
	};

	template <typename TKernelApi>
	struct MockTaskWithBothDefaultAndKernelApiConstructors
	{
		bool wasDefaultConstructorCalled;
		bool wasKernelApiConstructorCalled;

		MockTaskWithBothDefaultAndKernelApiConstructors(void) :
			wasDefaultConstructorCalled(true),
			wasKernelApiConstructorCalled(false)
		{
		}

		MockTaskWithBothDefaultAndKernelApiConstructors(TKernelApi &&) :
			wasDefaultConstructorCalled(false),
			wasKernelApiConstructorCalled(true)
		{
		}

		void run(void)
		{
		}
	};

	template <typename TException>
	struct StubTaskDefaultConstructorToThrow
	{
		static const char *what(void)
		{
			static auto value = nameof<TException>() + " thrown from " + nameof<StubTaskDefaultConstructorToThrow>() + "::ctor()";
			return value.c_str();
		}

		StubTaskDefaultConstructorToThrow(void)
		{
			throw TException(what());
		}

		void run(void)
		{
		}
	};

	template <>
	struct StubTaskDefaultConstructorToThrow<StubUnknownException>
	{
		StubTaskDefaultConstructorToThrow(void)
		{
			throw StubUnknownException();
		}

		void run(void)
		{
		}
	};

	template <typename TException, typename TKernelApi>
	struct StubTaskKernelApiConstructorToThrow
	{
		static const char *what(void)
		{
			static auto value =
				nameof<TException>() + " thrown from " +
				nameof<StubTaskKernelApiConstructorToThrow>() + "::ctor(" + nameof<TKernelApi>() + " &)";

			return value.c_str();
		}

		StubTaskKernelApiConstructorToThrow(TKernelApi &&)
		{
			throw TException(what());
		}

		void run(void)
		{
		}
	};

	template <typename TKernelApi>
	struct StubTaskKernelApiConstructorToThrow<StubUnknownException, TKernelApi>
	{
		void run(void)
		{
			throw StubUnknownException();
		}
	};

	template <typename TException>
	struct StubTaskDestructorToThrow
	{
		static const char *what(void)
		{
			static auto value = nameof<TException>() + " thrown from " + nameof<StubTaskDestructorToThrow>() + "::dtor()";
			return value.c_str();
		}

		~StubTaskDestructorToThrow(void) noexcept(false)
		{
			throw TException(what());
		}

		void run(void)
		{
		}
	};

	template <>
	struct StubTaskDestructorToThrow<StubUnknownException>
	{
		~StubTaskDestructorToThrow(void) noexcept(false)
		{
			throw StubUnknownException();
		}

		void run(void)
		{
		}
	};

	template <typename TException>
	struct StubTaskRunToThrow
	{
		static const char *what(void)
		{
			static auto value = nameof<TException>() + " thrown from " + nameof<StubTaskRunToThrow>() + "::run()";
			return value.c_str();
		}

		void run(void)
		{
			throw TException(what());
		}
	};

	template <>
	struct StubTaskRunToThrow<StubUnknownException>
	{
		void run(void)
		{
			throw StubUnknownException();
		}
	};

	class StubBooleanTaskToRunGivenNumberOfTimes
	{
	private:
		const int &numberOfRunsBeforeFalseReturned;
		int &numberOfRuns;

	public:
		StubBooleanTaskToRunGivenNumberOfTimes(const int &numberOfRunsBeforeFalseReturned, int &numberOfRuns) :
			numberOfRunsBeforeFalseReturned(numberOfRunsBeforeFalseReturned),
			numberOfRuns(numberOfRuns)
		{
		}

		bool run(void)
		{
			if (this->numberOfRuns == this->numberOfRunsBeforeFalseReturned)
				throw std::runtime_error("Stubbed task was run more times than its limit; limit=" + this->numberOfRunsBeforeFalseReturned);

			return ++this->numberOfRuns < this->numberOfRunsBeforeFalseReturned;
		}
	};

	template <typename TException>
	class StubVoidTaskToThrowAfterGivenNumberOfTimes
	{
	private:
		const int &numberOfRunsBeforeExceptionThrown;
		int &numberOfRuns;

	public:
		StubVoidTaskToThrowAfterGivenNumberOfTimes(const int &numberOfRunsBeforeExceptionThrown, int &numberOfRuns) :
			numberOfRunsBeforeExceptionThrown(numberOfRunsBeforeExceptionThrown),
			numberOfRuns(numberOfRuns)
		{
		}

		void run(void)
		{
			if (++this->numberOfRuns >= this->numberOfRunsBeforeExceptionThrown)
			{
				this->numberOfRuns = 0;
				throw TException();
			}
		}
	};

	template <typename TException>
	class StubBooleanTaskToThrowAfterGivenNumberOfTimes
	{
	private:
		const int &numberOfRunsBeforeExceptionThrown;
		int &numberOfRuns;

	public:
		StubBooleanTaskToThrowAfterGivenNumberOfTimes(const int &numberOfRunsBeforeExceptionThrown, int &numberOfRuns) :
			numberOfRunsBeforeExceptionThrown(numberOfRunsBeforeExceptionThrown),
			numberOfRuns(numberOfRuns)
		{
		}

		bool run(void)
		{
			if (++this->numberOfRuns >= this->numberOfRunsBeforeExceptionThrown)
			{
				this->numberOfRuns = 0;
				throw TException();
			}

			return true;
		}
	};
}

#endif
