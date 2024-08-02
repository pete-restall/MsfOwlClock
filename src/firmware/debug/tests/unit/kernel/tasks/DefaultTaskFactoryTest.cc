#include <typeinfo>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tasks/DefaultTaskFactory.hh"

#include "TaskTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel::tasks;

namespace smeg::tests::unit::kernel::tasks
{
	struct DummyKernelApi
	{
	};

	using StubTaskWithDummyKernelApiConstructor = StubTaskWithKernelApiConstructor<DummyKernelApi>;

	using MockTaskWithBothDefaultAndDummyKernelApiConstructors = MockTaskWithBothDefaultAndKernelApiConstructors<DummyKernelApi>;

	suite<> defaultTaskFactoryTest("DefaultTaskFactory Test Suite", [](auto &unit)
	{
		unit.test("createTask_calledWhenFactoryHasNoKernelApiAndTaskHasDefaultConstructor_expectTaskCanBeCreated", []()
		{
			auto task(DefaultTaskFactory<StubTaskWithDefaultConstructor>::createTask());
			auto isTaskExpectedType = typeid(task) == typeid(StubTaskWithDefaultConstructor);
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenFactoryHasKernelApiAndTaskHasDefaultConstructor_expectTaskCanBeCreated", []()
		{
			auto task(DefaultTaskFactory<StubTaskWithDefaultConstructor, DummyKernelApi>::createTask());
			auto isTaskExpectedType = typeid(task) == typeid(StubTaskWithDefaultConstructor);
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenFactoryHasKernelApiAndTaskHasKernelApiConstructor_expectTaskCanBeCreated", []()
		{
			auto task(DefaultTaskFactory<StubTaskWithDummyKernelApiConstructor, DummyKernelApi>::createTask());
			auto isTaskExpectedType = typeid(task) == typeid(StubTaskWithDummyKernelApiConstructor);
			expect(isTaskExpectedType, equal_to(true));
		});

		unit.test("createTask_calledWhenTaskHasBothDefaultAndKernelApiConstructors_expectTaskIsCreatedWithKernelApi", []()
		{
			auto task(DefaultTaskFactory<MockTaskWithBothDefaultAndDummyKernelApiConstructors, DummyKernelApi>::createTask());
			expect(task.wasKernelApiConstructorCalled, equal_to(true));
		});
	});
}
