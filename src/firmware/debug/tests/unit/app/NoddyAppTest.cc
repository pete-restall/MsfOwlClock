#include <mettle/suite.hpp>
#include <mettle/matchers.hpp>

using namespace mettle;

namespace smeg::tests::unit::app
{
	suite<> helloTest("Hello World App Tests", [](auto &unit)
	{
		unit.test("subject_action_expectation", []()
		{
			expect(true, equal_to(true));
		});
	});
}