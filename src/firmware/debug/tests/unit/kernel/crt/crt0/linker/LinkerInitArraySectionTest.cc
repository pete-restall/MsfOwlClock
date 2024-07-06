#include <cstdint>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/INonConstInitialisable.hh"
#include "kernel/crt/crt0/linker/LinkerInitArraySection.hh"

#include "../../../../CallRecorder.hh"
#include "../../../../ViewUtilities.hh"

using namespace mettle;

using namespace smeg::kernel;
using namespace smeg::kernel::crt::crt0::linker;

namespace smeg::tests::unit::kernel::crt::crt0::linker
{
	static std::atomic<CallRecorder<>::CallCountInt> callSequenceCounter(0);

	static thread_local CallRecorder<> mockInit0Calls(callSequenceCounter);
	static void mockInit0(void) noexcept { mockInit0Calls.calledWith(); }

	static thread_local CallRecorder<> mockInit1Calls(callSequenceCounter);
	static void mockInit1(void) noexcept { mockInit1Calls.calledWith(); }

	static thread_local CallRecorder<> mockInit2Calls(callSequenceCounter);
	static void mockInit2(void) noexcept { mockInit2Calls.calledWith(); }

	static void dummyInit(void) noexcept { }

	suite<> linkerInitArraySectionTest("LinkerInitArraySection Test Suite", [](auto &unit)
	{
		unit.test("class_testedAgainstINonConstInitialisableConcept_expectTrue", []()
		{
			std::vector initArray{&dummyInit};
			LinkerInitArraySection initArraySection(initArray.begin(), initArray.end());
			expect(INonConstInitialisable<decltype(initArraySection)>, equal_to(true));
		});

		unit.test("constructor_called_expectNoFunctionPointersAreCalled", []()
		{
			std::vector initArray{&mockInit0};
			LinkerInitArraySection initArraySection(initArray.begin(), initArray.end());
			expect(mockInit0Calls.count(), equal_to(0));
		});

		unit.test("initialise_testedAgainstNoExceptConcept_expectTrue", []()
		{
			std::vector initArray{&dummyInit};
			LinkerInitArraySection initArraySection(initArray.begin(), initArray.end());
			initArraySection.initialise();
			expect(noexcept(initArraySection.initialise()), equal_to(true));
		});

		unit.test("initialise_calledWithNoFunctionPointers_expectNoFunctionPointersAreCalled", []()
		{
			std::vector initArray{&mockInit0};
			LinkerInitArraySection initArraySection(initArray.begin(), initArray.begin());
			initArraySection.initialise();
			expect(mockInit0Calls.count(), equal_to(0));
		});

		unit.test("initialise_calledWithSingleFunctionPointer_expectFunctionPointerIsCalledOnce", []()
		{
			std::vector initArray{&mockInit0};
			LinkerInitArraySection initArraySection(initArray.begin(), initArray.end());
			initArraySection.initialise();
			expect(mockInit0Calls.count(), equal_to(1));
		});

		unit.test("initialise_calledWithMultipleFunctionPointers_expectAllFunctionPointersAreCalledOnce", []()
		{
			std::vector initArray{&mockInit0, &mockInit1, &mockInit2};
			LinkerInitArraySection initArraySection(initArray.begin(), initArray.end());
			initArraySection.initialise();

			expect(mockInit0Calls.count(), equal_to(1));
			expect(mockInit1Calls.count(), equal_to(1));
			expect(mockInit2Calls.count(), equal_to(1));
		});

		unit.test("initialise_calledWithMultipleFunctionPointers_expectAllFunctionPointersAreCalledInOrder", []()
		{
			std::vector initArray{&mockInit0, &mockInit1, &mockInit2};
			LinkerInitArraySection initArraySection(initArray.begin(), initArray.end());
			initArraySection.initialise();

			const std::vector callsToInits{
				toVector(mockInit0Calls.getCallSequences()),
				toVector(mockInit1Calls.getCallSequences()),
				toVector(mockInit2Calls.getCallSequences())
			};
			expect(callsToInits[0], all(less(callsToInits[1])));
			expect(callsToInits[1], all(less(callsToInits[2])));
		});
	});
}
