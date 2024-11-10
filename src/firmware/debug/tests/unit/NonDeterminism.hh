#ifndef __SMEG_TESTS_UNIT_NONDETERMINISM_HH
#define __SMEG_TESTS_UNIT_NONDETERMINISM_HH
#include <algorithm>
#include <limits>
#include <random>
#include <ranges>
#include <span>
#include <vector>

namespace smeg::tests::unit
{
	template <std::integral T>
	std::vector<T> anyVectorOfSize(typename std::vector<T>::size_type size);

	template <std::integral T>
	T anyInClosedRange(T min, T max);

	template <std::integral T>
	std::span<T> anyNonEmptySpanIn(std::vector<T> &range);

	template <std::integral T>
	std::span<T> anySpanInClosedRangeSize(
		std::vector<T> &range,
		typename std::vector<T>::size_type minSize,
		typename std::vector<T>::size_type maxSize);

	template <std::integral T>
	std::span<T> anySpanInClosedRangeSize(std::vector<T> &range, typename std::vector<T>::size_type size);

	extern thread_local std::mt19937 randomGenerator;

	template <std::integral T>
	std::vector<T> anyVectorOfSize(typename std::vector<T>::size_type size)
	{
		std::uniform_int_distribution<T> distribution(
			std::numeric_limits<T>::min(),
			std::numeric_limits<T>::max());

		std::vector<T> data(size);
		std::generate(data.begin(), data.end(), [distribution]() mutable { return distribution(randomGenerator); });
		return data;
	}

	template <std::integral T>
	std::span<T> anyNonEmptySpanIn(std::vector<T> &range)
	{
		return anySpanInClosedRangeSize(range, 1, range.size());
	}

	template <std::integral T>
	std::span<T> anySpanInClosedRangeSize(
		std::vector<T> &range,
		typename std::vector<T>::size_type minSize,
		typename std::vector<T>::size_type maxSize)
	{
		auto numberOfElements = anyInClosedRange<typename std::vector<T>::size_type>(minSize, maxSize);
		return anySpanInClosedRangeSize(range, numberOfElements);
	}

	template <std::integral T>
	std::span<T> anySpanInClosedRangeSize(std::vector<T> &range, typename std::vector<T>::size_type size)
	{
		auto startIndex = anyInClosedRange<typename std::vector<T>::size_type>(0, range.size() - size - 1);
		return std::span(range.begin() + startIndex, size);
	}

	template <std::integral T>
	T anyInClosedRange(T min, T max)
	{
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(randomGenerator);
	}

	template <std::integral T>
	T anyValueOf(void)
	{
		return anyInClosedRange(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
	}
}

#endif
