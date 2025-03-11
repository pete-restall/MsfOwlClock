#ifndef __SMEG_KERNEL_DI_ILAMBDAFACTORY_HH
#define __SMEG_KERNEL_DI_ILAMBDAFACTORY_HH
#include <concepts>
#include <type_traits>

#include "_IsNotSameAs.hh"

namespace smeg::kernel::di
{
	template <typename T>
	concept IStaticLambdaFactory = !std::is_member_function_pointer_v<decltype(&T::operator())> && requires
	{
		{ T::operator()() } -> _$IsNotSameAs<void>;
	};

	template <typename T>
	concept IInstanceLambdaFactory = std::is_member_function_pointer_v<decltype(&T::operator())> && requires(T &lambda)
	{
		{ lambda() } -> _$IsNotSameAs<void>;
	};

	template <typename T>
	concept ILambdaFactory = IStaticLambdaFactory<T> || IInstanceLambdaFactory<T>;
}

#endif
