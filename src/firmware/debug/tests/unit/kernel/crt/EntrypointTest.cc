#include <atomic>
#include <memory>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/crt/Entrypoint.hh"

#include "../../CallRecorder.hh"
#include "../FinalisableTestDoubles.hh"
#include "../InitialisableTestDoubles.hh"
#include "BootloaderTestDoubles.hh"
#include "Crt0EnvironmentTestDoubles.hh"
#include "LinkerMemoryMapTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel::crt;

namespace smeg::kernel::crt
{
	struct DummyInitialisationTaskRunner
	{
		static void run(void) noexcept
		{
		}
	};

	struct MockInitialisationTaskRunner
	{
		static thread_local std::unique_ptr<smeg::tests::unit::CallRecorder<>> runCalls;

		static void run(void) noexcept
		{
			if (runCalls.get())
				runCalls->calledWith();
		}
	};

	thread_local std::unique_ptr<smeg::tests::unit::CallRecorder<>> MockInitialisationTaskRunner::runCalls;

	template <typename TCrt0Config>
	Entrypoint(TCrt0Config) -> Entrypoint<TCrt0Config, DummyInitialisationTaskRunner>;
}

namespace smeg::tests::unit::kernel::crt
{
	template <typename T>
	auto first(const T &&elements)
	{
		auto firstElement(elements.cbegin());
		expect("Tried to get the first element of an empty iterator", firstElement, not_equal_to(elements.cend()));
		return *firstElement;
	}

	class Fixture
	{
	private:
		using CallCountInt = CallRecorder<>::CallCountInt;
		std::atomic<CallCountInt> callSequence;
		InitialisableTestDoubles initialisableTestDoubles;
		FinalisableTestDoubles finalisableTestDoubles;
		LinkerKernelMemoryMapTestDoubles linkerKernelMemoryMapTestDoubles;
		LinkerAppMemoryMapTestDoubles linkerAppMemoryMapTestDoubles;
		LinkerMemoryMapTestDoubles linkerMemoryMapTestDoubles;
		BootloaderTestDoubles bootloaderTestDoubles;
		Crt0EnvironmentTestDoubles crt0EnvironmentTestDoubles;

	public:
		Fixture() :
			callSequence(0),
			initialisableTestDoubles(this->callSequence),
			finalisableTestDoubles(this->callSequence),
			linkerKernelMemoryMapTestDoubles(this->initialisableTestDoubles, this->finalisableTestDoubles),
			linkerAppMemoryMapTestDoubles(this->initialisableTestDoubles, this->finalisableTestDoubles),
			linkerMemoryMapTestDoubles(this->linkerKernelMemoryMapTestDoubles, this->linkerAppMemoryMapTestDoubles),
			bootloaderTestDoubles(this->callSequence),
			crt0EnvironmentTestDoubles(this->linkerMemoryMapTestDoubles, this->bootloaderTestDoubles)
		{
			MockInitialisationTaskRunner::runCalls = std::make_unique<CallRecorder<>>(this->callSequence);
		}

		auto dummyCrt0Environment(void)
		{
			return this->crt0EnvironmentTestDoubles.dummy();
		}

		auto stubCrt0Environment(void)
		{
			return this->crt0EnvironmentTestDoubles.stub();
		}

		auto stubLinkerMemoryMap(void)
		{
			return this->linkerMemoryMapTestDoubles.stub();
		}

		auto stubLinkerMemoryMapForKernel(void)
		{
			return this->linkerKernelMemoryMapTestDoubles.stub();
		}

		auto stubLinkerMemoryMapForApp(void)
		{
			return this->linkerAppMemoryMapTestDoubles.stub();
		}

		auto mockInitialisable(void)
		{
			return this->initialisableTestDoubles.mockNonConst();
		}

		auto mockBootloader(void)
		{
			return this->bootloaderTestDoubles.mock();
		}
	};

