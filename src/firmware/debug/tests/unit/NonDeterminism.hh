#ifndef __SMEG_TESTS_UNIT_NONDETERMINISM_HH
#define __SMEG_TESTS_UNIT_NONDETERMINISM_HH
#include <algorithm>
#include <cstdint>
#include <limits>
#include <random>
#include <ranges>
#include <span>
#include <vector>

namespace smeg::tests::unit
{
	template <typename T>
	std::vector<T> anyVectorOfSize(typename std::vector<T>::size_type size);

	template <typename T>
	T anyInClosedRange(T min, T max);

	template <typename T>
	std::span<T> anyNonEmptySpanIn(std::vector<T> &range);

	template <typename T>
	std::span<T> anySpanInClosedRangeSize(
		std::vector<T> &range,
		typename std::vector<T>::size_type minSize,
		typename std::vector<T>::size_type maxSize);

	template <typename T>
	std::span<T> anySpanInClosedRangeSize(std::vector<T> &range, typename std::vector<T>::size_type size);

	extern thread_local std::mt19937 randomGenerator;

	template <typename T>
	std::vector<T> anyVectorOfSize(typename std::vector<T>::size_type size)
	{
		std::uniform_int_distribution<T> distribution(
			std::numeric_limits<T>::min(),
			std::numeric_limits<T>::max());

		std::vector<T> data(size);
		std::generate(data.begin(), data.end(), [distribution]() mutable { return distribution(randomGenerator); });
		return data;
	}

	template <typename T>
	std::span<T> anyNonEmptySpanIn(std::vector<T> &range)
	{
		return anySpanInClosedRangeSize(range, 1, range.size());
	}

	template <typename T>
	std::span<T> anySpanInClosedRangeSize(
		std::vector<T> &range,
		typename std::vector<T>::size_type minSize,
		typename std::vector<T>::size_type maxSize)
	{
		auto numberOfElements = anyInClosedRange<typename std::vector<T>::size_type>(minSize, maxSize);
		return anySpanInClosedRangeSize(range, numberOfElements);
	}

	template <typename T>
	std::span<T> anySpanInClosedRangeSize(std::vector<T> &range, typename std::vector<T>::size_type size)
	{
		auto startIndex = anyInClosedRange<typename std::vector<T>::size_type>(0, range.size() - size - 1);
		return std::span(range.begin() + startIndex, size);
	}

	template <typename T>
	T anyInClosedRange(T min, T max)
	{
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(randomGenerator);
	}
}

#endif
