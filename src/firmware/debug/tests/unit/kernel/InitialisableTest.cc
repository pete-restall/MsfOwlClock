#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/IInitialisable.hh"

using namespace mettle;
using namespace smeg::kernel;

namespace smeg::tests::unit::kernel
{
	class ShouldBeNonConstInitialisable
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

	suite<> initialisableTest("IInitialisable Tests", [](auto &unit)
	{
		unit.test("constInitialisable_testedAgainstConcept_expectTrue", []()
		{
			expect(IInitialisable<const ShouldBeConstInitialisable>, equal_to(true));
		});

		unit.test("nonConstInitialisable_testedAgainstConcept_expectTrue", []()
		{
			expect(IInitialisable<ShouldBeNonConstInitialisable>, equal_to(true));
		});

		unit.test("constAndNonConstInitialisable_testedAgainstConcept_expectTrue", []()
		{
			expect(IInitialisable<ShouldBeBothConstAndNonConstInitialisable>, equal_to(true));
			expect(IInitialisable<const ShouldBeBothConstAndNonConstInitialisable>, equal_to(true));
		});

		unit.test("protectedInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(IInitialisable<ProtectedShouldNotBeInitialisable>, equal_to(false));
			expect(IInitialisable<const ProtectedShouldNotBeInitialisable>, equal_to(false));
		});

		unit.test("withArgumentsInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(IInitialisable<WithArgumentsShouldNotBeInitialisable>, equal_to(false));
			expect(IInitialisable<const WithArgumentsShouldNotBeInitialisable>, equal_to(false));
		});

		unit.test("nonVoidReturnInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(IInitialisable<NonVoidReturnShouldNotBeInitialisable>, equal_to(false));
			expect(IInitialisable<const NonVoidReturnShouldNotBeInitialisable>, equal_to(false));
		});
	});
}
