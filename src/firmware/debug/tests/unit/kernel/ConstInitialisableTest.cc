#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/IConstInitialisable.hh"

using namespace mettle;
using namespace smeg::kernel;

namespace smeg::tests::unit::kernel
{
	class ShouldNotBeConstInitialisable
	{
	public:
		void initialise(void) { }
	};

	class ShouldBeConstInitialisable
	{
	public:
		void initialise(void) const { }
	};

	class ShouldBeBothConstAndNonConstInitialisable
	{
	public:
		void initialise(void) { }
		void initialise(void) const { }
	};

	class ProtectedShouldNotBeInitialisable
	{
	protected:
		void initialise(void) const { }
	};

	class WithArgumentsShouldNotBeInitialisable
	{
	public:
		void initialise([[maybe_unused]] int _) const { }
	};

	class NonVoidReturnShouldNotBeInitialisable
	{
	public:
		int initialise(void) const { return 0; }
	};

	suite<> constInitialisableTest("IConstInitialisable Tests", [](auto &unit)
	{
		unit.test("constInitialisable_testedAgainstConcept_expectTrue", []()
		{
			expect(IConstInitialisable<const ShouldBeConstInitialisable>, equal_to(true));
		});

		unit.test("nonConstInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(IConstInitialisable<const ShouldNotBeConstInitialisable>, equal_to(false));
		});

		unit.test("constAndNonConstInitialisable_testedAgainstConcept_expectTrue", []()
		{
			expect(IConstInitialisable<const ShouldBeBothConstAndNonConstInitialisable>, equal_to(true));
		});

		unit.test("protectedInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(IConstInitialisable<const ProtectedShouldNotBeInitialisable>, equal_to(false));
		});

		unit.test("withArgumentsInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(IConstInitialisable<const WithArgumentsShouldNotBeInitialisable>, equal_to(false));
		});

		unit.test("nonVoidReturnInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(IConstInitialisable<const NonVoidReturnShouldNotBeInitialisable>, equal_to(false));
		});
	});
}
