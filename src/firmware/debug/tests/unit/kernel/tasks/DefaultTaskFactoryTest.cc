#include <typeinfo>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/DefaultTaskFactory.hh"

#include "TaskTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel::tasks;

namespace smeg::tests::unit::kernel::tasks
{
	struct DummyRequiredApi
	{
	};

	suite<AppToDriverApis<DummyRequiredApi>, DriverToDriverApis<DummyRequiredApi>, DriverToKernelApis<DummyRequiredApi>> defaultTaskFactoryTest("DefaultTaskFactory Test Suite", [](auto &unit)
	{
		unit.test("createTask_calledWhenTaskHasNoRequiredApisAndHasDefaultConstructor_expectTaskCanBeCreated", [](auto)
		{
			auto task(DefaultTaskFactory<StubTaskWithDefaultConstructor>::createTask());
			auto isTaskExpectedType = typeid(task) == typeid(StubTaskWithDefaultConstructor);
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasRequiredApisButOnlyHasDefaultConstructor_expectTaskCanBeCreated", [](auto fixture)
		{
			using StubTask = StubTaskWithRequiredApisAndDefaultConstructor<decltype(fixture)>;
			auto task(DefaultTaskFactory<StubTask>::createTask());
			auto isTaskExpectedType = typeid(task) == typeid(StubTask);
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasRequiredApisAndHasMatchingConstructor_expectTaskCanBeCreated", [](auto fixture)
		{
			using StubTask = StubTaskWithRequiredApisConstructor<decltype(fixture)>;
			auto task(DefaultTaskFactory<StubTask>::createTask());
			auto isTaskExpectedType = typeid(task) == typeid(StubTask);
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasBothDefaultAndRequiredApisConstructors_expectTaskIsCreatedWithRequiredApis", [](auto fixture)
		{
			using MockTask = MockTaskWithBothDefaultAndRequiredApisConstructors<decltype(fixture)>;
			auto task(DefaultTaskFactory<MockTask>::createTask());
			expect(task.wasRequiredApisConstructorCalled, equal_to(true));
		});
	});
}
