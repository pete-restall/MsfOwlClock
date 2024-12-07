#include <algorithm>
#include <cstddef>
#include <mutex>
#include <tuple>
#include <type_traits>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/kernel/syscall/PortableSyscallIsr.hh"

#include "../../../../CallRecorder.hh"
#include "../../../../NonDeterminism.hh"
#include "../../../../ViewUtilities.hh"
#include "PortableSyscallPerCoreIsrTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel::drivers;
using namespace smeg::kernel::drivers::kernel::syscall;

namespace smeg::tests::unit::kernel::drivers::kernel::syscall
{
	template <auto NumberOfMcuCores>
	class Fixture
	{
	private:
		using CallCountInt = CallRecorder<>::CallCountInt;
		static std::atomic<CallCountInt> callSequence;
		static PortableSyscallPerCoreIsrTestDoubles portableSyscallPerCoreIsrTestDoubles;

		static std::size_t mcuCoreId;

		static std::vector<MockPortableSyscallPerCoreIsr> mockIsrs;

		static std::mutex noConcurrentTestsMutex;

		const std::lock_guard<std::mutex> noConcurrentTestsGuard;

		static auto initialise(void)
		{
			std::vector<MockPortableSyscallPerCoreIsr> initialisedMockIsrs;
			for (auto i = 0; i < NumberOfMcuCores; i++)
				initialisedMockIsrs.push_back(portableSyscallPerCoreIsrTestDoubles.mock());

			return initialisedMockIsrs;
		}

	public:
		Fixture() :
			noConcurrentTestsGuard(noConcurrentTestsMutex)
		{
			callSequence = 0;
			mcuCoreId = 0;
			for (auto isr : mockIsrs)
				isr.resetMock();
		}

		void *dummyArgs(void) const
		{
			return nullptr;
		}

		void *stubArgs(void) const
		{
			return reinterpret_cast<void *>(this->stubId());
		}

		std::uint32_t stubId(void) const
		{
			return anyInClosedRange(std::uint32_t(0), std::uint32_t(~0));
		}

		std::uint32_t dummyId(void) const
		{
			return 0;
		}

		void stubMcuCoreId(std::size_t id)
		{
			expect(id, less_equal(NumberOfMcuCores));
			mcuCoreId = id;
		}

		const auto getMockIsrs(void) const
		{
			std::vector<const MockPortableSyscallPerCoreIsr *> isrs;
			std::transform(mockIsrs.begin(), mockIsrs.end(), std::back_inserter(isrs), [](auto &isr) { return &isr; });
			return isrs;
		}

		template <std::size_t McuCoreId>
		struct StubPortableSyscallPerCoreIsrFactoryForMockIsrs
		{
			static auto createPortableSyscallPerCoreIsr(void) noexcept
			{
				return mockIsrs.at(McuCoreId);
			}
		};

		struct StubMcuCoreTraits
		{
			static constexpr auto numberOfMcuCores = NumberOfMcuCores;

			static auto getMcuCoreId(void) noexcept
			{
				return mcuCoreId;
			}
		};
	};

	template <auto NumberOfMcuCores>
	std::atomic<typename Fixture<NumberOfMcuCores>::CallCountInt> Fixture<NumberOfMcuCores>::callSequence = 0;

	template <auto NumberOfMcuCores>
	PortableSyscallPerCoreIsrTestDoubles Fixture<NumberOfMcuCores>::portableSyscallPerCoreIsrTestDoubles(Fixture<NumberOfMcuCores>::callSequence);

	template <auto NumberOfMcuCores>
	std::size_t Fixture<NumberOfMcuCores>::mcuCoreId = 0;

	template <auto NumberOfMcuCores>
	std::vector<MockPortableSyscallPerCoreIsr> Fixture<NumberOfMcuCores>::mockIsrs(Fixture<NumberOfMcuCores>::initialise());

	template <auto NumberOfMcuCores>
	std::mutex Fixture<NumberOfMcuCores>::noConcurrentTestsMutex;

