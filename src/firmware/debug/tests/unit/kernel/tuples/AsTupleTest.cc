#include <array>
#include <concepts>
#include <tuple>
#include <utility>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tuples/AsTuple.hh"

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

	suite<> asTupleTest("AsTuple Test Suite", [](auto &unit)
	{
		unit.test("AsTuple_getWithEmptyTuple_expectEmptyTuple", []()
		{
			using EmptyTuple = std::tuple<>;
			expect(std::same_as<AsTuple<EmptyTuple>, EmptyTuple>, equal_to(true));
		});

		unit.test("AsTuple_getWithTupleOfSingleElement_expectTupleOfSameElement", []()
		{
			using Tuple = std::tuple<Dummy<-99>>;
			expect(std::same_as<AsTuple<Tuple>, Tuple>, equal_to(true));
		});

		unit.test("AsTuple_getWithTupleOfMultipleElements_expectTupleOfSameElements", []()
		{
			using Tuple = std::tuple<Dummy<3>, Dummy<1>, Dummy<4>, Dummy<1>, Dummy<5>, Dummy<9>>;
			expect(std::same_as<AsTuple<Tuple>, Tuple>, equal_to(true));
		});

		unit.test("AsTuple_getWithTupleOfTuples_expectSameTupleOfTuples", []()
		{
			using TupleOfTuples = std::tuple<std::tuple<Dummy<0>>, std::tuple<Dummy<1>, Dummy<1>, Dummy<2>>, std::tuple<Dummy<3>>>;
			expect(std::same_as<AsTuple<TupleOfTuples>, TupleOfTuples>, equal_to(true));
		});

		unit.test("AsTuple_getWithTupleOfUnconstructableClass_expectSameTuple", []()
		{
			using TupleOfUnconstructable = std::tuple<Unconstructable>;
			expect(std::same_as<AsTuple<TupleOfUnconstructable>, TupleOfUnconstructable>, equal_to(true));
		});

		unit.test("AsTuple_getWithPair_expectTupleOfSameTypes", []()
		{
			using Pair = std::pair<Dummy<1>, Dummy<2>>;
			expect(std::same_as<AsTuple<Pair>, std::tuple<Dummy<1>, Dummy<2>>>, equal_to(true));
		});

		unit.test("AsTuple_getWithPairContainingTuple_expectTupleOfSameTypes", []()
		{
			using Pair = std::pair<std::tuple<Dummy<1>>, Dummy<2>>;
			expect(std::same_as<AsTuple<Pair>, std::tuple<std::tuple<Dummy<1>>, Dummy<2>>>, equal_to(true));
		});

		unit.test("AsTuple_getWithPairContainingUnconstructableClass_expectTupleOfSameTypes", []()
		{
			using PairContainingUnconstructable = std::pair<Dummy<87612>, Unconstructable>;
			using TupleContainingUnconstructable = std::tuple<Dummy<87612>, Unconstructable>;
			expect(std::same_as<AsTuple<PairContainingUnconstructable>, TupleContainingUnconstructable>, equal_to(true));
		});

		unit.test("AsTuple_getWithEmptyArray_expectEmptyTuple", []()
		{
			using EmptyArray = std::array<Dummy<3>, 0>;
			using EmptyTuple = std::tuple<>;
			expect(std::same_as<AsTuple<EmptyArray>, EmptyTuple>, equal_to(true));
		});

		unit.test("AsTuple_getWithArrayOfSingleElement_expectTupleOfSameElement", []()
		{
			using Array = std::array<Dummy<-42>, 1>;
			using Tuple = std::tuple<Dummy<-42>>;
			expect(std::same_as<AsTuple<Array>, Tuple>, equal_to(true));
		});

		unit.test("AsTuple_getWithArrayOfMultipleElements_expectTupleOfSameRepeatedElement", []()
		{
			using Array = std::array<Dummy<77>, 7>;
			using Tuple = std::tuple<Dummy<77>, Dummy<77>, Dummy<77>, Dummy<77>, Dummy<77>, Dummy<77>, Dummy<77>>;
			expect(std::same_as<AsTuple<Array>, Tuple>, equal_to(true));
		});

		unit.test("AsTuple_getWithArrayOfTuples_expectTupleOfTuples", []()
		{
			using ArrayOfTuples = std::array<std::tuple<Dummy<123>>, 3>;
			using TupleOfTuples = std::tuple<std::tuple<Dummy<123>>, std::tuple<Dummy<123>>, std::tuple<Dummy<123>>>;
			expect(std::same_as<AsTuple<ArrayOfTuples>, TupleOfTuples>, equal_to(true));
		});

		unit.test("AsTuple_getWithArrayOfUnconstructables_expectTupleOfSameTypes", []()
		{
			using ArrayOfUnconstructables = std::array<Unconstructable, 3>;
			using TupleOfUnconstructables = std::tuple<Unconstructable, Unconstructable, Unconstructable>;
			expect(std::same_as<AsTuple<ArrayOfUnconstructables>, TupleOfUnconstructables>, equal_to(true));
		});
	});
}
