#ifndef __SMEG_TESTS_UNIT_KERNEL_DRIVERS_DUMMYTASKCONFIG_HH
#define __SMEG_TESTS_UNIT_KERNEL_DRIVERS_DUMMYTASKCONFIG_HH
#include <tuple>

namespace smeg::tests::unit::kernel::drivers::config
{
	template <auto X>
	struct StubDriverConfig
	{
		struct DummyApi
		{
			template <typename TApi>
			struct Interface
			{
			};

			struct Type
			{
			};
		};

		using ProvidedApis = std::tuple<DummyApi>;
	};
}

#endif
