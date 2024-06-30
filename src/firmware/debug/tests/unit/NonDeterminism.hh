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
	template<typename T>
	std::vector<T> anyVectorOfSize(size_t size);

	template<typename T>
	T anyInClosedRange(T min, T max);

	template<typename T>
	std::span<T> anyNonEmptySpanIn(std::vector<T> &range);

	extern thread_local std::default_random_engine randomGenerator;

	template<typename T>
	std::vector<T> anyVectorOfSize(size_t size)
	{
		std::uniform_int_distribution<T> distribution(
			std::numeric_limits<T>::min(),
			std::numeric_limits<T>::max());

		std::vector<T> data(size);
		std::generate(data.begin(), data.end(), [distribution]() mutable { return distribution(randomGenerator); });
		return data;
	}

	template<typename T>
	std::span<T> anyNonEmptySpanIn(std::vector<T> &range)
	{
		auto numberOfElements = anyInClosedRange<std::size_t>(1, range.size());
		auto startIndex = anyInClosedRange<std::size_t>(0, range.size() - numberOfElements - 1);
		return std::span(range.begin() + startIndex, numberOfElements);
	}

	template<typename T>
	T anyInClosedRange(T min, T max)
	{
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(randomGenerator);
	}
}

#endif
