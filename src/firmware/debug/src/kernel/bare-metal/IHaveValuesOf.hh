#ifndef __SMEG_KERNEL_BAREMETAL_IHAVEVALUESOF_HH
#define __SMEG_KERNEL_BAREMETAL_IHAVEVALUESOF_HH
#include <concepts>
#include <utility>

namespace smeg::kernel::bare_metal
{
	namespace
	{
		template <std::integral TValue, std::integral auto... Values>
		consteval auto isIntegerSequence(std::integer_sequence<TValue, Values...>)
		{
			return true;
		}
	}

	template <typename TValue, typename T>
	concept IHaveValuesOf = requires
	{
		isIntegerSequence(typename T::Values{});
	};
}

#endif
