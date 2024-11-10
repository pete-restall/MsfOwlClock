#ifndef __SMEG_KERNEL_TUPLES_TUPLEPROJECTION_HH
#define __SMEG_KERNEL_TUPLES_TUPLEPROJECTION_HH
#include <cstddef>
#include <tuple>

namespace smeg::kernel::tuples
{
	template <bool TDummyForSpecialisation, typename TTuple, template <typename, std::size_t...> typename TProjection>
	struct _TupleProjection;

	template <typename TTuple, template <typename> typename TProjection>
	class _TupleProjection<true, TTuple, TProjection>
	{
	private:
		template <typename THead, typename... TTail>
		static consteval auto project(std::tuple<THead, TTail...>)
		{
			return std::tuple_cat(
				typename TProjection<THead>::AsTuple{},
				project(std::tuple<TTail...>{}));
		}

		static consteval auto project(std::tuple<>)
		{
			return std::tuple<>{};
		}

	public:
		using Input = TTuple;
		using Output = decltype(project(TTuple{}));
	};

	template <typename TTuple, template <typename, std::size_t> typename TProjection>
	class _TupleProjection<true, TTuple, TProjection>
	{
	private:
		template <std::size_t InputIndex, typename THead, typename... TTail>
		static consteval auto project(std::tuple<THead, TTail...>)
		{
			return std::tuple_cat(
				typename TProjection<THead, InputIndex>::AsTuple{},
				project<InputIndex + 1>(std::tuple<TTail...>{}));
		}

		template <std::size_t InputIndex>
		static consteval auto project(std::tuple<>)
		{
			return std::tuple<>{};
		}

	public:
		using Input = TTuple;
		using Output = decltype(project<0>(TTuple{}));
	};

	template <typename TTuple, template <typename, std::size_t, std::size_t> typename TProjection>
	class _TupleProjection<true, TTuple, TProjection>
	{
	private:
		template <std::size_t InputIndex, std::size_t OutputIndex, typename THead, typename... TTail>
		static consteval auto project(std::tuple<THead, TTail...>)
		{
			using ProjectedAsTuple = typename TProjection<THead, InputIndex, OutputIndex>::AsTuple;
			return std::tuple_cat(
				ProjectedAsTuple{},
				project<InputIndex + 1, OutputIndex + std::tuple_size_v<ProjectedAsTuple>>(std::tuple<TTail...>{}));
		}

		template <std::size_t InputIndex, std::size_t OutputIndex>
		static consteval auto project(std::tuple<>)
		{
			return std::tuple<>{};
		}

	public:
		using Input = TTuple;
		using Output = decltype(project<0, 0>(TTuple{}));
	};

	template <typename TTuple, template <typename, std::size_t...> typename TProjection>
	using TupleProjection = _TupleProjection<true, decltype(std::tuple_cat(TTuple{})), TProjection>;
}

#endif
