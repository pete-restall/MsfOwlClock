#include <atomic>
#include <ranges>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/ChainedInitialisation.hh"

#include "../CallRecorder.hh"
#include "../NonDeterminism.hh"
#include "../ViewUtilities.hh"
#include "InitialisableTestDoubles.hh"
#include "MockConstInitialisable.hh"
#include "MockNonConstInitialisable.hh"

using namespace mettle;
using namespace smeg::kernel;

namespace smeg::tests::unit::kernel
{
	class Fixture
	{
private:
		typedef CallRecorder<>::CallCountInt CallCountInt;
		std::atomic<CallCountInt> callSequence;
		InitialisableTestDoubles initialisableTestDoubles;

public:
		Fixture() :
			callSequence(0),
			initialisableTestDoubles(this->callSequence)
		{
		}

		MockNonConstInitialisable mockNonConstInitialisable(void)
		{
			return this->initialisableTestDoubles.mockNonConst();
		}

		MockConstInitialisable mockConstInitialisable(void)
		{
			return this->initialisableTestDoubles.mockConst();
		}
	};

	suite<Fixture> chainedInitialisationTest("ChainedInitialisation Tests", [](auto &unit)
	{
		unit.test("constructor_constCalledWithConstInitialiser_expectInitialiserIsNotCalled", [](auto &fixture)
		{
			const MockConstInitialisable initialiser(fixture.mockConstInitialisable());
			const ChainedInitialisation chain(initialiser);
			expect(initialiser.callsToConstInitialise().count(), equal_to(0));
		});

		unit.test("constructor_constCalledWithNonConstInitialiser_expectInitialiserIsNotCalled", [](auto &fixture)
		{
			MockNonConstInitialisable initialiser(fixture.mockNonConstInitialisable());
			const ChainedInitialisation chain(initialiser);
			expect(initialiser.callsToNonConstInitialise().count(), equal_to(0));
		});

		unit.test("constructor_nonConstCalledWithConstInitialiser_expectInitialiserIsNotCalled", [](auto &fixture)
		{
			const MockConstInitialisable initialiser(fixture.mockConstInitialisable());
			ChainedInitialisation chain(initialiser);
			expect(initialiser.callsToConstInitialise().count(), equal_to(0));
		});

		unit.test("constructor_nonConstCalledWithNonConstInitialiser_expectInitialiserIsNotCalled", [](auto &fixture)
		{
			MockNonConstInitialisable initialiser(fixture.mockNonConstInitialisable());
			ChainedInitialisation chain(initialiser);
			expect(initialiser.callsToNonConstInitialise().count(), equal_to(0));
		});

		unit.test("initialise_constCalledWhenGivenSingleConstInitialiser_expectInitialiserIsCalledOnce", [](auto &fixture)
		{
			const MockConstInitialisable initialiser(fixture.mockConstInitialisable());
			const ChainedInitialisation chain(initialiser);
			chain.initialise();
			expect(initialiser.callsToConstInitialise().count(), equal_to(1));
		});

		unit.test("initialise_nonConstCalledWhenGivenSingleNonConstInitialiser_expectInitialiserIsCalledOnce", [](auto &fixture)
		{
			MockNonConstInitialisable initialiser(fixture.mockNonConstInitialisable());
			ChainedInitialisation chain(initialiser);
			chain.initialise();
			expect(initialiser.callsToNonConstInitialise().count(), equal_to(1));
		});

		unit.test("initialise_nonConstCalledWhenGivenSinglConstInitialiser_expectInitialiserIsCalledOnce", [](auto &fixture)
		{
			const MockConstInitialisable initialiser(fixture.mockConstInitialisable());
			ChainedInitialisation chain(initialiser);
			chain.initialise();
			expect(initialiser.callsToConstInitialise().count(), equal_to(1));
		});

		unit.test("initialise_constCalledMoreThanOnceWhenGivenSingleInitialiser_expectInitialiserIsCalledEachTime", [](auto &fixture)
		{
			const MockConstInitialisable initialiser(fixture.mockConstInitialisable());
			const ChainedInitialisation chain(initialiser);
			auto numberOfChainInitialiseCalls = anyInClosedRange(2, 10);
			for (auto i = 0; i < numberOfChainInitialiseCalls; i++)
				chain.initialise();

			expect(initialiser.callsToConstInitialise().count(), equal_to(numberOfChainInitialiseCalls));
		});

		unit.test("initialise_nonConstCalledMoreThanOnceWhenGivenSingleInitialiser_expectInitialiserIsCalledEachTime", [](auto &fixture)
		{
			MockNonConstInitialisable initialiser(fixture.mockNonConstInitialisable());
			ChainedInitialisation chain(initialiser);
			auto numberOfChainInitialiseCalls = anyInClosedRange(2, 10);
			for (auto i = 0; i < numberOfChainInitialiseCalls; i++)
				chain.initialise();

			expect(initialiser.callsToNonConstInitialise().count(), equal_to(numberOfChainInitialiseCalls));
		});

		unit.test("initialise_constCalledWhenMultipleInitialisers_expectEachInitialiserIsCalledOnce", [](auto &fixture)
		{
			const std::vector initialisers{
				fixture.mockConstInitialisable(),
				fixture.mockConstInitialisable(),
				fixture.mockConstInitialisable()
			};
			const ChainedInitialisation chain(initialisers[0], initialisers[1], initialisers[2]);
			chain.initialise();

			expect(initialisers, each(
				filter([](auto &&init) { return init.callsToConstInitialise().count(); },
				equal_to(1))));
		});

		unit.test("initialise_nonConstCalledWhenMultipleInitialisers_expectEachInitialiserIsCalledOnce", [](auto &fixture)
		{
			const std::vector initialisers{
				fixture.mockNonConstInitialisable(),
				fixture.mockNonConstInitialisable(),
				fixture.mockNonConstInitialisable()
			};
			ChainedInitialisation chain(initialisers[0], initialisers[1], initialisers[2]);
			chain.initialise();

			expect(initialisers, each(
				filter([](auto &&init) { return init.callsToNonConstInitialise().count(); },
				equal_to(1))));
		});

		unit.test("initialise_constCalledWhenMultipleInitialisers_expectEachInitialiserIsCalledInOrder", [](auto &fixture)
		{
			const std::vector initialisers{
				fixture.mockConstInitialisable(),
				fixture.mockConstInitialisable(),
				fixture.mockConstInitialisable()
			};
			const ChainedInitialisation chain(initialisers[0], initialisers[1], initialisers[2]);
			chain.initialise();

			const std::vector callsToInitialisers{
				toVector(initialisers[0].callsToConstInitialise().getCallSequences()),
				toVector(initialisers[1].callsToConstInitialise().getCallSequences()),
				toVector(initialisers[2].callsToConstInitialise().getCallSequences())
			};
			expect(callsToInitialisers[0], all(less(callsToInitialisers[1])));
			expect(callsToInitialisers[1], all(less(callsToInitialisers[2])));
		});

		unit.test("initialise_nonConstCalledWhenMultipleInitialisers_expectEachInitialiserIsCalledInOrder", [](auto &fixture)
		{
			const std::vector initialisers{
				fixture.mockNonConstInitialisable(),
				fixture.mockNonConstInitialisable(),
				fixture.mockNonConstInitialisable()
			};
			ChainedInitialisation chain(initialisers[0], initialisers[1], initialisers[2]);
			chain.initialise();

			const std::vector callsToInitialisers{
				toVector(initialisers[0].callsToNonConstInitialise().getCallSequences()),
				toVector(initialisers[1].callsToNonConstInitialise().getCallSequences()),
				toVector(initialisers[2].callsToNonConstInitialise().getCallSequences())
			};
			expect(callsToInitialisers[0], all(less(callsToInitialisers[1])));
			expect(callsToInitialisers[1], all(less(callsToInitialisers[2])));
		});
	});
}
