#ifndef __SMEG_KERNEL_TUPLES_TUPLEINDEXZIP_HH
#define __SMEG_KERNEL_TUPLES_TUPLEINDEXZIP_HH
#include <cstdint>
#include <tuple>
#include "TupleProjection.hh"

namespace smeg::kernel::tuples
{
	template <typename T, std::size_t Index>
	struct TupleElementWithIndex
	{
	};

	template <typename... T>
	struct TupleIndexZip;

	template <typename... T>
	class TupleIndexZip<std::tuple<T...>>
	{
	private:
		template <typename TElement, std::size_t Index>
		struct Zipper
		{
			using AsTuple = std::tuple<TupleElementWithIndex<TElement, Index>>;
		};

	public:
		using WithIndices = TupleProjection<std::tuple<T...>, Zipper>::Output;
	};

	template <typename... T>
	struct TupleIndexZip
	{
		using WithIndices = TupleIndexZip<std::tuple<T...>>::WithIndices;
	};
}

#endif
