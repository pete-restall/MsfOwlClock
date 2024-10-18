#include <array>
#include <cstdint>
#include <type_traits>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "../../../IntegerSequenceUtilities.hh"

#include "kernel/tasks/config/ResourceToTaskAssociation.hh"

using namespace mettle;

using namespace smeg::kernel::tasks::config;

namespace smeg::tests::unit::kernel::tasks::config
{
	struct DummyResource
	{
	};

	struct AnotherDummyResource
	{
	};

	suite<> resourceToTaskAssociationTest("ResourceToTaskAssociation Test Suite", [](auto &unit)
	{
		unit.test("hasMultipleTasks_getWhenPassedNoTasksId_expectFalse", []()
		{
			expect(ResourceToTaskAssociation<DummyResource>::hasMultipleTasks, equal_to(false));
		});

		unit.test("hasMultipleTasks_getWhenPassedSingleTaskId_expectFalse", []()
		{
			std::array assertions
			{
				ResourceToTaskAssociation<DummyResource, 1>::hasMultipleTasks,
				ResourceToTaskAssociation<DummyResource, 77>::hasMultipleTasks,
				ResourceToTaskAssociation<DummyResource, 1024>::hasMultipleTasks
			};

			expect(assertions, each(equal_to(false)));
		});

		unit.test("hasMultipleTasks_getWhenPassedMultipleTaskIds_expectTrue", []()
		{
			std::array assertions
			{
				ResourceToTaskAssociation<DummyResource, 1, 2>::hasMultipleTasks,
				ResourceToTaskAssociation<DummyResource, 77, 33, 11>::hasMultipleTasks,
				ResourceToTaskAssociation<DummyResource, 0, 1, 1, 2, 3, 5, 8, 13>::hasMultipleTasks
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("hasMultipleTasks_getWhenPassedSingleDuplicatedTaskId_expectFalse", []()
		{
			std::array assertions
			{
				ResourceToTaskAssociation<DummyResource, 1, 1>::hasMultipleTasks,
				ResourceToTaskAssociation<DummyResource, 2, 2, 2>::hasMultipleTasks,
				ResourceToTaskAssociation<DummyResource, 7, 7, 7, 7, 7, 7, 7>::hasMultipleTasks
			};

			expect(assertions, each(equal_to(false)));
		});

		unit.test("HasMultipleTasks_getWhenPassedNoTaskIds_expectFalse", []()
		{
			expect(typeid(ResourceToTaskAssociation<DummyResource>::HasMultipleTasks) == typeid(std::false_type), equal_to(true));
		});

		unit.test("HasMultipleTasks_getWhenPassedSingleTaskId_expectFalse", []()
		{
			std::array assertions
			{
				typeid(ResourceToTaskAssociation<DummyResource, 1>::HasMultipleTasks) == typeid(std::false_type),
				typeid(ResourceToTaskAssociation<DummyResource, 77>::HasMultipleTasks) == typeid(std::false_type),
				typeid(ResourceToTaskAssociation<DummyResource, 1024>::HasMultipleTasks) == typeid(std::false_type)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("HasMultipleTasks_getWhenPassedMultipleTaskIds_expectTrue", []()
		{
			std::array assertions
			{
				typeid(ResourceToTaskAssociation<DummyResource, 1, 2>::HasMultipleTasks) == typeid(std::true_type),
				typeid(ResourceToTaskAssociation<DummyResource, 77, 33, 11>::HasMultipleTasks) == typeid(std::true_type),
				typeid(ResourceToTaskAssociation<DummyResource, 0, 1, 1, 2, 3, 5, 8, 13>::HasMultipleTasks) == typeid(std::true_type)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("HasMultipleTasks_getWhenPassedSingleDuplicatedTaskId_expectFalse", []()
		{
			std::array assertions
			{
				typeid(ResourceToTaskAssociation<DummyResource, 1, 1>::HasMultipleTasks) == typeid(std::false_type),
				typeid(ResourceToTaskAssociation<DummyResource, 2, 2, 2>::HasMultipleTasks) == typeid(std::false_type),
				typeid(ResourceToTaskAssociation<DummyResource, 7, 7, 7, 7, 7, 7, 7>::HasMultipleTasks) == typeid(std::false_type)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("TaskIds_getWhenPassedNoTaskIds_expectNoTaskIds", []()
		{
			expect(asVector(ResourceToTaskAssociation<DummyResource>::TaskIds{}), array());
		});

		unit.test("TaskIds_getWhenPassedSingleTaskId_expectSameTaskId", []()
		{
			expect(asVector(ResourceToTaskAssociation<DummyResource, 1>::TaskIds{}), array(1));
			expect(asVector(ResourceToTaskAssociation<DummyResource, 999>::TaskIds{}), array(999));
			expect(asVector(ResourceToTaskAssociation<DummyResource, 1024>::TaskIds{}), array(1024));
		});

		unit.test("TaskIds_getWhenPassedSingleDuplicatedTaskId_expectSameTaskId", []()
		{
			expect(asVector(ResourceToTaskAssociation<DummyResource, 1, 1>::TaskIds{}), array(1));
			expect(asVector(ResourceToTaskAssociation<DummyResource, 65535, 65535, 65535, 65535, 65535, 65535>::TaskIds{}), array(65535));
			expect(asVector(ResourceToTaskAssociation<DummyResource, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42>::TaskIds{}), array(42));
		});

		unit.test("TaskIds_getWhenPassedMultipleTaskIds_expectSameTaskIdsSortedInAscendingOrder", []()
		{
			expect(asVector(ResourceToTaskAssociation<DummyResource, 1, 2>::TaskIds{}), array(1, 2));
			expect(asVector(ResourceToTaskAssociation<DummyResource, 5, 3, 2, 4, 1>::TaskIds{}), array(1, 2, 3, 4, 5));
			expect(asVector(ResourceToTaskAssociation<DummyResource, 1024, 7, 48, 111, 8713124>::TaskIds{}), array(7, 48, 111, 1024, 8713124));
		});

		unit.test("TaskIds_getWhenPassedMultipleTaskIdsWithSomeDuplicates_expectUniqueTaskIdsSortedInAscendingOrder", []()
		{
			expect(asVector(ResourceToTaskAssociation<DummyResource, 1, 2, 1>::TaskIds{}), array(1, 2));
			expect(asVector(ResourceToTaskAssociation<DummyResource, 1, 1, 2>::TaskIds{}), array(1, 2));
			expect(asVector(ResourceToTaskAssociation<DummyResource, 5, 7, 100, 7, 23, 6, 652385, 5, 88, 652385>::TaskIds{}), array(5, 6, 7, 23, 88, 100, 652385));
		});

		unit.test("Resource_get_expectSameTypeAsTemplateArgument", []()
		{
			std::array assertions
			{
				typeid(typename ResourceToTaskAssociation<DummyResource>::Resource) == typeid(DummyResource),
				typeid(typename ResourceToTaskAssociation<DummyResource, 1, 2, 3>::Resource) == typeid(DummyResource),
				typeid(typename ResourceToTaskAssociation<std::array<int, 73>>::Resource) == typeid(std::array<int, 73>)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("WithResource_get_expectSameAssociationButWithNewResource", []()
		{
			using Association = ResourceToTaskAssociation<DummyResource, 1, 2, 3>;
			using NewAssociation = Association::WithResource<AnotherDummyResource>;
			expect(typeid(NewAssociation) == typeid(ResourceToTaskAssociation<AnotherDummyResource, 1, 2, 3>), equal_to(true));
		});
	});
}
