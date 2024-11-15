#ifndef __SMEG_KERNEL_TUPLES_UNIQUE_HH
#define __SMEG_KERNEL_TUPLES_UNIQUE_HH
#include <array>
#include <concepts>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

#include "TupleCat.hh"

namespace smeg::kernel::tuples
{
	template <typename T>
	struct _Unique;

	template <typename THead, typename... TTail>
	struct _Unique<std::tuple<THead, TTail...>>
	{
		using AsTuple = std::conditional<
			(!std::same_as<THead, TTail> && ...),
			TupleCat<std::tuple<THead>, typename _Unique<std::tuple<TTail...>>::AsTuple>,
			typename _Unique<std::tuple<TTail...>>::AsTuple
		>::type;
	};

	template <typename T>
	struct _Unique<std::tuple<T>>
	{
		using AsTuple = std::tuple<T>;
	};

	template <>
	struct _Unique<std::tuple<>>
	{
		using AsTuple = std::tuple<>;
	};

	template <typename T1, typename T2>
	struct _Unique<std::pair<T1, T2>>
	{
		using AsTuple = std::conditional_t<std::same_as<T1, T2>, std::tuple<T1>, std::tuple<T1, T2>>;
	};

	template <typename T>
	struct _Unique<std::array<T, 0>>
	{
		using AsTuple = std::tuple<>;
	};

	template <typename T, std::size_t N>
	struct _Unique<std::array<T, N>>
	{
		using AsTuple = std::tuple<T>;
	};

	template <typename T>
	using Unique = _Unique<T>::AsTuple;
}

#endif