	suite<Fixture> entrypointTest("Entrypoint Test Suite", [](auto &unit)
	{
		unit.test("constructor_testedForExceptions_expectQualifiedWithNoExcept", [](auto &fixture)
		{
			const auto crt0Environment(fixture.dummyCrt0Environment());
			expect(noexcept(Entrypoint(crt0Environment)), equal_to(true));
		});

		unit.test("run_testedForExceptions_expectQualifiedWithNoExcept", [](auto &fixture)
		{
			const Entrypoint entrypoint(fixture.dummyCrt0Environment());
			expect(noexcept(entrypoint.run()), equal_to(true));
		});

		unit.test("run_called_expectKernelRamSectionsAreInitialisedExactlyOnce", [](auto &fixture)
		{
			auto kernelRamSectionsInitialiser(fixture.mockInitialisable());
			const Entrypoint entrypoint(fixture
				.stubCrt0Environment()
				.withLinkerMemoryMap(fixture
					.stubLinkerMemoryMap()
					.withLinkerMemoryMapForKernel(fixture
						.stubLinkerMemoryMapForKernel()
						.withInitialiserForRamSections(kernelRamSectionsInitialiser))));

			entrypoint.run();

			auto kernelRamSectionsInitialisationCalls(kernelRamSectionsInitialiser.callsToNonConstInitialise());
			expect(kernelRamSectionsInitialisationCalls.count(), equal_to(1));
		});

		unit.test("run_called_expectKernelCodeSectionsAreInitialisedExactlyOnce", [](auto &fixture)
		{
			auto kernelCodeSectionsInitialiser(fixture.mockInitialisable());
			const Entrypoint entrypoint(fixture
				.stubCrt0Environment()
				.withLinkerMemoryMap(fixture
					.stubLinkerMemoryMap()
					.withLinkerMemoryMapForKernel(fixture
						.stubLinkerMemoryMapForKernel()
						.withInitialiserForCodeSections(kernelCodeSectionsInitialiser))));

			entrypoint.run();

			auto kernelCodeSectionsInitialisationCalls(kernelCodeSectionsInitialiser.callsToNonConstInitialise());
			expect(kernelCodeSectionsInitialisationCalls.count(), equal_to(1));
		});

		unit.test("run_called_expectKernelRamSectionsAreInitialisedBeforeKernelCodeSections", [](auto &fixture)
		{
			auto kernelRamSectionsInitialiser(fixture.mockInitialisable());
			auto kernelCodeSectionsInitialiser(fixture.mockInitialisable());
			const Entrypoint entrypoint(fixture
				.stubCrt0Environment()
				.withLinkerMemoryMap(fixture
					.stubLinkerMemoryMap()
					.withLinkerMemoryMapForKernel(fixture
						.stubLinkerMemoryMapForKernel()
						.withInitialiserForRamSections(kernelRamSectionsInitialiser)
						.withInitialiserForCodeSections(kernelCodeSectionsInitialiser))));

			entrypoint.run();

			auto kernelRamSectionsInitialisationCall(first(kernelRamSectionsInitialiser.callsToNonConstInitialise().getCallSequences()));
			auto kernelCodeSectionsInitialisationCall(first(kernelCodeSectionsInitialiser.callsToNonConstInitialise().getCallSequences()));
			expect(kernelRamSectionsInitialisationCall, less(kernelCodeSectionsInitialisationCall));
		});

		unit.test("run_called_expectAppRamSectionsAreNotInitialised", [](auto &fixture)
		{
			auto appRamSectionsInitialiser(fixture.mockInitialisable());
			const Entrypoint entrypoint(fixture
				.stubCrt0Environment()
				.withLinkerMemoryMap(fixture
					.stubLinkerMemoryMap()
					.withLinkerMemoryMapForApp(fixture
						.stubLinkerMemoryMapForApp()
						.withInitialiserForRamSections(appRamSectionsInitialiser))));

			entrypoint.run();

			auto appRamSectionsInitialisationCalls(appRamSectionsInitialiser.callsToNonConstInitialise());
			expect(appRamSectionsInitialisationCalls.count(), equal_to(0));
		});

		unit.test("run_called_expectAppCodeSectionsAreNotInitialised", [](auto &fixture)
		{
			auto appCodeSectionsInitialiser(fixture.mockInitialisable());
			const Entrypoint entrypoint(fixture
				.stubCrt0Environment()
				.withLinkerMemoryMap(fixture
					.stubLinkerMemoryMap()
					.withLinkerMemoryMapForApp(fixture
						.stubLinkerMemoryMapForApp()
						.withInitialiserForCodeSections(appCodeSectionsInitialiser))));

			entrypoint.run();

			auto appCodeSectionsInitialisationCalls(appCodeSectionsInitialiser.callsToNonConstInitialise());
			expect(appCodeSectionsInitialisationCalls.count(), equal_to(0));
		});

		unit.test("run_called_expectBootloaderPreEntrypointHookIsCalledBeforeAnyRamSectionInitialisation", [](auto &fixture)
		{
			auto bootloader(fixture.mockBootloader());
			auto kernelRamSectionsInitialiser(fixture.mockInitialisable());
			const Entrypoint entrypoint(fixture
				.stubCrt0Environment()
				.withBootloader(bootloader)
				.withLinkerMemoryMap(fixture
					.stubLinkerMemoryMap()
					.withLinkerMemoryMapForKernel(fixture
						.stubLinkerMemoryMapForKernel()
						.withInitialiserForRamSections(kernelRamSectionsInitialiser))));

			entrypoint.run();

			auto bootloaderOnPreEntrypointCall(first(bootloader.callsToOnPreEntrypoint().getCallSequences()));
			auto kernelRamSectionsInitialisationCall(first(kernelRamSectionsInitialiser.callsToNonConstInitialise().getCallSequences()));
			expect(bootloaderOnPreEntrypointCall, less(kernelRamSectionsInitialisationCall));
		});

		unit.test("run_called_expectBootloaderPostEntrypointHookIsCalledAfterAnyCodeSectionInitialisation", [](auto &fixture)
		{
			auto bootloader(fixture.mockBootloader());
			auto kernelCodeSectionsInitialiser(fixture.mockInitialisable());
			const Entrypoint entrypoint(fixture
				.stubCrt0Environment()
				.withBootloader(bootloader)
				.withLinkerMemoryMap(fixture
					.stubLinkerMemoryMap()
					.withLinkerMemoryMapForKernel(fixture
						.stubLinkerMemoryMapForKernel()
						.withInitialiserForCodeSections(kernelCodeSectionsInitialiser))));

			entrypoint.run();

			auto kernelRamSectionsInitialisationCall(first(kernelCodeSectionsInitialiser.callsToNonConstInitialise().getCallSequences()));
			auto bootloaderOnPostEntrypointCall(first(bootloader.callsToOnPostEntrypoint().getCallSequences()));
			expect(bootloaderOnPostEntrypointCall, greater(kernelRamSectionsInitialisationCall));
		});

		unit.test("run_called_expectInitialisationTaskRunnerIsInvokedAfterTheBootloaderPostEntrypointHook", [](auto &fixture)
		{
			auto bootloader(fixture.mockBootloader());
			const auto crt0Environment(fixture.stubCrt0Environment().withBootloader(bootloader));
			const Entrypoint<decltype(crt0Environment), MockInitialisationTaskRunner> entrypoint(crt0Environment);

			entrypoint.run();

			auto bootloaderOnPostEntrypointCall(first(bootloader.callsToOnPostEntrypoint().getCallSequences()));
			auto taskRunnerCall(first(MockInitialisationTaskRunner::runCalls->getCallSequences()));
			expect(taskRunnerCall, greater(bootloaderOnPostEntrypointCall));
		});
	});
}
