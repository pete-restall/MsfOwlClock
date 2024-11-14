#ifndef __SMEG_KERNEL_TUPLES_TUPLEPROJECTION_HH
#define __SMEG_KERNEL_TUPLES_TUPLEPROJECTION_HH
#include <cstddef>
#include <tuple>

#include "TupleCat.hh"

namespace smeg::kernel::tuples
{
	template <bool TDummyForSpecialisation, typename TTuple, template <typename, std::size_t...> typename TProjection>
	struct _TupleProjection;

	template <typename TTuple, template <typename> typename TProjection>
	class _TupleProjection<true, TTuple, TProjection>
	{
	private:
		template <bool TDummyForSpecialisation, typename... T>
		struct Project;

		template <bool TDummyForSpecialisation, typename THead, typename... TTail>
		struct Project<TDummyForSpecialisation, THead, TTail...>
		{
			using AsTuple = TupleCat<typename TProjection<THead>::AsTuple, typename Project<TDummyForSpecialisation, TTail...>::AsTuple>;
		};

		template <bool TDummyForSpecialisation>
		struct Project<TDummyForSpecialisation>
		{
			using AsTuple = std::tuple<>;
		};

		template <typename... T>
		struct _Output;

		template <typename... T>
		struct _Output<std::tuple<T...>>
		{
			using AsTuple = typename Project<true, T...>::AsTuple;
		};

	public:
		using Input = TTuple;
		using Output = typename _Output<TTuple>::AsTuple;
	};

	template <typename TTuple, template <typename, std::size_t> typename TProjection>
	class _TupleProjection<true, TTuple, TProjection>
	{
	private:
		template <std::size_t InputIndex, typename... T>
		struct Project;

		template <std::size_t InputIndex, typename THead, typename... TTail>
		struct Project<InputIndex, THead, TTail...>
		{
			using AsTuple = TupleCat<
				typename TProjection<THead, InputIndex>::AsTuple,
				typename Project<InputIndex + 1, TTail...>::AsTuple>;
		};

		template <std::size_t InputIndex>
		struct Project<InputIndex>
		{
			using AsTuple = std::tuple<>;
		};

		template <typename... T>
		struct _Output;

		template <typename... T>
		struct _Output<std::tuple<T...>>
		{
			using AsTuple = typename Project<0, T...>::AsTuple;
		};

	public:
		using Input = TTuple;
		using Output = typename _Output<TTuple>::AsTuple;
	};

	template <typename TTuple, template <typename, std::size_t, std::size_t> typename TProjection>
	class _TupleProjection<true, TTuple, TProjection>
	{
	private:
		template <std::size_t InputIndex, std::size_t OutputIndex, typename... T>
		struct Project;

		template <std::size_t InputIndex, std::size_t OutputIndex, typename THead, typename... TTail>
		struct Project<InputIndex, OutputIndex, THead, TTail...>
		{
			using ProjectedAsTuple = typename TProjection<THead, InputIndex, OutputIndex>::AsTuple;
			using AsTuple = TupleCat<
				ProjectedAsTuple,
				typename Project<InputIndex + 1, OutputIndex + std::tuple_size_v<ProjectedAsTuple>, TTail...>::AsTuple>;
		};

		template <std::size_t InputIndex, std::size_t OutputIndex>
		struct Project<InputIndex, OutputIndex>
		{
			using AsTuple = std::tuple<>;
		};

		template <typename... T>
		struct _Output;

		template <typename... T>
		struct _Output<std::tuple<T...>>
		{
			using AsTuple = typename Project<0, 0, T...>::AsTuple;
		};


	public:
		using Input = TTuple;
		using Output = typename _Output<TTuple>::AsTuple;
	};

	template <typename TTuple, template <typename, std::size_t...> typename TProjection>
	using TupleProjection = _TupleProjection<true, TupleCat<TTuple>, TProjection>;
}

#endif
