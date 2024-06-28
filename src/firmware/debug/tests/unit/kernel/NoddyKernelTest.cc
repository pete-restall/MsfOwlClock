#include <mettle.hpp>

using namespace mettle;

namespace smeg::tests::unit::app
{
	suite<> helloTest("Hello World Kernel Tests", [](auto &unit)
	{
		unit.test("subject_action_expectation", []()
		{
			expect(true, equal_to(true));
		});
	});
}
