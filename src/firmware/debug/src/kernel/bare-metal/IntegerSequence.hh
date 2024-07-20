#ifndef __SMEG_KERNEL_BAREMETAL_INTEGERSEQUENCE_HH
#define __SMEG_KERNEL_BAREMETAL_INTEGERSEQUENCE_HH
#include <array>
#include <concepts>
#include <utility>

namespace smeg::kernel::bare_metal
{
	namespace
	{
		template <auto... Values>
		using TypeOfFirstElementIn = decltype(std::to_array({Values...}))::value_type;
	}

	template <typename TSeq>
	struct IntegerSequence;

	template <std::integral auto... Ints>
	struct IntegerSequence<std::integer_sequence<TypeOfFirstElementIn<Ints...>, Ints...>>
	{
		using Values = std::integer_sequence<TypeOfFirstElementIn<Ints...>, Ints...>;
	};

	template <typename T>
	struct IntegerSequence<std::integer_sequence<T>>
	{
		using Values = std::integer_sequence<T>;
	};
}

#endif
