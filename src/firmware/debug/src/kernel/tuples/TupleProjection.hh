#ifndef __SMEG_KERNEL_TUPLES_TUPLEPROJECTION_HH
#define __SMEG_KERNEL_TUPLES_TUPLEPROJECTION_HH
#include <cstddef>
#include <tuple>

#include "TupleCat.hh"

namespace smeg::kernel::tuples
{
	template <bool, typename, template <typename, std::size_t...> typename>
	struct _$TupleProjection;

	template <typename TTuple, template <typename> typename TProjection>
	class _$TupleProjection<true, TTuple, TProjection>
	{
	private:
		template <bool, typename...>
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

		template <typename...>
		struct _$Output;

		template <typename... T>
		struct _$Output<std::tuple<T...>> // TODO: we should change _$Output to _$Output, plus the same for the others...
		{
			using AsTuple = Project<true, T...>::AsTuple; // TODO: We can tidy this up by removing 'typename' - check the others, too.
		};

	public:
		using Input = TTuple;
		using Output = _$Output<TTuple>::AsTuple;
	};

	template <typename TTuple, template <typename, std::size_t> typename TProjection>
	class _$TupleProjection<true, TTuple, TProjection>
	{
	private:
		template <std::size_t, typename...>
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

		template <typename...>
		struct _$Output;

		template <typename... T>
		struct _$Output<std::tuple<T...>>
		{
			using AsTuple = Project<0, T...>::AsTuple;
		};

	public:
		using Input = TTuple;
		using Output = _$Output<TTuple>::AsTuple;
	};

	template <typename TTuple, template <typename, std::size_t, std::size_t> typename TProjection>
	class _$TupleProjection<true, TTuple, TProjection>
	{
	private:
		template <std::size_t, std::size_t, typename...>
		struct Project;

		template <std::size_t InputIndex, std::size_t OutputIndex, typename THead, typename... TTail>
		struct Project<InputIndex, OutputIndex, THead, TTail...>
		{
			using ProjectedAsTuple = TProjection<THead, InputIndex, OutputIndex>::AsTuple;
			using AsTuple = TupleCat<
				ProjectedAsTuple,
				typename Project<InputIndex + 1, OutputIndex + std::tuple_size_v<ProjectedAsTuple>, TTail...>::AsTuple>;
		};

		template <std::size_t InputIndex, std::size_t OutputIndex>
		struct Project<InputIndex, OutputIndex>
		{
			using AsTuple = std::tuple<>;
		};

		template <typename...>
		struct _$Output;

		template <typename... T>
		struct _$Output<std::tuple<T...>>
		{
			using AsTuple = Project<0, 0, T...>::AsTuple;
		};


	public:
		using Input = TTuple;
		using Output = _$Output<TTuple>::AsTuple;
	};

	template <typename TTuple, template <typename, std::size_t...> typename TProjection>
	using TupleProjection = _$TupleProjection<true, TupleCat<TTuple>, TProjection>;
}

#endif
