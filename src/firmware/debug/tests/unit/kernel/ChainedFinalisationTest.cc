#include <atomic>
#include <ranges>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/ChainedFinalisation.hh"

#include "../CallRecorder.hh"
#include "../NonDeterminism.hh"
#include "../ViewUtilities.hh"
#include "FinalisableTestDoubles.hh"
#include "MockConstFinalisable.hh"
#include "MockNonConstFinalisable.hh"

using namespace mettle;
using namespace smeg::kernel;

namespace smeg::tests::unit::kernel
{
	class Fixture
	{
	private:
		using CallCountInt = CallRecorder<>::CallCountInt;
		std::atomic<CallCountInt> callSequence;
		FinalisableTestDoubles finalisableTestDoubles;

	public:
		Fixture() :
			callSequence(0),
			finalisableTestDoubles(this->callSequence)
		{
		}

		MockNonConstFinalisable mockNonConstFinalisable(void)
		{
			return this->finalisableTestDoubles.mockNonConst();
		}

		MockConstFinalisable mockConstFinalisable(void)
		{
			return this->finalisableTestDoubles.mockConst();
		}
	};

	suite<Fixture> chainedFinalisationTest("ChainedFinalisation Tests", [](auto &unit)
	{
		unit.test("constructor_constCalledWithConstFinaliser_expectFinaliserIsNotCalled", [](auto &fixture)
		{
			const MockConstFinalisable finaliser(fixture.mockConstFinalisable());
			const ChainedFinalisation chain(finaliser);
			expect(finaliser.callsToConstFinalise().count(), equal_to(0));
		});

		unit.test("constructor_constCalledWithNonConstFinaliser_expectFinaliserIsNotCalled", [](auto &fixture)
		{
			MockNonConstFinalisable finaliser(fixture.mockNonConstFinalisable());
			const ChainedFinalisation chain(finaliser);
			expect(finaliser.callsToNonConstFinalise().count(), equal_to(0));
		});

		unit.test("constructor_nonConstCalledWithConstFinaliser_expectFinaliserIsNotCalled", [](auto &fixture)
		{
			const MockConstFinalisable finaliser(fixture.mockConstFinalisable());
			ChainedFinalisation chain(finaliser);
			expect(finaliser.callsToConstFinalise().count(), equal_to(0));
		});

		unit.test("constructor_nonConstCalledWithNonConstFinaliser_expectFinaliserIsNotCalled", [](auto &fixture)
		{
			MockNonConstFinalisable finaliser(fixture.mockNonConstFinalisable());
			ChainedFinalisation chain(finaliser);
			expect(finaliser.callsToNonConstFinalise().count(), equal_to(0));
		});

		unit.test("finalise_constCalledWhenGivenSingleConstFinaliser_expectFinaliserIsCalledOnce", [](auto &fixture)
		{
			const MockConstFinalisable finaliser(fixture.mockConstFinalisable());
			const ChainedFinalisation chain(finaliser);
			chain.finalise();
			expect(finaliser.callsToConstFinalise().count(), equal_to(1));
		});

		unit.test("finalise_nonConstCalledWhenGivenSingleNonConstFinaliser_expectFinaliserIsCalledOnce", [](auto &fixture)
		{
			MockNonConstFinalisable finaliser(fixture.mockNonConstFinalisable());
			ChainedFinalisation chain(finaliser);
			chain.finalise();
			expect(finaliser.callsToNonConstFinalise().count(), equal_to(1));
		});

		unit.test("finalise_nonConstCalledWhenGivenSinglConstFinaliser_expectFinaliserIsCalledOnce", [](auto &fixture)
		{
			const MockConstFinalisable finaliser(fixture.mockConstFinalisable());
			ChainedFinalisation chain(finaliser);
			chain.finalise();
			expect(finaliser.callsToConstFinalise().count(), equal_to(1));
		});

		unit.test("finalise_constCalledMoreThanOnceWhenGivenSingleFinaliser_expectFinaliserIsCalledEachTime", [](auto &fixture)
		{
			const MockConstFinalisable finaliser(fixture.mockConstFinalisable());
			const ChainedFinalisation chain(finaliser);
			auto numberOfChainFinaliseCalls = anyInClosedRange(2, 10);
			for (auto i = 0; i < numberOfChainFinaliseCalls; i++)
				chain.finalise();

			expect(finaliser.callsToConstFinalise().count(), equal_to(numberOfChainFinaliseCalls));
		});

		unit.test("finalise_nonConstCalledMoreThanOnceWhenGivenSingleFinaliser_expectFinaliserIsCalledEachTime", [](auto &fixture)
		{
			MockNonConstFinalisable finaliser(fixture.mockNonConstFinalisable());
			ChainedFinalisation chain(finaliser);
			auto numberOfChainFinaliseCalls = anyInClosedRange(2, 10);
			for (auto i = 0; i < numberOfChainFinaliseCalls; i++)
				chain.finalise();

			expect(finaliser.callsToNonConstFinalise().count(), equal_to(numberOfChainFinaliseCalls));
		});

		unit.test("finalise_constCalledWhenMultipleFinalisers_expectEachFinaliserIsCalledOnce", [](auto &fixture)
		{
			const std::vector finalisers{
				fixture.mockConstFinalisable(),
				fixture.mockConstFinalisable(),
				fixture.mockConstFinalisable()
			};
			const ChainedFinalisation chain(finalisers[0], finalisers[1], finalisers[2]);
			chain.finalise();

			expect(finalisers, each(
				filter([](auto &&init) { return init.callsToConstFinalise().count(); },
				equal_to(1))));
		});

		unit.test("finalise_nonConstCalledWhenMultipleFinalisers_expectEachFinaliserIsCalledOnce", [](auto &fixture)
		{
			const std::vector finalisers{
				fixture.mockNonConstFinalisable(),
				fixture.mockNonConstFinalisable(),
				fixture.mockNonConstFinalisable()
			};
			ChainedFinalisation chain(finalisers[0], finalisers[1], finalisers[2]);
			chain.finalise();

			expect(finalisers, each(
				filter([](auto &&init) { return init.callsToNonConstFinalise().count(); },
				equal_to(1))));
		});

		unit.test("finalise_constCalledWhenMultipleFinalisers_expectEachFinaliserIsCalledInOrder", [](auto &fixture)
		{
			const std::vector finalisers{
				fixture.mockConstFinalisable(),
				fixture.mockConstFinalisable(),
				fixture.mockConstFinalisable()
			};
			const ChainedFinalisation chain(finalisers[0], finalisers[1], finalisers[2]);
			chain.finalise();

			const std::vector callsToFinalisers{
				toVector(finalisers[0].callsToConstFinalise().getCallSequences()),
				toVector(finalisers[1].callsToConstFinalise().getCallSequences()),
				toVector(finalisers[2].callsToConstFinalise().getCallSequences())
			};
			expect(callsToFinalisers[0], all(less(callsToFinalisers[1])));
			expect(callsToFinalisers[1], all(less(callsToFinalisers[2])));
		});

		unit.test("finalise_nonConstCalledWhenMultipleFinalisers_expectEachFinaliserIsCalledInOrder", [](auto &fixture)
		{
			const std::vector finalisers{
				fixture.mockNonConstFinalisable(),
				fixture.mockNonConstFinalisable(),
				fixture.mockNonConstFinalisable()
			};
			ChainedFinalisation chain(finalisers[0], finalisers[1], finalisers[2]);
			chain.finalise();

			const std::vector callsToFinalisers{
				toVector(finalisers[0].callsToNonConstFinalise().getCallSequences()),
				toVector(finalisers[1].callsToNonConstFinalise().getCallSequences()),
				toVector(finalisers[2].callsToNonConstFinalise().getCallSequences())
			};
			expect(callsToFinalisers[0], all(less(callsToFinalisers[1])));
			expect(callsToFinalisers[1], all(less(callsToFinalisers[2])));
		});
	});
}
