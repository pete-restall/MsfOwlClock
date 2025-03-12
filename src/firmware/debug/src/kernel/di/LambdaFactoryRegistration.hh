#ifndef __SMEG_KERNEL_DI_LAMBDAFACTORYREGISTRATION_HH
#define __SMEG_KERNEL_DI_LAMBDAFACTORYREGISTRATION_HH
#include "ILambdaFactory.hh"
#include "LambdaFactoryTraits.hh"

namespace smeg::kernel::di
{
	template <typename...>
	class LambdaFactoryRegistration;

	template <typename TKey, IStaticLambdaFactory TFactory>
	class LambdaFactoryRegistration<TKey, TFactory>
	{
	public:
		using Type = LambdaFactoryTraits<TFactory>::Type;

		LambdaFactoryRegistration(TFactory)
		{
		}

		constexpr Type create(void) const
		{
			return TFactory::operator()();
		}
	};

	template <typename TKey, IInstanceLambdaFactory TFactory>
	class LambdaFactoryRegistration<TKey, TFactory>
	{
	private:
		TFactory factory;

	public:
		LambdaFactoryRegistration(TFactory factory) :
			factory(factory)
		{
		}

		using Type = LambdaFactoryTraits<TFactory>::Type;

		constexpr Type create(void) const
		{
			return this->factory();
		}
	};
}

#endif
