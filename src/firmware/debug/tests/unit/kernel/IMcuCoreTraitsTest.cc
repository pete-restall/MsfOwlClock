#include <cstddef>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/IMcuCoreTraits.hh"

using namespace mettle;

using namespace smeg::kernel;

namespace smeg::tests::unit::kernel
{
	template <auto NumberOfMcuCores, auto CoreId>
	struct StubMcuCoreTraits
	{
		static constexpr auto numberOfMcuCores = NumberOfMcuCores;

		static auto getMcuCoreId(void) noexcept
		{
			return CoreId;
		}
	};

	struct McuCoreTraitsWithNonConstexprNumberOfMcuCores
	{
		static std::size_t numberOfMcuCores;

		static auto getMcuCoreId(void) noexcept
		{
			return 0;
		}
	};

	std::size_t McuCoreTraitsWithNonConstexprNumberOfMcuCores::numberOfMcuCores = 1;

	struct McuCoreTraitsWithMissingNumberOfMcuCores
	{
		static std::size_t getMcuCoreId(void) noexcept
		{
			return 0;
		}
	};

	struct McuCoreTraitsWithMissingGetMcuCoreId
	{
		static constexpr std::size_t numberOfMcuCores = 1;
	};

	struct McuCoreTraitsWithGetMcuCoreIdMissingNoexcept
	{
		static constexpr auto numberOfMcuCores = 1;

		static auto getMcuCoreId(void)
		{
			return 0;
		}
	};

	struct McuCoreTraitsWithNonStaticGetMcuCoreId
	{
		static constexpr auto numberOfMcuCores = 1;

		auto getMcuCoreId(void) noexcept
		{
			return 0;
		}
	};

	suite<> iMcuCoreTraitsTest("IMcuCoreTraits Test Suite", [](auto &unit)
	{
		unit.test("IMcuCoreTraits_conceptPassedValidTraits_expectTrueIsReturned", []()
		{
			expect(IMcuCoreTraits<StubMcuCoreTraits<83, 79>>, equal_to(true));
		});

		unit.test("IMcuCoreTraits_conceptPassedTypeWithMissingNumberOfMcuCores_expectFalseIsReturned", []()
		{
			expect(IMcuCoreTraits<McuCoreTraitsWithMissingNumberOfMcuCores>, equal_to(false));
		});

		unit.test("IMcuCoreTraits_conceptPassedNonConstexprNumberOfMcuCores_expectFalseIsReturned", []()
		{
			expect(IMcuCoreTraits<McuCoreTraitsWithNonConstexprNumberOfMcuCores>, equal_to(false));
		});

		unit.test("IMcuCoreTraits_conceptPassedNumberOfMcuCoresLessThanOne_expectFalseIsReturned", []()
		{
			expect(IMcuCoreTraits<StubMcuCoreTraits<0, 0>>, equal_to(false));
			expect(IMcuCoreTraits<StubMcuCoreTraits<-1, 0>>, equal_to(false));
			expect(IMcuCoreTraits<StubMcuCoreTraits<-2, 0>>, equal_to(false));
		});

		unit.test("IMcuCoreTraits_conceptPassedInvalidTypeForNumberOfMcuCores_expectFalseIsReturned", []()
		{
			expect(IMcuCoreTraits<StubMcuCoreTraits<5.1, 0>>, equal_to(false));
			expect(IMcuCoreTraits<StubMcuCoreTraits<true, 0>>, equal_to(false));
		});

		unit.test("IMcuCoreTraits_conceptPassedTypeWithMissingGetMcuCoreId_expectFalseIsReturned", []()
		{
			expect(IMcuCoreTraits<McuCoreTraitsWithMissingGetMcuCoreId>, equal_to(false));
		});

		unit.test("IMcuCoreTraits_conceptPassedTypeWithGetMcuCoreIdMissingNoexcept_expectFalseIsReturned", []()
		{
			expect(IMcuCoreTraits<McuCoreTraitsWithGetMcuCoreIdMissingNoexcept>, equal_to(false));
		});

		unit.test("IMcuCoreTraits_conceptPassedTypeWithNonStaticGetMcuCoreId_expectFalseIsReturned", []()
		{
			expect(IMcuCoreTraits<McuCoreTraitsWithNonStaticGetMcuCoreId>, equal_to(false));
		});

		unit.test("IMcuCoreTraits_conceptPassedTypeWithGetMcuCoreIdReturningInvalidType_expectFalseIsReturned", []()
		{
			expect(IMcuCoreTraits<StubMcuCoreTraits<10, 5.1>>, equal_to(false));
			expect(IMcuCoreTraits<StubMcuCoreTraits<3, true>>, equal_to(false));
		});
	});
}
