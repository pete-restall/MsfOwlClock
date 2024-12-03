#include <algorithm>
#include <array>
#include <cstddef>
#include <mutex>
#include <type_traits>
#include <vector>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/drivers/IIsr.hh"
#include "kernel/drivers/config/NakedToPerCoreIsrAdapter.hh"

#include "../../../CallRecorder.hh"
#include "../../../NonDeterminism.hh"
#include "../PerCoreIsrTestDoubles.hh"

using namespace mettle;

using namespace smeg::kernel::drivers;
using namespace smeg::kernel::drivers::config;

namespace smeg::tests::unit::kernel::drivers::config
{
	struct DummyMcuCoreTraits
	{
		static constexpr auto numberOfMcuCores = 1;

		static auto getMcuCoreId(void) noexcept
		{
			return 0;
		}
	};

	struct DummyPerCoreIsrConfig
	{
		static constexpr auto irq = 0;

		struct Handler
		{
			void onInterrupt(void) noexcept
			{
			}
		};
	};

	template <IProvidedIsrConfig TIsrConfig, auto CoreId>
	struct DummyPerCoreIsrFactory
	{
		static auto createPerCoreIsr(void) noexcept
		{
			return typename TIsrConfig::Handler();
		}
	};

	template <auto NumberOfMcuCores>
	class Fixture
	{
	private:
		using CallCountInt = CallRecorder<>::CallCountInt;
		static std::atomic<CallCountInt> callSequence;
		static PerCoreIsrTestDoubles perCoreIsrTestDoubles;

		static std::size_t mcuCoreId;

		static std::vector<MockPerCoreIsr> mockIsrs;

		static std::mutex noConcurrentTestsMutex;

		const std::lock_guard<std::mutex> noConcurrentTestsGuard;

		static auto initialise(void)
		{
			std::vector<MockPerCoreIsr> initialisedMockIsrs;
			for (auto i = 0; i < NumberOfMcuCores; i++)
				initialisedMockIsrs.push_back(perCoreIsrTestDoubles.mockPerCoreIsr());

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

		void stubMcuCoreId(std::size_t id)
		{
			expect(id, less_equal(NumberOfMcuCores));
			mcuCoreId = id;
		}

		const auto getMockIsrs(void) const
		{
			std::vector<const MockPerCoreIsr *> isrs;
			std::transform(mockIsrs.begin(), mockIsrs.end(), std::back_inserter(isrs), [](auto &isr) { return &isr; });
			return isrs;
		}

		template <IProvidedIsrConfig TIsrConfig, std::size_t CoreId>
		struct StubPerCoreIsrFactoryForMockIsrs
		{
			static auto createPerCoreIsr(void) noexcept
			{
				return mockIsrs.at(CoreId);
			}
		};

		template <IProvidedIsrConfig TIsrConfig, std::size_t CoreId>
		struct StubPerCoreIsrFactoryForDummies
		{
			static auto createPerCoreIsr(void) noexcept
			{
				return MockPerCoreIsr();
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

		struct StubPerCoreIsrConfigForMockIsr
		{
			static constexpr auto irq = 1;
			using Handler = MockPerCoreIsr;
		};

		struct StubPerCoreIsrConfigForMockIsrWithFactory
		{
			static constexpr auto irq = 1;
			using Handler = MockPerCoreIsr;

			template <typename TIsrConfig, auto McuCoreId>
			using Factory = StubPerCoreIsrFactoryForMockIsrs<TIsrConfig, McuCoreId>;
		};
	};

	template <auto NumberOfMcuCores>
	std::atomic<typename Fixture<NumberOfMcuCores>::CallCountInt> Fixture<NumberOfMcuCores>::callSequence = 0;

	template <auto NumberOfMcuCores>
	PerCoreIsrTestDoubles Fixture<NumberOfMcuCores>::perCoreIsrTestDoubles(Fixture<NumberOfMcuCores>::callSequence);

	template <auto NumberOfMcuCores>
	std::size_t Fixture<NumberOfMcuCores>::mcuCoreId = 0;

	template <auto NumberOfMcuCores>
	std::vector<MockPerCoreIsr> Fixture<NumberOfMcuCores>::mockIsrs(Fixture<NumberOfMcuCores>::initialise());

	template <auto NumberOfMcuCores>
	std::mutex Fixture<NumberOfMcuCores>::noConcurrentTestsMutex;

	suite<Fixture<1>, Fixture<3>, Fixture<5>> nakedToPerCoreIsrAdapterTest("NakedToPerCoreIsrAdapter Test Suite", [](auto &unit)
	{
		unit.test("INakedIsr_conceptIsPassedAdapter_expectTrueIsReturned", [](auto &)
		{
			expect(INakedIsr<NakedToPerCoreIsrAdapter<DummyMcuCoreTraits, DummyPerCoreIsrConfig, DummyPerCoreIsrFactory>>, equal_to(true));
		});

		unit.test("onInterrupt_calledWhenConfigDoesNotHaveFactory_expectFactoryPassedAsTemplateArgumentIsUsedToCreateOneInstancePerCore", [](auto &fixture)
		{
			using Fixture = std::decay_t<decltype(fixture)>;
			using McuCoreTraits = Fixture::StubMcuCoreTraits;
			using Adapter = NakedToPerCoreIsrAdapter<
				McuCoreTraits,
				typename Fixture::StubPerCoreIsrConfigForMockIsr,
				Fixture::template StubPerCoreIsrFactoryForMockIsrs>;

			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
			{
				fixture.stubMcuCoreId(mcuCoreId);
				Adapter::onInterrupt();
			}

			auto isrs(fixture.getMockIsrs());
			expect(isrs, each(
				filter([](auto &&isr) { return isr->callsToOnInterrupt().count(); },
				equal_to(1))));
		});

		unit.test("onInterrupt_calledWhenConfigHasFactory_expectSpecifiedFactoryIsUsedToCreateOneInstancePerCore", [](auto &fixture)
		{
			using Fixture = std::decay_t<decltype(fixture)>;
			using McuCoreTraits = Fixture::StubMcuCoreTraits;
			using Adapter = NakedToPerCoreIsrAdapter<
				McuCoreTraits,
				typename Fixture::StubPerCoreIsrConfigForMockIsrWithFactory,
				Fixture::template StubPerCoreIsrFactoryForDummies>;

			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
			{
				fixture.stubMcuCoreId(mcuCoreId);
				Adapter::onInterrupt();
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
			using Adapter = NakedToPerCoreIsrAdapter<
				McuCoreTraits,
				typename Fixture::StubPerCoreIsrConfigForMockIsr,
				Fixture::template StubPerCoreIsrFactoryForMockIsrs>;

			std::vector<int> numberOfCalls;
			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
			{
				numberOfCalls.push_back(anyInClosedRange(0, 10));
				fixture.stubMcuCoreId(mcuCoreId);
				for (auto i = 0; i < numberOfCalls.back(); i++)
					Adapter::onInterrupt();
			}

			auto isrs(fixture.getMockIsrs());
			for (auto mcuCoreId = 0; mcuCoreId < McuCoreTraits::numberOfMcuCores; mcuCoreId++)
				expect(isrs.at(mcuCoreId)->callsToOnInterrupt().count(), equal_to(numberOfCalls.at(mcuCoreId)));
		});
	});
}
