#include <cstdint>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/INonConstFinalisable.hh"
#include "kernel/crt/crt0/linker/LinkerFiniArraySection.hh"

#include "../../../../CallRecorder.hh"
#include "../../../../ViewUtilities.hh"

using namespace mettle;

using namespace smeg::kernel;
using namespace smeg::kernel::crt::crt0::linker;

namespace smeg::tests::unit::kernel::crt::crt0::linker
{
	static std::atomic<CallRecorder<>::CallCountInt> callSequenceCounter(0);

	static thread_local CallRecorder<> mockFini0Calls(callSequenceCounter);
	static void mockFini0(void) noexcept { mockFini0Calls.calledWith(); }

	static thread_local CallRecorder<> mockFini1Calls(callSequenceCounter);
	static void mockFini1(void) noexcept { mockFini1Calls.calledWith(); }

	static thread_local CallRecorder<> mockFini2Calls(callSequenceCounter);
	static void mockFini2(void) noexcept { mockFini2Calls.calledWith(); }

	static void dummyFini(void) noexcept { }

	suite<> linkerFiniArraySectionTest("LinkerFiniArraySection Test Suite", [](auto &unit)
	{
		unit.test("class_testedAgainstINonConstFinalisableConcept_expectTrue", []()
		{
			const std::vector finiArray{&dummyFini};
			LinkerFiniArraySection finiArraySection(finiArray.begin(), finiArray.end());
			expect(INonConstFinalisable<decltype(finiArraySection)>, equal_to(true));
		});

		unit.test("constructor_called_expectNoFunctionPointersAreCalled", []()
		{
			const std::vector finiArray{&mockFini0};
			LinkerFiniArraySection finiArraySection(finiArray.begin(), finiArray.end());
			expect(mockFini0Calls.count(), equal_to(0));
		});

		unit.test("finalise_testedAgainstNoExceptConcept_expectTrue", []()
		{
			const std::vector finiArray{&dummyFini};
			LinkerFiniArraySection finiArraySection(finiArray.begin(), finiArray.end());
			finiArraySection.finalise();
			expect(noexcept(finiArraySection.finalise()), equal_to(true));
		});

		unit.test("finalise_calledWithNoFunctionPointers_expectNoFunctionPointersAreCalled", []()
		{
			const std::vector finiArray{&mockFini0};
			LinkerFiniArraySection finiArraySection(finiArray.begin(), finiArray.begin());
			finiArraySection.finalise();
			expect(mockFini0Calls.count(), equal_to(0));
		});

		unit.test("finalise_calledWithSingleFunctionPointer_expectFunctionPointerIsCalledOnce", []()
		{
			const std::vector finiArray{&mockFini0};
			LinkerFiniArraySection finiArraySection(finiArray.begin(), finiArray.end());
			finiArraySection.finalise();
			expect(mockFini0Calls.count(), equal_to(1));
		});

		unit.test("finalise_calledWithMultipleFunctionPointers_expectAllFunctionPointersAreCalledOnce", []()
		{
			const std::vector finiArray{&mockFini0, &mockFini1, &mockFini2};
			LinkerFiniArraySection finiArraySection(finiArray.begin(), finiArray.end());
			finiArraySection.finalise();

			expect(mockFini0Calls.count(), equal_to(1));
			expect(mockFini1Calls.count(), equal_to(1));
			expect(mockFini2Calls.count(), equal_to(1));
		});

		unit.test("finalise_calledWithMultipleFunctionPointers_expectAllFunctionPointersAreCalledInReverseOrder", []()
		{
			const std::vector finiArray{&mockFini0, &mockFini1, &mockFini2};
			LinkerFiniArraySection finiArraySection(finiArray.begin(), finiArray.end());
			finiArraySection.finalise();

			const std::vector callsToFinis{
				asVector(mockFini0Calls.getCallSequences()),
				asVector(mockFini1Calls.getCallSequences()),
				asVector(mockFini2Calls.getCallSequences())
			};
			expect(callsToFinis[2], all(less(callsToFinis[1])));
			expect(callsToFinis[1], all(less(callsToFinis[0])));
		});

		unit.test("finalise_calledMoreThanOnce_expectFunctionPointersAreCalledEachTime", []()
		{
			const std::vector finiArray{&mockFini0};
			LinkerFiniArraySection finiArraySection(finiArray.begin(), finiArray.end());
			finiArraySection.finalise();
			finiArraySection.finalise();
			expect(mockFini0Calls.count(), equal_to(2));
		});
	});
}
