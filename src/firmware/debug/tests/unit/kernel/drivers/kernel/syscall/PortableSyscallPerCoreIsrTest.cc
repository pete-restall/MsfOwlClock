#include <tuple>
#include <type_traits>

#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

#include "kernel/CurrentTaskSyscallApi.hh"
#include "kernel/drivers/SyscallApis.hh"
#include "kernel/drivers/kernel/syscall/PortableSyscallPerCoreIsr.hh"

using namespace mettle;

using namespace smeg::kernel;
using namespace smeg::kernel::drivers;
using namespace smeg::kernel::drivers::kernel::syscall;

namespace smeg::tests::unit::kernel::drivers::kernel::syscall
{
	suite<> portableSyscallPerCoreIsrTest("PortableSyscallPerCoreIsr Test Suite", [](auto &unit)
	{
		unit.test("constructor_testedForExceptions_expectQualifiedWithNoexcept", []()
		{
			using AnyHandlers = std::tuple<>;
			using RequiredApis = SyscallApis<CurrentTaskSyscallApi>;
			expect(std::is_nothrow_constructible_v<PortableSyscallPerCoreIsr<AnyHandlers>, RequiredApis, AnyHandlers>, equal_to(true));
		});

		// TODO: clearly more tests to build out the ISR functionality...
	});
}
