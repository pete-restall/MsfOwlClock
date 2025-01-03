#ifndef __SMEG_KERNEL_DI_CONTAINER_HH
#define __SMEG_KERNEL_DI_CONTAINER_HH
#include <concepts>
#include <tuple>
#include <type_traits>

#include "../tuples/TupleProjection.hh"
#include "ConstructorParameters.hh"

namespace smeg::kernel::di
{
	using namespace smeg::kernel::tuples;

	struct NoKey
	{
	};

	template <typename T, typename TNot>
	concept _$IsNotSameAs = !std::is_same_v<T, TNot>;

	template <typename T>
	concept IStaticLambdaFactory = !std::is_member_function_pointer_v<decltype(&T::operator())> && requires // TODO: needs testing independently of the container
	{
		{ T::operator()() } -> _$IsNotSameAs<void>; // TODO: needs testing independently of the container
	};

	template <typename T>
	concept IInstanceLambdaFactory = std::is_member_function_pointer_v<decltype(&T::operator())> && requires(T &lambda) // TODO: needs testing independently of the container
	{
		{ lambda() } -> _$IsNotSameAs<void>; // TODO: needs testing independently of the container
	};

	template <typename T>
	concept ILambdaFactory = IStaticLambdaFactory<T> || IInstanceLambdaFactory<T>; // TODO: needs testing independently of the container

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
		TFactory factory; // TODO: need to devise a test to verify that we're using an instance member here rather than an auto

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

	template <typename T>
	concept IRegistration = true; // TODO: needs to be defined and tested

	template <IRegistration... TRegistrations>
	class Container
	{
	private:
		std::tuple<TRegistrations...> registrations;

		template <typename T>
		struct _$ContainerRegistrationsFor
		{
			template <IRegistration TRegistration>
			struct Filter
			{
				using AsTuple = std::conditional_t<std::same_as<typename TRegistration::Type, T>, std::tuple<TRegistration>, std::tuple<>>;
			};
		};

		template <typename T>
		using ContainerRegistrationsFor = TupleProjection<std::tuple<TRegistrations...>, _$ContainerRegistrationsFor<T>::template Filter>::Output;

		template <typename T>
		using ContainerRegistrationFor = std::tuple_element_t<0, ContainerRegistrationsFor<T>>;

		template <typename T>
		static constexpr bool containerHasRegistrationFor = std::tuple_size_v<ContainerRegistrationsFor<T>> == 1;

		template <typename TFrom>
		struct Deduce
		{
			const Container<TRegistrations...> &container;

			constexpr Deduce(const Container<TRegistrations...> &container) :
				container(container)
			{
			}

			template <typename T>
			static constexpr bool matchesParameterType = std::is_same_v<std::remove_cvref_t<TFrom>, std::remove_cvref_t<T>>;

			template <typename TTo, typename = std::enable_if_t<matchesParameterType<TTo> && containerHasRegistrationFor<TTo &>>> // TODO: plus the other stuff like if TFrom has no copy constructor and a registration of TFrom & is present, then what happens for a parameter of type 'TTo' ?  In this case we should fall back to 'container.resolve<TTo>' instead of 'TTo &'...
			constexpr operator TTo&(void) const
			{
				return this->container.resolve<TTo &>();
			}

// TODO: Add an operator TTo&& for when there is a registration...

			template <typename TTo, typename = std::enable_if_t<matchesParameterType<TTo> && !containerHasRegistrationFor<TTo &>>>
			constexpr operator TTo(void) const
			{
				return this->container.resolve<TTo>();
			}
		};

		template <typename TClass, typename... TParameters>
		struct FactoryFor;

		template <typename TClass, typename... TParameters>
		struct FactoryFor<TClass, std::tuple<TParameters...>>
		{
			static auto createUsing(const Container<TRegistrations...> &container)
			{
				// TODO: resolving 'const T &' should look for a registration first, then _iff_ the T is copy- or move-constructible then just create a new instance of T

				if constexpr (containerHasRegistrationFor<TClass>)
					return std::get<ContainerRegistrationFor<TClass>>(container.registrations).create();
				else
					return TClass(Deduce<TParameters>(container) ...);
			}
		};

		template <typename TClass>
		struct FactoryFor<TClass &, std::tuple<>>
		{
			static auto &createUsing(const Container<TRegistrations...> &container)
			{
				if constexpr (containerHasRegistrationFor<TClass &>)
					return std::get<ContainerRegistrationFor<TClass &>>(container.registrations).create();

				//static_assert(false, "TODO: THIS NEEDS TO BE TESTED / CODED FOR...");
			}
		};

	public:
		Container(std::tuple<TRegistrations...> registrations) :
			registrations(registrations)
		{
		}

	public:
		Container(void) :
			registrations{}
		{
			static_assert(sizeof...(TRegistrations) == 0, "There must be no registrations for an initial DI container; remove the template arguments");
		}

		template <ILambdaFactory TFactory> requires (!containerHasRegistrationFor<typename LambdaFactoryTraits<TFactory>::Type>)
		auto registerFactory(TFactory factory) const
		{
			return Container<TRegistrations..., LambdaFactoryRegistration<NoKey, TFactory>>(std::tuple_cat(
				this->registrations,
				std::make_tuple(LambdaFactoryRegistration<NoKey, TFactory>(factory))));
		}

		// TODO: Add a convenience signature...
		// template <ILambdaFactory... TFactories
		// auto registerFactories(TFactories... factories) const

		// can we resolve factories from the DI container ?

		template <typename T> requires (std::is_class_v<T> || containerHasRegistrationFor<T>)
		T resolve(void) const
		{
			using ConstructorParameters = ConstructorParameters::For<T>;
			return FactoryFor<T, ConstructorParameters>::createUsing(*this);
		}
	};
}

#endif
