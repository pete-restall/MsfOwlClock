#ifndef __SMEG_KERNEL_BAREMETAL_INTEGERSEQUENCE_HH
#define __SMEG_KERNEL_BAREMETAL_INTEGERSEQUENCE_HH
#include <array>
#include <concepts>
#include <utility>

namespace smeg::kernel::bare_metal
{
	template <std::integral auto FirstElement, std::integral auto... Values>
	struct _StructTypeOfFirstElementIn
	{
		using Type = decltype(FirstElement);
	};

	template <std::integral auto... Values>
	using _TypeOfFirstElementIn = _StructTypeOfFirstElementIn<Values...>::Type;

	template <typename TSeq>
	struct IntegerSequence;

	template <std::integral auto... Ints>
	struct IntegerSequence<std::integer_sequence<_TypeOfFirstElementIn<Ints...>, Ints...>>
	{
		using Values = std::integer_sequence<_TypeOfFirstElementIn<Ints...>, Ints...>;
	};

	template <typename T>
	struct IntegerSequence<std::integer_sequence<T>>
	{
		using Values = std::integer_sequence<T>;
	};
}

#endif
