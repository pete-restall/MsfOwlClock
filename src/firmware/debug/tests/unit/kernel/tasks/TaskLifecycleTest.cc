#include <atomic>
#include <exception>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/Exception.hh"
#include "kernel/tasks/TaskLifecycle.hh"

#include "../../CallRecorder.hh"
#include "../../ViewUtilities.hh"
#include "AbnormalExitHandlerSubstitute.hh"
#include "AbnormalExitHandlerTestDoubles.hh"
#include "StubExceptions.hh"
#include "StubTasks.hh"

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

	struct DummyKernelApi
	{
	};

	template <typename TException>
	using StubTaskDummyKernelApiConstructorToThrow = StubTaskKernelApiConstructorToThrow<TException, DummyKernelApi>;

	template <template <typename> typename TThrowingTask, typename TException, typename TExceptionBase>
	static void run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException(auto &fixture)
	{
		auto abnormalExitHandler = fixture.mockAbnormalExitHandlerWithAllStubbedToReturn(true);
		TaskLifecycle<TThrowingTask<TException>, DummyKernelApi, AbnormalExitHandlerSubstitute> lifecycle(abnormalExitHandler);
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
		TaskLifecycle<TThrowingTask<StubUnknownException>, DummyKernelApi, AbnormalExitHandlerSubstitute> lifecycle(abnormalExitHandler);
		lifecycle.run();

		expect(abnormalExitHandler.callsToOnUnknownException().count(), equal_to(1));
	}

	suite<Fixture> taskLifecycleTest("TaskLifecycle Test Suite", [](auto &unit)
	{
		unit.test("run_calledWhenTaskDefaultConstructorThrowsSmegException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskDefaultConstructorToThrow,
				StubSmegException,
				Exception>(fixture);
		});

		unit.test("run_calledWhenTaskKernelApiConstructorThrowsSmegException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskDummyKernelApiConstructorToThrow,
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

		unit.test("run_calledWhenTaskDefaultConstructorThrowsStandardException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskDefaultConstructorToThrow,
				StubStandardException,
				std::exception>(fixture);
		});

		unit.test("run_calledWhenTaskKernelApiConstructorThrowsStandardException_expectAbnormalExitHandlerIsCalledWithSameException", [](auto &fixture)
		{
			run_calledWhenTaskThrowsKnownException_expectAbnormalExitHandlerIsCalledWithSameException<
				StubTaskDummyKernelApiConstructorToThrow,
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

		unit.test("run_calledWhenTaskDefaultConstructorThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled", [](auto &fixture)
		{
			run_calledWhenTaskThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled<StubTaskDefaultConstructorToThrow>(fixture);
		});

		unit.test("run_calledWhenTaskKernelApiConstructorThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled", [](auto &fixture)
		{
			run_calledWhenTaskThrowsUnknownException_expectAbnormalExitHandlerOnUnknownExceptionIsCalled<StubTaskDummyKernelApiConstructorToThrow>(fixture);
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
			// TODO: this is where StubBooleanTaskToRunGivenNumberOfTimes comes in, but to use this stub we need to refactor to use a task factory.
		});

		// TODO: now start to work in the 'while (restartTask...) { runTask(); }' logic
	});
}
