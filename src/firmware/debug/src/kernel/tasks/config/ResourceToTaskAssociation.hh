#ifndef __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#define __SMEG_KERNEL_TASKS_CONFIG_RESOURCETOTASKASSOCIATION_HH
#include <cstdint>
#include <type_traits>
#include <utility>
#include "../../IntegerSequenceUtilities.hh"

namespace smeg::kernel::tasks::config
{
	template <typename TResource, std::size_t HeadTaskId, std::size_t... TailTaskIds>
	class ResourceToTaskAssociation
	{
	private:
		// TODO: ALL OF THIS NEEDS REFACTORING - IT CAN ALL BE SPLIT OUT AND TESTED INDEPENDENTLY...LOVELY.

		template <typename T, T Head, T... Tail>
		struct Unique
		{
			using Values = std::conditional<
				((Head != Tail) && ...),
				decltype(pushFront<Head>(typename Unique<T, Tail...>::Values{})),
				typename Unique<T, Tail...>::Values
			>::type;
		};

		template <typename T, T Head>
		struct Unique<T, Head>
		{
			using Values = std::integer_sequence<T, Head>;
		};

		template <typename T, T Head, T... Tail>
		class BubbleSorted
		{
		private:
			template <T A, T... Ints>
			struct BubbleSortIteration;

			template <T A, T B, T... Ints>
			struct BubbleSortIteration<A, B, Ints...>
			{
				using Values = std::conditional<
					A < B,
					decltype(pushFront<A>(typename BubbleSortIteration<B, Ints...>::Values{})),
					decltype(pushFront<B>(typename BubbleSortIteration<A, Ints...>::Values{}))
				>::type;
			};

			template <T A>
			struct BubbleSortIteration<A>
			{
				using Values = std::integer_sequence<T, A>;
			};

			template <auto N, auto... Ints>
			static constexpr auto sort(std::integer_sequence<T, Ints...> seq)
			{
				if constexpr (N > (sizeof...(Ints) + 1) / 2)
					return seq;
				else
					return sort<N + 1>(typename BubbleSortIteration<Ints...>::Values{});
			}

		public:
			using Values = decltype(sort<0>(std::integer_sequence<T, Head, Tail...>{}));
		};

		template <typename T, T... Ints>
		static constexpr auto bubbleSorted(std::integer_sequence<T, Ints...>)
		{
			return typename BubbleSorted<T, Ints...>::Values{};
		}

	public:
		using TaskIds = decltype(bubbleSorted(typename Unique<std::size_t, HeadTaskId, TailTaskIds...>::Values{})); // TODO: This can be made into a 'SortedSet<>' type...cool...

		using IsSharedResource = std::conditional<(TaskIds::size() > 1), std::true_type, std::false_type>::type;

		static constexpr bool isSharedResource = IsSharedResource::value;
	};
}

#endif
