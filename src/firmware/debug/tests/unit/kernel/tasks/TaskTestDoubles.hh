#ifndef __SMEG_TESTS_UNIT_KERNEL_TASKS_TASKTESTDOUBLES_HH
#define __SMEG_TESTS_UNIT_KERNEL_TASKS_TASKTESTDOUBLES_HH
#include <stdexcept>
#include <type_traits>
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

	template <typename TRequiredApis>
	struct StubTaskWithRequiredApisAndDefaultConstructor
	{
		using RequiredApis = TRequiredApis;

		void run(void)
		{
		}
	};

	template <typename TRequiredApis>
	struct StubTaskWithRequiredApisConstructor
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		StubTaskWithRequiredApisConstructor(RequiredApis &&)
		{
		}

		void run(void)
		{
		}
	};

	template <typename TRequiredApis>
	struct MockTaskWithBothDefaultAndRequiredApisConstructors
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		bool wasDefaultConstructorCalled;
		bool wasRequiredApisConstructorCalled;

		MockTaskWithBothDefaultAndRequiredApisConstructors(void) :
			wasDefaultConstructorCalled(true),
			wasRequiredApisConstructorCalled(false)
		{
		}

		MockTaskWithBothDefaultAndRequiredApisConstructors(RequiredApis &&) :
			wasDefaultConstructorCalled(false),
			wasRequiredApisConstructorCalled(true)
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

	template <typename TException, typename TRequiredApis>
	struct StubTaskConstructorRequiringApisToThrow
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		static const char *what(void)
		{
			static auto value =
				nameof<TException>() + " thrown from " +
				nameof<StubTaskConstructorRequiringApisToThrow>() + "::ctor(" + nameof<RequiredApis>() + " &)";

			return value.c_str();
		}

		StubTaskConstructorRequiringApisToThrow(RequiredApis &&)
		{
			throw TException(what());
		}

		void run(void)
		{
		}
	};

	template <typename TRequiredApis>
	struct StubTaskConstructorRequiringApisToThrow<StubUnknownException, TRequiredApis>
	{
		using RequiredApis = std::remove_cvref_t<TRequiredApis>;

		StubTaskConstructorRequiringApisToThrow(RequiredApis &&)
		{
		}

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
