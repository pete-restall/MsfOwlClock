#include <atomic>
#include <exception>
#include <stdexcept>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/Exception.hh"
#include "kernel/tasks/TaskLifecycle.hh"

#include "../../CallRecorder.hh"
#include "../../NonDeterminism.hh"
#include "../../ViewUtilities.hh"
#include "AbnormalExitHandlerTestDoubles.hh"
#include "StubExceptions.hh"
#include "TaskTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel;
using namespace smeg::kernel::tasks;

namespace smeg::tests::unit::kernel::tasks
{
	class Fixture
	{
	private:
		using CallCountInt = CallRecorder<>::CallCountInt;
		std::atomic<CallCountInt> callSequence;
		AbnormalExitHandlerTestDoubles abnormalExitHandlerTestDoubles;

	public:
		Fixture() :
			callSequence(0),
			abnormalExitHandlerTestDoubles(this->callSequence)
		{
		}

		DummyAbnormalExitHandler dummyAbnormalExitHandler(void)
		{
			return this->abnormalExitHandlerTestDoubles.dummy();
		}

		AbnormalExitHandlerSubstitute stubAbnormalExitHandlerToReturnFalseWhenCalledGivenNumberOfTimes(int numberOfTimes)
		{
			return this->abnormalExitHandlerTestDoubles
				.stub()
				.stubOnExceptionReturnValue<const Exception &>(true, numberOfTimes - 1)
				.stubOnExceptionReturnValue<const Exception &>(false)
				.stubOnExceptionReturnValue<const std::exception &>(true, numberOfTimes - 1)
				.stubOnExceptionReturnValue<const std::exception &>(false)
				.stubOnUnknownExceptionReturnValue(true, numberOfTimes - 1)
				.stubOnUnknownExceptionReturnValue(false);
		}

		AbnormalExitHandlerSubstitute mockAbnormalExitHandler(void)
		{
			return this->abnormalExitHandlerTestDoubles.mock();
		}

		AbnormalExitHandlerSubstitute mockAbnormalExitHandlerWithAllStubbedToReturn(bool returnValue)
		{
			return (*this)
				.mockAbnormalExitHandler()
				.stubOnExceptionReturnValue<const Exception &>(returnValue)
				.stubOnExceptionReturnValue<const std::exception &>(returnValue)
				.stubOnUnknownExceptionReturnValue(returnValue);
		}
	};

	template <typename TTask>
	struct StubDefaultConstructorTaskFactoryFor
	{
		static TTask createTask(void)
		{
			return TTask();
		}
	};

	struct StubBooleanTaskToRunGivenNumberOfTimesTaskFactory
	{
		thread_local static int numberOfRunsBeforeFalseReturned;
		thread_local static int numberOfRuns;

		static auto createTask(void)
		{
			return StubBooleanTaskToRunGivenNumberOfTimes(numberOfRunsBeforeFalseReturned, numberOfRuns);
		}
	};

	thread_local int StubBooleanTaskToRunGivenNumberOfTimesTaskFactory::numberOfRunsBeforeFalseReturned(0);
	thread_local int StubBooleanTaskToRunGivenNumberOfTimesTaskFactory::numberOfRuns(0);

	template <typename TException, typename TReturn>
	struct StubTaskToThrowWhenCalledGivenNumberOfTimesTaskFactory
	{
		thread_local static int numberOfRunsBeforeExceptionThrown;
		thread_local static int numberOfRuns;

		static auto createTask(void)
		{
			if constexpr (std::is_void_v<TReturn>)
				return StubVoidTaskToThrowAfterGivenNumberOfTimes<TException>(numberOfRunsBeforeExceptionThrown, numberOfRuns);
			else
				return StubBooleanTaskToThrowAfterGivenNumberOfTimes<TException>(numberOfRunsBeforeExceptionThrown, numberOfRuns);
		}
	};

