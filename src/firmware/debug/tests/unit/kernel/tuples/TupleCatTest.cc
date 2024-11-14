#include <array>
#include <concepts>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tuples/TupleCat.hh"

using namespace mettle;

using namespace smeg::kernel::tuples;

namespace smeg::tests::unit::kernel::tuples
{
	template <auto X>
	struct Dummy
	{
	};

	struct Unconstructable
	{
		Unconstructable(void) = delete;
	};

	using EmptyArray = std::array<Dummy<123>, 0>;
	using EmptyTuple = std::tuple<>;

	suite<> tupleCatTest("TupleCat Test Suite", [](auto &unit)
	{
		unit.test("TupleCat_getWithNoArguments_expectEmptyTuple", []()
		{
			expect(std::same_as<TupleCat<>, EmptyTuple>, equal_to(true));
		});

		unit.test("TupleCat_getWithEmptyTuple_expectEmptyTuple", []()
		{
			expect(std::same_as<TupleCat<EmptyTuple>, EmptyTuple>, equal_to(true));
		});

		unit.test("TupleCat_getWithSingleTuple_expectSameTuple", []()
		{
			using Tuple = std::tuple<Dummy<2>, Dummy<7>, Dummy<1>, Dummy<8>, Dummy<2>, Dummy<8>>;
			expect(std::same_as<TupleCat<Tuple>, Tuple>, equal_to(true));
		});

		unit.test("TupleCat_getWithMultipleTuples_expectConcatenationOfTupleElementsIntoSingleTuple", []()
		{
			using Tuple1 = std::tuple<Dummy<1>, Dummy<2>>;
			using Tuple2 = std::tuple<Dummy<3>>;
			using Tuple3 = std::tuple<Dummy<4>, Dummy<5>, Dummy<99>>;
			expect(std::same_as<TupleCat<Tuple1, Tuple2, Tuple3>, std::tuple<Dummy<1>, Dummy<2>, Dummy<3>, Dummy<4>, Dummy<5>, Dummy<99>>>, equal_to(true));
		});

		unit.test("TupleCat_getWithTuplesContainingUnconstructableElements_expectConcatenationOfTupleElementsIntoSingleTuple", []()
		{
			using Tuple1 = std::tuple<Unconstructable, Dummy<2>, Dummy<4>>;
			using Tuple2 = std::tuple<Unconstructable>;
			using Tuple3 = std::tuple<Dummy<6>, Dummy<8>, Unconstructable>;
			expect(
				std::same_as<
					TupleCat<Tuple1, Tuple2, Tuple3>,
					std::tuple<Unconstructable, Dummy<2>, Dummy<4>, Unconstructable, Dummy<6>, Dummy<8>, Unconstructable>>,
				equal_to(true));
		});

		unit.test("TupleCat_getWithPair_expectTupleOfBothElements", []()
		{
			using Pair = std::pair<Dummy<4>, Dummy<2>>;
			expect(std::same_as<TupleCat<Pair>, std::tuple<Dummy<4>, Dummy<2>>>, equal_to(true));
		});

		unit.test("TupleCat_getWithMultiplePairs_expectConcatenationOfPairElementsIntoSingleTuple", []()
		{
			using Pair1 = std::pair<Dummy<1>, Dummy<1>>;
			using Pair2 = std::pair<Dummy<2>, Dummy<3>>;
			expect(std::same_as<TupleCat<Pair1, Pair2>, std::tuple<Dummy<1>, Dummy<1>, Dummy<2>, Dummy<3>>>, equal_to(true));
		});

		unit.test("TupleCat_getWithPairsContainingUnconstructable_expectConcatenationOfPairElementsIntoSingleTuple", []()
		{
			using Pair1 = std::pair<Dummy<1>, Unconstructable>;
			using Pair2 = std::pair<Unconstructable, Dummy<3>>;
			expect(std::same_as<TupleCat<Pair1, Pair2>, std::tuple<Dummy<1>, Unconstructable, Unconstructable, Dummy<3>>>, equal_to(true));
		});

		unit.test("TupleCat_getWithEmptyArray_expectEmptyTuple", []()
		{
			expect(std::same_as<TupleCat<EmptyArray>, EmptyTuple>, equal_to(true));
		});

		unit.test("TupleCat_getWithArray_expectTupleOfArrayElements", []()
		{
			using Array = std::array<Dummy<6>, 3>;
			expect(std::same_as<TupleCat<Array>, std::tuple<Dummy<6>, Dummy<6>, Dummy<6>>>, equal_to(true));
		});

		unit.test("TupleCat_getWithMultipleArrays_expectConcatenationOfArrayElementsIntoSingleTuple", []()
		{
			using Array1 = std::array<Dummy<1>, 3>;
			using Array2 = std::array<Dummy<2>, 2>;
			expect(std::same_as<TupleCat<Array1, Array2>, std::tuple<Dummy<1>, Dummy<1>, Dummy<1>, Dummy<2>, Dummy<2>>>, equal_to(true));
		});

		unit.test("TupleCat_getWithArraysContainingUnconstructableElements_expectConcatenationOfArrayElementsIntoSingleTuple", []()
		{
			using Array1 = std::array<Unconstructable, 2>;
			using Array2 = std::array<Dummy<2>, 3>;
			expect(std::same_as<TupleCat<Array1, Array2>, std::tuple<Unconstructable, Unconstructable, Dummy<2>, Dummy<2>, Dummy<2>>>, equal_to(true));
		});

		unit.test("TupleCat_getWithCombinationOfTupleLikeContainers_expectConcatenationOfElementsIntoSingleTuple", []()
		{
			using Array = std::array<Dummy<99>, 3>;
			using Pair = std::pair<Dummy<-22>, Unconstructable>;
			using Tuple = std::tuple<Dummy<0>, Dummy<1>, Dummy<2>, Dummy<4>, Dummy<8>>;
			expect(
				std::same_as<TupleCat<Array, Pair, Tuple>,
				std::tuple<
					Dummy<99>, Dummy<99>, Dummy<99>,
					Dummy<-22>, Unconstructable,
					Dummy<0>, Dummy<1>, Dummy<2>, Dummy<4>, Dummy<8>>>,
				equal_to(true));
		});
	});
}
