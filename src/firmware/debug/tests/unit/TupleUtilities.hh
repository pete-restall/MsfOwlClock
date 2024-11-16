#ifndef __SMEG_TESTS_UNIT_TUPLEUTILITIES_HH
#define __SMEG_TESTS_UNIT_TUPLEUTILITIES_HH
#include <concepts>
#include <tuple>
#include <utility>

namespace smeg::tests::unit
{
	template <typename T, typename... TElements>
	struct TupleContains
	{
		static constexpr bool value = false;
	};

	template <typename T, typename... TElements>
	class TupleContains<T, std::tuple<TElements...>>
	{
	public:
		static constexpr bool value = (std::same_as<T, TElements> || ...);
	};

	template <typename T1, typename... T2Elements>
	class TuplesContainSameElements;

	template <typename T1, typename... T2Elements>
	class TuplesContainSameElements<T1, std::tuple<T2Elements...>>
	{
	private:
		template <typename T2, typename... T1Elements>
		struct OtherTupleContainsSameElements;

		template <typename T2, typename... T1Elements>
		struct OtherTupleContainsSameElements<T2, std::tuple<T1Elements...>>
		{
			static constexpr bool areAllContained = (TupleContains<T1Elements, T2>::value && ...);
		};

	public:
		static constexpr bool inAnyOrder =
			std::tuple_size_v<T1> == std::tuple_size_v<std::tuple<T2Elements...>> &&
			(TupleContains<T2Elements, T1>::value && ...) &&
			OtherTupleContainsSameElements<std::tuple<T2Elements...>, T1>::areAllContained;
	};

	template <typename T>
	constexpr auto popFront(T &tuple)
	{
		static_assert(std::tuple_size_v<T> > 0, "An empty tuple does not have a front element available to pop");
		return std::apply([](auto, auto... back) noexcept { return std::make_tuple(back...); }, tuple);
	}
}

#endif
