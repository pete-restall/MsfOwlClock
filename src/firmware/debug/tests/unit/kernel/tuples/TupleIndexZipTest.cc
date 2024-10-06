#include <array>
#include <cstdint>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tuples/TupleIndexZip.hh"

using namespace mettle;

using namespace smeg::kernel::tuples;

namespace smeg::tests::unit::kernel::tuples
{
	suite<> tupleIndexZipTest("TupleIndexZip Test Suite", [](auto &unit)
	{
		unit.test("WithIndices_getWithEmptyTuple_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<TupleIndexZip<std::tuple<>>::WithIndices>, equal_to(0));
		});

		unit.test("WithIndices_getWithTupleContainingSingleElement_expectTupleWithOneValueAndZeroIndex", []()
		{
			using Zipped = TupleIndexZip<std::tuple<int>>;
			expect(typeid(Zipped::WithIndices) == typeid(
				std::tuple<
					TupleElementWithIndex<int, 0>>),
				equal_to(true));
		});

		unit.test("WithIndices_getWithTupleContainingTwoElements_expectTupleWithTwoValuesAndIncrementingIndices", []()
		{
			using Zipped = TupleIndexZip<std::tuple<float, char>>;
			expect(typeid(Zipped::WithIndices) == typeid(
				std::tuple<
					TupleElementWithIndex<float, 0>,
					TupleElementWithIndex<char, 1>>),
				equal_to(true));
		});

		unit.test("WithIndices_getWithTupleContainingThreeElements_expectTupleWithThreeValuesAndIncrementingIndices", []()
		{
			using Zipped = TupleIndexZip<std::tuple<float, char, bool>>;
			expect(typeid(Zipped::WithIndices) == typeid(
				std::tuple<
					TupleElementWithIndex<float, 0>,
					TupleElementWithIndex<char, 1>,
					TupleElementWithIndex<bool, 2>>),
				equal_to(true));
		});

		unit.test("WithIndices_getWithTupleContainingSevenElements_expectTupleWithSevenValuesAndIncrementingIndices", []()
		{
			using Zipped = TupleIndexZip<std::tuple<std::size_t, double, char, bool, std::array<int, 23>, std::tuple<int, float, bool>, short>>;
			expect(typeid(Zipped::WithIndices) == typeid(
				std::tuple<
					TupleElementWithIndex<std::size_t, 0>,
					TupleElementWithIndex<double, 1>,
					TupleElementWithIndex<char, 2>,
					TupleElementWithIndex<bool, 3>,
					TupleElementWithIndex<std::array<int, 23>, 4>,
					TupleElementWithIndex<std::tuple<int, float, bool>, 5>,
					TupleElementWithIndex<short, 6>>),
				equal_to(true));
		});

		unit.test("WithIndices_getWithNoTemplateArguments_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<TupleIndexZip<>::WithIndices>, equal_to(0));
		});

		unit.test("WithIndices_getWithSingleNonTupleTemplateArgument_expectTupleWithOneValueAndZeroIndex", []()
		{
			using Zipped = TupleIndexZip<int>;
			expect(typeid(Zipped::WithIndices) == typeid(
				std::tuple<
					TupleElementWithIndex<int, 0>>),
				equal_to(true));
		});

		unit.test("WithIndices_getWithTwoTemplateArguments_expectTupleWithTwoValuesAndIncrementingIndices", []()
		{
			using Zipped = TupleIndexZip<std::tuple<float>, char>;
			expect(typeid(Zipped::WithIndices) == typeid(
				std::tuple<
					TupleElementWithIndex<std::tuple<float>, 0>,
					TupleElementWithIndex<char, 1>>),
				equal_to(true));
		});

		unit.test("WithIndices_getWithThreeTemplateArguments_expectTupleWithThreeValuesAndIncrementingIndices", []()
		{
			using Zipped = TupleIndexZip<std::tuple<std::uint_least64_t, std::uintptr_t, nullptr_t>>;
			expect(typeid(Zipped::WithIndices) == typeid(
				std::tuple<
					TupleElementWithIndex<std::uint_least64_t, 0>,
					TupleElementWithIndex<std::uintptr_t, 1>,
					TupleElementWithIndex<std::nullptr_t, 2>>),
				equal_to(true));
		});

		unit.test("WithIndices_getWithTupleContainingFiveElements_expectTupleWithFiveValuesAndIncrementingIndices", []()
		{
			using Zipped = TupleIndexZip<std::tuple<std::tuple<double, bool>, char, bool, std::array<char, 7>, short>>;
			expect(typeid(Zipped::WithIndices) == typeid(
				std::tuple<
					TupleElementWithIndex<std::tuple<double, bool>, 0>,
					TupleElementWithIndex<char, 1>,
					TupleElementWithIndex<bool, 2>,
					TupleElementWithIndex<std::array<char, 7>, 3>,
					TupleElementWithIndex<short, 4>>),
				equal_to(true));
		});
	});
}
