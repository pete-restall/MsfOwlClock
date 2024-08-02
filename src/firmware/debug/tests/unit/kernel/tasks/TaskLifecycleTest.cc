#include <atomic>
#include <exception>
#include <stdexcept>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/Exception.hh"
#include "kernel/tasks/TaskLifecycle.hh"

#include "../../CallRecorder.hh"
#include "../../ViewUtilities.hh"
#include "AbnormalExitHandlerSubstitute.hh"
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
	struct StubTaskFactoryFor
	{
		static TTask createTask(void)
		{
			return TTask();
		}
	};

	template <template <typename> typename TThrowingTask, typename TException, typename TExceptionBase>
	static void run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException(auto &fixture)
	{
		auto abnormalExitHandler = fixture.mockAbnormalExitHandlerWithAllStubbedToReturn(true);
		TaskLifecycle<StubTaskFactoryFor<TThrowingTask<TException>>, AbnormalExitHandlerSubstitute> lifecycle(abnormalExitHandler);
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
		auto abnormalExitHandler = fixture.mockAbnormalExitHandlerWithAllStubbedToReturn(true);
		TaskLifecycle<StubTaskFactoryFor<TThrowingTask<StubUnknownException>>, AbnormalExitHandlerSubstitute> lifecycle(abnormalExitHandler);
		lifecycle.run();

		expect(abnormalExitHandler.callsToOnUnknownException().count(), equal_to(1));
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
			// TODO: now we can use a StubTaskFactory that returns a StubBooleanTaskToRunGivenNumberOfTimes(N)
		});

		// TODO: now start to work in the 'while (restartTask...) { runTask(); }' logic
	});
}
