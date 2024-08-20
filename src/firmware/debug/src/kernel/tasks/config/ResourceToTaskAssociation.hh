#ifndef __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#define __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#include <cstdint>
#include <type_traits>
#include <utility>
#include "../../integer-sequences/SortedSet.hh"

namespace smeg::kernel::tasks::config
{
	using namespace smeg::kernel::integer_sequences;

	// TODO: Should we also be allowed to have an empty ResourceToTaskAssociation ?  Makes sense in some cases, such as identifying unallocated resources
	// TODO: Yes, and this has been modified - add some tests for empty tasks...
	// TODO: SortedSet also needs to be modified to allow emptiness before this will compile - make it so.
	// TODO: Find users of ResourceToTaskAssociation and modify their tests to exercise emptiness.
	// TODO: Find users of SortedSet and modify their tests to exercise emptiness.
	template <typename TResource, std::size_t... AssociatedTaskIds>
	struct ResourceToTaskAssociation
	{
		using TaskIds = SortedSet<std::size_t, AssociatedTaskIds...>::Ascending;

		// TODO: Bad terminology - having a type associated with multiple tasks does not mean it is a shared resource; it is perfectly possible / acceptable
		// to instantiate one instance of the resource for each task, which is up to the consumer of this class.  Rename this to something more sensible.
		using IsSharedResource = std::conditional<(TaskIds::size() > 1), std::true_type, std::false_type>::type;

		static constexpr bool isSharedResource = IsSharedResource::value;
	};
}

#endif
