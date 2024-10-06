#include <array>
#include <cstdint>
#include <tuple>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/tuples/TupleProjection.hh"

using namespace mettle;

using namespace smeg::kernel::tuples;

namespace smeg::tests::unit::kernel::tuples
{
	template <typename T, std::size_t Index>
	struct DummyProjection
	{
		using AsTuple = std::tuple<>;
	};

	template <typename T, std::size_t... Indices>
	struct StubProjectedValue
	{
	};

	template <typename... T>
	struct StubFor
	{
	};

	using StubEmpty = StubFor<>;

	template <typename T>
	struct StubProjectionWithNoIndices
	{
		using AsTuple = std::tuple<StubProjectedValue<T>>;
	};

	template <typename... T>
	struct StubProjectionWithNoIndices<StubFor<T...>>
	{
		using AsTuple = std::tuple<StubProjectedValue<T>...>;
	};

	template <typename T, std::size_t InputIndex>
	struct StubProjectionWithInputIndex
	{
		using AsTuple = std::tuple<StubProjectedValue<T, InputIndex>>;
	};

	template <std::size_t InputIndex, typename... T>
	struct StubProjectionWithInputIndex<StubFor<T...>, InputIndex>
	{
		using AsTuple = std::tuple<StubProjectedValue<T, InputIndex>...>;
	};

	template <typename T, std::size_t InputIndex, std::size_t OutputIndex>
	struct StubProjectionWithInputAndOutputIndices
	{
		using AsTuple = std::tuple<StubProjectedValue<T, InputIndex, OutputIndex>>;
	};

	template <std::size_t InputIndex, std::size_t OutputIndex, typename... T>
	struct StubProjectionWithInputAndOutputIndices<StubFor<T...>, InputIndex, OutputIndex>
	{
		using AsTuple = std::tuple<StubProjectedValue<T, InputIndex, OutputIndex>...>;
	};

