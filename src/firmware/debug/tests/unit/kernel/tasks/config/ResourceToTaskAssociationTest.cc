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

	suite<> resourceToTaskAssociationTest("ResourceToTaskAssociation Test Suite", [](auto &unit)
	{
		unit.test("isSharedResource_getWhenPassedSingleTaskId_expectFalse", []()
		{
			std::array assertions
			{
				ResourceToTaskAssociation<DummyResource, 1>::isSharedResource,
				ResourceToTaskAssociation<DummyResource, 77>::isSharedResource,
				ResourceToTaskAssociation<DummyResource, 1024>::isSharedResource
			};

			expect(assertions, each(equal_to(false)));
		});

		unit.test("isSharedResource_getWhenPassedMultipleTaskIds_expectTrue", []()
		{
			std::array assertions
			{
				ResourceToTaskAssociation<DummyResource, 1, 2>::isSharedResource,
				ResourceToTaskAssociation<DummyResource, 77, 33, 11>::isSharedResource,
				ResourceToTaskAssociation<DummyResource, 0, 1, 1, 2, 3, 5, 8, 13>::isSharedResource
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("isSharedResource_getWhenPassedSingleDuplicatedTaskId_expectFalse", []()
		{
			std::array assertions
			{
				ResourceToTaskAssociation<DummyResource, 1, 1>::isSharedResource,
				ResourceToTaskAssociation<DummyResource, 2, 2, 2>::isSharedResource,
				ResourceToTaskAssociation<DummyResource, 7, 7, 7, 7, 7, 7, 7>::isSharedResource
			};

			expect(assertions, each(equal_to(false)));
		});

		unit.test("IsSharedResource_getWhenPassedSingleTaskId_expectFalse", []()
		{
			std::array assertions
			{
				typeid(ResourceToTaskAssociation<DummyResource, 1>::IsSharedResource) == typeid(std::false_type),
				typeid(ResourceToTaskAssociation<DummyResource, 77>::IsSharedResource) == typeid(std::false_type),
				typeid(ResourceToTaskAssociation<DummyResource, 1024>::IsSharedResource) == typeid(std::false_type)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("IsSharedResource_getWhenPassedMultipleTaskIds_expectTrue", []()
		{
			std::array assertions
			{
				typeid(ResourceToTaskAssociation<DummyResource, 1, 2>::IsSharedResource) == typeid(std::true_type),
				typeid(ResourceToTaskAssociation<DummyResource, 77, 33, 11>::IsSharedResource) == typeid(std::true_type),
				typeid(ResourceToTaskAssociation<DummyResource, 0, 1, 1, 2, 3, 5, 8, 13>::IsSharedResource) == typeid(std::true_type)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("IsSharedResource_getWhenPassedSingleDuplicatedTaskId_expectFalse", []()
		{
			std::array assertions
			{
				typeid(ResourceToTaskAssociation<DummyResource, 1, 1>::IsSharedResource) == typeid(std::false_type),
				typeid(ResourceToTaskAssociation<DummyResource, 2, 2, 2>::IsSharedResource) == typeid(std::false_type),
				typeid(ResourceToTaskAssociation<DummyResource, 7, 7, 7, 7, 7, 7, 7>::IsSharedResource) == typeid(std::false_type)
			};

			expect(assertions, each(equal_to(true)));
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
	});
}