#ifndef __SMEG_KERNEL_DI_LAMBDAFACTORYTRAITS_HH
#define __SMEG_KERNEL_DI_LAMBDAFACTORYTRAITS_HH
#include <type_traits>

#include "ILambdaFactory.hh"

namespace smeg::kernel::di
{
	template <typename TFactory>
	struct LambdaFactoryTraits;

	template <IStaticLambdaFactory TFactory>
	struct LambdaFactoryTraits<TFactory>
	{
		using Type = decltype(TFactory::operator()());
	};

	template <IInstanceLambdaFactory TFactory>
	struct LambdaFactoryTraits<TFactory>
	{
		using Type = decltype(std::declval<TFactory>()());
	};
}

#endif