	template <typename TException, typename TReturn>
	thread_local int StubTaskToThrowWhenCalledGivenNumberOfTimesTaskFactory<TException, TReturn>::numberOfRunsBeforeExceptionThrown(0);

	template <typename TException, typename TReturn>
	thread_local int StubTaskToThrowWhenCalledGivenNumberOfTimesTaskFactory<TException, TReturn>::numberOfRuns(0);

	template <template <typename> typename TThrowingTask, typename TException, typename TExceptionBase>
	static void run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException(auto &fixture)
	{
		auto abnormalExitHandler = fixture.mockAbnormalExitHandlerWithAllStubbedToReturn(false);
		TaskLifecycle<StubDefaultConstructorTaskFactoryFor<TThrowingTask<TException>>, AbnormalExitHandlerSubstitute> lifecycle(abnormalExitHandler);
		lifecycle.run();

		auto callsToOnException(
			asVector(abnormalExitHandler
				.template callsToOnException<const TExceptionBase &>()
				.getCallArguments()));

		expect(callsToOnException.size(), equal_to(1));

		auto callToOnException(callsToOnException.at(0));
		expect(
			std::get<0>(callToOnException),
			equal_to(TThrowingTask<TException>::what()));
	}

	template <template <typename> typename TThrowingTask>
	static void run_calledWhenTaskThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled(auto &fixture)
	{
		auto abnormalExitHandler = fixture.mockAbnormalExitHandlerWithAllStubbedToReturn(false);
		TaskLifecycle<StubDefaultConstructorTaskFactoryFor<TThrowingTask<StubUnknownException>>, AbnormalExitHandlerSubstitute> lifecycle(abnormalExitHandler);
		lifecycle.run();

		expect(abnormalExitHandler.callsToOnUnknownException().count(), equal_to(1));
	}

	template <typename TTaskFactory, typename TCaughtException>
	static void run_calledWhenTaskThrowsKnownException_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalse(auto &fixture)
	{
		auto numberOfRunsBeforeExceptionThrown(anyInClosedRange(2, 10));
		TTaskFactory::numberOfRunsBeforeExceptionThrown = numberOfRunsBeforeExceptionThrown;
		TTaskFactory::numberOfRuns = 0;

		auto numberOfAbnormalExitsBeforeFalseReturned(anyInClosedRange(2, 10));
		auto abnormalExitHandler(fixture.stubAbnormalExitHandlerToReturnFalseWhenCalledGivenNumberOfTimes(numberOfAbnormalExitsBeforeFalseReturned));
		TaskLifecycle<TTaskFactory, AbnormalExitHandlerSubstitute> lifecycle(abnormalExitHandler);

		lifecycle.run();
		expect(abnormalExitHandler.template callsToOnException<const TCaughtException &>().count(), equal_to(numberOfAbnormalExitsBeforeFalseReturned));
	}

	template <typename TTaskFactory>
	static void run_calledWhenTaskThrowsUnknownException_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalse(auto &fixture)
	{
		auto numberOfRunsBeforeExceptionThrown(anyInClosedRange(2, 10));
		TTaskFactory::numberOfRunsBeforeExceptionThrown = numberOfRunsBeforeExceptionThrown;
		TTaskFactory::numberOfRuns = 0;

		auto numberOfAbnormalExitsBeforeFalseReturned(anyInClosedRange(2, 10));
		auto abnormalExitHandler(fixture.stubAbnormalExitHandlerToReturnFalseWhenCalledGivenNumberOfTimes(numberOfAbnormalExitsBeforeFalseReturned));
		TaskLifecycle<TTaskFactory, AbnormalExitHandlerSubstitute> lifecycle(abnormalExitHandler);

		lifecycle.run();
		expect(abnormalExitHandler.callsToOnUnknownException().count(), equal_to(numberOfAbnormalExitsBeforeFalseReturned));
	}

