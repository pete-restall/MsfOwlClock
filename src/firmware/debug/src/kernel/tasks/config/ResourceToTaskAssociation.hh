#ifndef __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#define __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#include <cstdint>
#include <type_traits>
#include <utility>
#include "../../integer-sequences/SortedSet.hh"

namespace smeg::kernel::tasks::config
{
	using namespace smeg::kernel::integer_sequences;

	// TODO: SortedSet also needs to be modified to allow emptiness before this will compile - make it so.
	// TODO: Find users of ResourceToTaskAssociation and modify their tests to exercise emptiness.
	// TODO: Find users of SortedSet and modify their tests to exercise emptiness.
	template <typename TResource, std::size_t... AssociatedTaskIds>
	struct ResourceToTaskAssociation
	{
		using TaskIds = SortedSet<std::size_t, AssociatedTaskIds...>::Ascending;

		using HasMultipleTasks = std::conditional<(TaskIds::size() > 1), std::true_type, std::false_type>::type;

		static constexpr bool hasMultipleTasks = HasMultipleTasks::value;
	};
}

#endif
