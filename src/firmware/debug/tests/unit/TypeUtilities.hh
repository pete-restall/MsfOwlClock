#ifndef __SMEG_TESTS_UNIT_TYPEUTILITIES_HH
#define __SMEG_TESTS_UNIT_TYPEUTILITIES_HH
#include <string>
#include <typeinfo>

namespace smeg::tests::unit
{
	template <typename T>
	static std::string nameof(void)
	{
		return std::string(typeid(T).name());
	}
}

#endif
