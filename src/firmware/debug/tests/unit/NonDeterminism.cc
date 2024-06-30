#include <random>

#include "NonDeterminism.hh"

namespace smeg::tests::unit
{
	thread_local std::default_random_engine randomGenerator;
}