	suite<> tupleProjectionWithNoIndicesTest("TupleProjection (No Indices) Test Suite", [](auto &unit)
	{
		unit.test("Input_getWithEmptyTuple_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<TupleProjection<std::tuple<>, StubProjectionWithNoIndices>::Input>, equal_to(0));
		});

		unit.test("Input_get_expectSameTypeAsFirstTemplateArgument", []()
		{
			using Input1 = std::tuple<int>;
			using Input2 = std::tuple<float, double>;
			using Input3 = std::tuple<std::tuple<std::array<int, 7>, double, std::tuple<>>, std::array<float, 10>, std::size_t>;
			using Input5 = std::tuple<char, short, int, long, double>;

			std::array assertions
			{
				typeid(TupleProjection<Input1, StubProjectionWithNoIndices>::Input) == typeid(Input1),
				typeid(TupleProjection<Input2, StubProjectionWithNoIndices>::Input) == typeid(Input2),
				typeid(TupleProjection<Input3, StubProjectionWithNoIndices>::Input) == typeid(Input3),
				typeid(TupleProjection<Input5, StubProjectionWithNoIndices>::Input) == typeid(Input5)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("Output_getWithEmptyTuple_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<TupleProjection<std::tuple<>, StubProjectionWithNoIndices>::Output>, equal_to(0));
		});

		unit.test("Output_getWithTupleContainingSingleElement_expectTupleContainingOneProjectedElement", []()
		{
			expect(typeid(TupleProjection<std::tuple<double>, StubProjectionWithNoIndices>::Output) == typeid(std::tuple<StubProjectedValue<double>>), equal_to(true));
		});

		unit.test("Output_getWithTupleContainingTwoElements_expectTupleContainingTwoProjectedElements", []()
		{
			expect(typeid(TupleProjection<std::tuple<std::size_t, std::int64_t>, StubProjectionWithNoIndices>::Output) == typeid(
				std::tuple<
					StubProjectedValue<std::size_t>,
					StubProjectedValue<std::int64_t>>),
				equal_to(true));
		});

		unit.test("Output_getWithTupleContainingFiveElements_expectTupleContainingFiveProjectedElements", []()
		{
			expect(typeid(TupleProjection<std::tuple<char, char, int, std::tuple<double>, long>, StubProjectionWithNoIndices>::Output) == typeid(
				std::tuple<
					StubProjectedValue<char>,
					StubProjectedValue<char>,
					StubProjectedValue<int>,
					StubProjectedValue<std::tuple<double>>,
					StubProjectedValue<long>>),
				equal_to(true));
		});

		unit.test("Output_getWhenProjectionReturnsEmptyTuple_expectTupleContainingProjectedElements", []()
		{
			expect(typeid(TupleProjection<std::tuple<StubEmpty, double, StubEmpty, StubEmpty, int>, StubProjectionWithNoIndices>::Output) == typeid(
				std::tuple<
					StubProjectedValue<double>,
					StubProjectedValue<int>>),
				equal_to(true));
		});

		unit.test("Output_getWhenProjectionReturnsTupleWithMoreThanOneElement_expectTupleContainingProjectedElements", []()
		{
			expect(typeid(TupleProjection<std::tuple<int, std::tuple<int, float>, StubFor<char, short>, double>, StubProjectionWithNoIndices>::Output) == typeid(
				std::tuple<
					StubProjectedValue<int>,
					StubProjectedValue<std::tuple<int, float>>,
					StubProjectedValue<char>,
					StubProjectedValue<short>,
					StubProjectedValue<double>>),
				equal_to(true));
		});
	});

	suite<> tupleProjectionWithInputIndexTest("TupleProjection (Input Index) Test Suite", [](auto &unit)
	{
		unit.test("Input_getWithEmptyTuple_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<TupleProjection<std::tuple<>, StubProjectionWithInputIndex>::Input>, equal_to(0));
		});

		unit.test("Input_get_expectSameTypeAsFirstTemplateArgument", []()
		{
			using Input1 = std::tuple<int>;
			using Input2 = std::tuple<float, double>;
			using Input3 = std::tuple<std::tuple<std::array<int, 7>, double, std::tuple<>>, std::array<float, 10>, std::size_t>;
			using Input5 = std::tuple<char, short, int, long, double>;

			std::array assertions
			{
				typeid(TupleProjection<Input1, StubProjectionWithInputIndex>::Input) == typeid(Input1),
				typeid(TupleProjection<Input2, StubProjectionWithInputIndex>::Input) == typeid(Input2),
				typeid(TupleProjection<Input3, StubProjectionWithInputIndex>::Input) == typeid(Input3),
				typeid(TupleProjection<Input5, StubProjectionWithInputIndex>::Input) == typeid(Input5)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("Output_getWithEmptyTuple_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<TupleProjection<std::tuple<>, StubProjectionWithInputIndex>::Output>, equal_to(0));
		});

		unit.test("Output_getWithTupleContainingSingleElement_expectTupleContainingOneProjectedElement", []()
		{
			expect(typeid(TupleProjection<std::tuple<double>, StubProjectionWithInputIndex>::Output) == typeid(std::tuple<StubProjectedValue<double, 0>>), equal_to(true));
		});

		unit.test("Output_getWithTupleContainingTwoElements_expectTupleContainingTwoProjectedElements", []()
		{
			expect(typeid(TupleProjection<std::tuple<int, float>, StubProjectionWithInputIndex>::Output) == typeid(
				std::tuple<
					StubProjectedValue<int, 0>,
					StubProjectedValue<float, 1>>),
				equal_to(true));
		});

		unit.test("Output_getWithTupleContainingFiveElements_expectTupleContainingFiveProjectedElements", []()
		{
			expect(typeid(TupleProjection<std::tuple<int, float, double, std::tuple<short>, long>, StubProjectionWithInputIndex>::Output) == typeid(
				std::tuple<
					StubProjectedValue<int, 0>,
					StubProjectedValue<float, 1>,
					StubProjectedValue<double, 2>,
					StubProjectedValue<std::tuple<short>, 3>,
					StubProjectedValue<long, 4>>),
				equal_to(true));
		});

		unit.test("Output_getWhenProjectionReturnsEmptyTuple_expectTupleContainingProjectedElementsWithCorrectIndices", []()
		{
			expect(typeid(TupleProjection<std::tuple<StubEmpty, char, StubEmpty, double, long, StubEmpty>, StubProjectionWithInputIndex>::Output) == typeid(
				std::tuple<
					StubProjectedValue<char, 1>,
					StubProjectedValue<double, 3>,
					StubProjectedValue<long, 4>>),
				equal_to(true));
		});

		unit.test("Output_getWhenProjectionReturnsTupleWithMoreThanOneElement_expectTupleContainingProjectedElementsWithCorrectIndices", []()
		{
			expect(typeid(TupleProjection<std::tuple<StubFor<int, double>, char, StubFor<float, short, int>, double>, StubProjectionWithInputIndex>::Output) == typeid(
				std::tuple<
					StubProjectedValue<int, 0>,
					StubProjectedValue<double, 0>,
					StubProjectedValue<char, 1>,
					StubProjectedValue<float, 2>,
					StubProjectedValue<short, 2>,
					StubProjectedValue<int, 2>,
					StubProjectedValue<double, 3>>),
				equal_to(true));
		});
	});

	suite<> tupleProjectionWithInputAndOutputIndicesTest("TupleProjection (Input and Output Indices) Test Suite", [](auto &unit)
	{
		unit.test("Input_getWithEmptyTuple_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<TupleProjection<std::tuple<>, StubProjectionWithInputAndOutputIndices>::Input>, equal_to(0));
		});

		unit.test("Input_get_expectSameTypeAsFirstTemplateArgument", []()
		{
			using Input1 = std::tuple<int>;
			using Input2 = std::tuple<float, double>;
			using Input3 = std::tuple<std::tuple<std::array<int, 7>, double, std::tuple<>>, std::array<float, 10>, std::size_t>;
			using Input5 = std::tuple<char, short, int, long, double>;

			std::array assertions
			{
				typeid(TupleProjection<Input1, StubProjectionWithInputAndOutputIndices>::Input) == typeid(Input1),
				typeid(TupleProjection<Input2, StubProjectionWithInputAndOutputIndices>::Input) == typeid(Input2),
				typeid(TupleProjection<Input3, StubProjectionWithInputAndOutputIndices>::Input) == typeid(Input3),
				typeid(TupleProjection<Input5, StubProjectionWithInputAndOutputIndices>::Input) == typeid(Input5)
			};

			expect(assertions, each(equal_to(true)));
		});

		unit.test("Output_getWithEmptyTuple_expectEmptyTuple", []()
		{
			expect(std::tuple_size_v<TupleProjection<std::tuple<>, StubProjectionWithInputAndOutputIndices>::Output>, equal_to(0));
		});

		unit.test("Output_getWithTupleContainingSingleElement_expectTupleContainingOneProjectedElement", []()
		{
			expect(typeid(TupleProjection<std::tuple<double>, StubProjectionWithInputAndOutputIndices>::Output) == typeid(
				std::tuple<
					StubProjectedValue<double, 0, 0>>),
				equal_to(true));
		});

		unit.test("Output_getWithTupleContainingTwoElements_expectTupleContainingTwoProjectedElements", []()
		{
			expect(typeid(TupleProjection<std::tuple<int, float>, StubProjectionWithInputAndOutputIndices>::Output) == typeid(
				std::tuple<
					StubProjectedValue<int, 0, 0>,
					StubProjectedValue<float, 1, 1>>),
				equal_to(true));
		});

		unit.test("Output_getWithTupleContainingFiveElements_expectTupleContainingFiveProjectedElements", []()
		{
			expect(typeid(TupleProjection<std::tuple<int, float, double, std::tuple<short>, long>, StubProjectionWithInputAndOutputIndices>::Output) == typeid(
				std::tuple<
					StubProjectedValue<int, 0, 0>,
					StubProjectedValue<float, 1, 1>,
					StubProjectedValue<double, 2, 2>,
					StubProjectedValue<std::tuple<short>, 3, 3>,
					StubProjectedValue<long, 4, 4>>),
				equal_to(true));
		});

		unit.test("Output_getWhenProjectionReturnsEmptyTuple_expectTupleContainingProjectedElementsWithCorrectInputAndOutputIndices", []()
		{
			expect(typeid(TupleProjection<std::tuple<StubEmpty, char, StubEmpty, double, long, StubEmpty>, StubProjectionWithInputAndOutputIndices>::Output) == typeid(
				std::tuple<
					StubProjectedValue<char, 1, 0>,
					StubProjectedValue<double, 3, 1>,
					StubProjectedValue<long, 4, 2>>),
				equal_to(true));
		});

		unit.test("Output_getWhenProjectionReturnsTupleWithMoreThanOneElement_expectTupleContainingProjectedElementsWithCorrectInputAndOutputIndices", []()
		{
			expect(typeid(TupleProjection<std::tuple<StubFor<int, double>, char, StubFor<float, short, int>, double>, StubProjectionWithInputAndOutputIndices>::Output) == typeid(
				std::tuple<
					StubProjectedValue<int, 0, 0>,
					StubProjectedValue<double, 0, 0>,
					StubProjectedValue<char, 1, 2>,
					StubProjectedValue<float, 2, 3>,
					StubProjectedValue<short, 2, 3>,
					StubProjectedValue<int, 2, 3>,
					StubProjectedValue<double, 3, 6>>),
				equal_to(true));
		});
	});
}
