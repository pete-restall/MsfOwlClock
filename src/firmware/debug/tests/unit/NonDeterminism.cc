#include <random>
#include <ranges>

#include "NonDeterminism.hh"

namespace smeg::tests::unit
{
	template <typename T = std::mt19937, std::size_t N = T::state_size * sizeof(typename T::result_type)>
	static T properlySeededRandomGenerator(void)
	{
		std::random_device source;
		auto randomData =
			std::views::iota(std::size_t(), (N - 1) / sizeof(source()) + 1) |
			std::views::transform([&](auto) { return source(); });

		std::seed_seq seeds(std::begin(randomData), std::end(randomData));
		return T(seeds);
	}

	thread_local std::mt19937 randomGenerator(properlySeededRandomGenerator());
}
