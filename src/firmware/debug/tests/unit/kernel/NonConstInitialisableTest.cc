#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/INonConstInitialisable.hh"

using namespace mettle;
using namespace smeg::kernel;

namespace smeg::tests::unit::kernel
{
	class ShouldBeNonConstInitialisable
	{
public:
		void initialise(void) { }
	};

	class ConstShouldBeNonConstInitialisable
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
		void initialise(void) { }
	};

	class WithArgumentsShouldNotBeInitialisable
	{
public:
		void initialise([[maybe_unused]] int _) { }
	};

	class NonVoidReturnShouldNotBeInitialisable
	{
public:
		int initialise(void) { return 0; }
	};

	suite<> nonConstInitialisableTest("INonConstInitialisable Tests", [](auto &unit)
	{
		unit.test("constInitialisable_testedAgainstConcept_expectTrue", []()
		{
			expect(INonConstInitialisable<ConstShouldBeNonConstInitialisable>, equal_to(true));
			expect(INonConstInitialisable<const ConstShouldBeNonConstInitialisable>, equal_to(true));
		});

		unit.test("nonConstInitialisable_testedAgainstConcept_expectTrue", []()
		{
			expect(INonConstInitialisable<ShouldBeNonConstInitialisable>, equal_to(true));
		});

		unit.test("constAndNonConstInitialisable_testedAgainstConcept_expectTrue", []()
		{
			expect(INonConstInitialisable<ShouldBeBothConstAndNonConstInitialisable>, equal_to(true));
			expect(INonConstInitialisable<const ShouldBeBothConstAndNonConstInitialisable>, equal_to(true));
		});

		unit.test("protectedInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(INonConstInitialisable<ProtectedShouldNotBeInitialisable>, equal_to(false));
		});

		unit.test("withArgumentsInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(INonConstInitialisable<WithArgumentsShouldNotBeInitialisable>, equal_to(false));
		});

		unit.test("nonVoidReturnInitialisable_testedAgainstConcept_expectFalse", []()
		{
			expect(INonConstInitialisable<NonVoidReturnShouldNotBeInitialisable>, equal_to(false));
		});
	});
}