	suite<Fixture> taskLifecycleTest("TaskLifecycle Test Suite", [](auto &unit)
	{
		unit.test("run_calledWhenTaskConstructorThrowsSmegException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskDefaultConstructorToThrow,
				StubSmegException,
				Exception>(fixture);
		});

		unit.test("run_calledWhenTaskRunThrowsSmegException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskRunToThrow,
				StubSmegException,
				Exception>(fixture);
		});

		unit.test("run_calledWhenTaskDestructorThrowsSmegException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskDestructorToThrow,
				StubSmegException,
				Exception>(fixture);
		});

		unit.test("run_calledWhenTaskConstructorThrowsStandardException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskDefaultConstructorToThrow,
				StubStandardException,
				std::exception>(fixture);
		});

		unit.test("run_calledWhenTaskRunThrowsStandardException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskRunToThrow,
				StubStandardException,
				std::exception>(fixture);
		});

		unit.test("run_calledWhenTaskDestructorThrowsStandardException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskDestructorToThrow,
				StubStandardException,
				std::exception>(fixture);
		});

		unit.test("run_calledWhenTaskConstructorThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled", [](auto &fixture)
		{
			run_calledWhenTaskThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled<StubTaskDefaultConstructorToThrow>(fixture);
		});

		unit.test("run_calledWhenTaskRunThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled", [](auto &fixture)
		{
			run_calledWhenTaskThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled<StubTaskRunToThrow>(fixture);
		});

		unit.test("run_calledWhenTaskDestructorThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled", [](auto &fixture)
		{
			run_calledWhenTaskThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled<StubTaskDestructorToThrow>(fixture);
		});

		unit.test("run_calledWhenTaskRunReturnsBoolean_expectTaskIsRepeatedlyRunUntilFalseIsReturned", [](auto &fixture)
		{
			using TaskFactory = StubBooleanTaskToRunGivenNumberOfTimesTaskFactory;
			auto numberOfRunsBeforeFalseReturned(anyInClosedRange(2, 10));
			TaskFactory::numberOfRunsBeforeFalseReturned = numberOfRunsBeforeFalseReturned;
			TaskFactory::numberOfRuns = 0;

			auto abnormalExitHandler(fixture.dummyAbnormalExitHandler());
			TaskLifecycle<TaskFactory, DummyAbnormalExitHandler> lifecycle(abnormalExitHandler);

			lifecycle.run();
			expect(TaskFactory::numberOfRuns, equal_to(numberOfRunsBeforeFalseReturned));
		});

		unit.test("run_calledWhenTaskRunReturnsVoid_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalseForSmegException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalse<
				StubTaskToThrowWhenCalledGivenNumberOfTimesTaskFactory<StubSmegException, void>,
				Exception>(fixture);
		});

		unit.test("run_calledWhenTaskRunReturnsVoid_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalseForStandardException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalse<
				StubTaskToThrowWhenCalledGivenNumberOfTimesTaskFactory<StubStandardException, void>,
				std::exception>(fixture);
		});

		unit.test("run_calledWhenTaskRunReturnsVoid_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalseForUnknownException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsUnknownException_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalse<
				StubTaskToThrowWhenCalledGivenNumberOfTimesTaskFactory<StubUnknownException, void>>(fixture);
		});

		unit.test("run_calledWhenTaskRunReturnsBoolean_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalseForSmegException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalse<
				StubTaskToThrowWhenCalledGivenNumberOfTimesTaskFactory<StubSmegException, bool>,
				Exception>(fixture);
		});

		unit.test("run_calledWhenTaskRunReturnsBoolean_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalseForStandardException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalse<
				StubTaskToThrowWhenCalledGivenNumberOfTimesTaskFactory<StubStandardException, bool>,
				std::exception>(fixture);
		});

		unit.test("run_calledWhenTaskRunReturnsBoolean_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalseForUnknownException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsUnknownException_expectTaskIsRepeatedlyRunUntilAbnormalExitHandlerReturnsFalse<
				StubTaskToThrowWhenCalledGivenNumberOfTimesTaskFactory<StubUnknownException, bool>>(fixture);
		});
	});
}
