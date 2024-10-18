#ifndef __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#define __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#include <cstdint>
#include <type_traits>
#include <utility>
#include "../../integer-sequences/SortedSet.hh"

namespace smeg::kernel::tasks::config
{
	using namespace smeg::kernel::integer_sequences;

	template <typename TResource, std::size_t... AssociatedTaskIds>
	struct ResourceToTaskAssociation
	{
		using Resource = TResource;
		using TaskIds = SortedSet<std::size_t, AssociatedTaskIds...>::Ascending;

		using HasMultipleTasks = std::conditional<(TaskIds::size() > 1), std::true_type, std::false_type>::type;

		static constexpr bool hasMultipleTasks = HasMultipleTasks::value;

		template <typename TNewResource>
		using WithResource = ResourceToTaskAssociation<TNewResource, AssociatedTaskIds...>;
	};
}

#endif