	suite<Fixture<1>, Fixture<3>, Fixture<5>> portableSyscallIsrTest("PortableSyscallIsr Test Suite", [](auto &unit)
	{
		unit.test("onInterrupt_called_expectFactoryPassedAsTemplateArgumentIsUsedToCreateOneInstancePerCore", [](auto &fixture)
		{
			using Fixture = std::decay_t<decltype(fixture)>;
			using McuCoreTraits = Fixture::StubMcuCoreTraits;
			using PortableSyscallIsr = PortableSyscallIsr<
				McuCoreTraits,
				Fixture::template StubPortableSyscallPerCoreIsrFactoryForMockIsrs>;

			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
			{
				fixture.stubMcuCoreId(mcuCoreId);
				PortableSyscallIsr::onInterrupt(fixture.dummyArgs(), fixture.dummyId());
			}

			auto isrs(fixture.getMockIsrs());
			expect(isrs, each(
				filter([](auto &&isr) { return isr->callsToOnInterrupt().count(); },
				equal_to(1))));
		});

		unit.test("onInterrupt_calledMultipleTimesForEachCore_expectCallsToGivenCoreSpecificHandlersTally", [](auto &fixture)
		{
			using Fixture = std::decay_t<decltype(fixture)>;
			using McuCoreTraits = Fixture::StubMcuCoreTraits;
			using PortableSyscallIsr = PortableSyscallIsr<
				McuCoreTraits,
				Fixture::template StubPortableSyscallPerCoreIsrFactoryForMockIsrs>;

			std::vector<int> numberOfCalls;
			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
			{
				numberOfCalls.push_back(anyInClosedRange(0, 10));
				fixture.stubMcuCoreId(mcuCoreId);
				for (auto i = 0; i < numberOfCalls.back(); i++)
					PortableSyscallIsr::onInterrupt(fixture.dummyArgs(), fixture.dummyId());
			}

			auto isrs(fixture.getMockIsrs());
			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
				expect(isrs.at(mcuCoreId)->callsToOnInterrupt().count(), equal_to(numberOfCalls.at(mcuCoreId)));
		});

		unit.test("onInterrupt_calledMultipleTimesForEachCore_expectEachCoreHandlerIsGivenSameArgs", [](auto &fixture)
		{
			using Fixture = std::decay_t<decltype(fixture)>;
			using McuCoreTraits = Fixture::StubMcuCoreTraits;
			using PortableSyscallIsr = PortableSyscallIsr<
				McuCoreTraits,
				Fixture::template StubPortableSyscallPerCoreIsrFactoryForMockIsrs>;

			std::vector<void *> args;
			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
			{
				args.push_back(fixture.stubArgs());
				fixture.stubMcuCoreId(mcuCoreId);
				PortableSyscallIsr::onInterrupt(args.back(), fixture.dummyId());
			}

			auto isrs(fixture.getMockIsrs());
			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
			{
				auto calls(asVector(isrs.at(mcuCoreId)->callsToOnInterrupt().getCallArguments()));
				expect(std::get<void *>(calls.at(0)), equal_to(args.at(mcuCoreId)));
			}
		});

		unit.test("onInterrupt_calledMultipleTimesForEachCore_expectEachCoreHandlerIsGivenSameSyscallId", [](auto &fixture)
		{
			using Fixture = std::decay_t<decltype(fixture)>;
			using McuCoreTraits = Fixture::StubMcuCoreTraits;
			using PortableSyscallIsr = PortableSyscallIsr<
				McuCoreTraits,
				Fixture::template StubPortableSyscallPerCoreIsrFactoryForMockIsrs>;

			std::vector<std::uint32_t> ids;
			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
			{
				ids.push_back(fixture.stubId());
				fixture.stubMcuCoreId(mcuCoreId);
				PortableSyscallIsr::onInterrupt(fixture.dummyArgs(), ids.back());
			}

			auto isrs(fixture.getMockIsrs());
			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
			{
				auto calls(asVector(isrs.at(mcuCoreId)->callsToOnInterrupt().getCallArguments()));
				expect(std::get<std::uint32_t>(calls.at(0)), equal_to(ids.at(mcuCoreId)));
			}
		});
	});
}
