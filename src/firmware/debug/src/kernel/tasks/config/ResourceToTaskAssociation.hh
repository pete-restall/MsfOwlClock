#ifndef __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#define __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#include <cstdint>
#include <type_traits>
#include <utility>
#include "../../integer-sequences/BubbleSorted.hh"
#include "../../integer-sequences/utilities.hh"
#include "../../integer-sequences/Unique.hh"

namespace smeg::kernel::tasks::config
{
	using namespace smeg::kernel::integer_sequences;

	// TODO: WE CAN TIDY UP THE TESTS FOR THIS NOW, TOO...
	template <typename TResource, std::size_t HeadTaskId, std::size_t... TailTaskIds>
	struct ResourceToTaskAssociation
	{
		using TaskIds = decltype(bubbleSortedAscending(typename Unique<std::size_t, HeadTaskId, TailTaskIds...>::Values{})); // TODO: This can be made into a 'SortedSet<>' type...cool...

		using IsSharedResource = std::conditional<(TaskIds::size() > 1), std::true_type, std::false_type>::type;

		static constexpr bool isSharedResource = IsSharedResource::value;
	};
}

#endif
