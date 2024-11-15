#include <algorithm>
#include <array>
#include <concepts>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tuples/Unique.hh"

using namespace mettle;

using namespace smeg::kernel::tuples;

namespace smeg::tests::unit::kernel::tuples
{
	template <auto X>
	struct Dummy
	{
	};

	template <int X>
	struct Stub
	{
		static constexpr int value = X;
	};

	template <typename... T>
	struct From;

	template <typename... T>
	struct From<std::tuple<T...>>
	{
		static constexpr std::array values{T::value ...};

		static auto getSortedValues(void)
		{
			auto sortedValues(values);
			std::sort(sortedValues.begin(), sortedValues.end());
			return sortedValues;
		}
	};

	suite<> uniqueTest("Unique Test Suite", [](auto &unit)
	{
		unit.test("Unique_getWithEmptyTuple_expectEmptyTuple", []()
		{
			using EmptyTuple = std::tuple<>;
			expect(std::same_as<Unique<EmptyTuple>, EmptyTuple>, equal_to(true));
		});

		unit.test("Unique_getWithTupleOfSingleElement_expectTupleOfSameElement", []()
		{
			using Tuple = std::tuple<Dummy<42>>;
			expect(std::same_as<Unique<Tuple>, Tuple>, equal_to(true));
		});

		unit.test("Unique_getWithTupleOfMultipleDifferingElements_expectTupleOfSameElements", []()
		{
			using Tuple = std::tuple<Dummy<1>, Dummy<2>, Dummy<4>, Dummy<8>, Dummy<16>>;
			expect(std::same_as<Unique<Tuple>, Tuple>, equal_to(true));
		});

		unit.test("Unique_getWithTupleOfSomeDifferingAndSomeUniqueElements_expectTupleOfUniqueElementsInNoParticularOrder", []()
		{
			using Tuple = std::tuple<Stub<1>, Stub<2>, Stub<4>, Stub<4>, Stub<8>, Stub<4>, Stub<16>, Stub<32>, Stub<-87>, Stub<1>>;
			expect(From<Unique<Tuple>>::getSortedValues(), array(-87, 1, 2, 4, 8, 16, 32));
		});

		unit.test("Unique_getWithPairOfDifferingElements_expectTupleOfSameElements", []()
		{
			using Pair = std::pair<Dummy<1>, Dummy<2>>;
			using Tuple = std::tuple<Dummy<1>, Dummy<2>>;
			expect(std::same_as<Unique<Pair>, Tuple>, equal_to(true));
		});

		unit.test("Unique_getWithPairOfSameElements_expectTupleOfSingleElement", []()
		{
			using Pair = std::pair<Dummy<1>, Dummy<1>>;
			using Tuple = std::tuple<Dummy<1>>;
			expect(std::same_as<Unique<Pair>, Tuple>, equal_to(true));
		});

		unit.test("Unique_getWithEmptyArray_expectEmptyTuple", []()
		{
			using EmptyArray = std::array<Dummy<7>, 0>;
			using EmptyTuple = std::tuple<>;
			expect(std::same_as<Unique<EmptyArray>, EmptyTuple>, equal_to(true));
		});

		unit.test("Unique_getWithArrayOfSingleElement_expectTupleOfSameElement", []()
		{
			using Array = std::array<Dummy<123>, 1>;
			using Tuple = std::tuple<Dummy<123>>;
			expect(std::same_as<Unique<Array>, Tuple>, equal_to(true));
		});

		unit.test("Unique_getWithArrayOfMultipleElements_expectTupleOfSingleElement", []()
		{
			using Array = std::array<Dummy<-9>, 983>;
			using Tuple = std::tuple<Dummy<-9>>;
			expect(std::same_as<Unique<Array>, Tuple>, equal_to(true));
		});
	});
}
