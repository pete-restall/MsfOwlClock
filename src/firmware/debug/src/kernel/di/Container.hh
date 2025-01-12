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

			template <typename TTo>
			static constexpr bool matchesParameterType = std::is_same_v<std::remove_cvref_t<TFrom>, std::remove_cvref_t<TTo>>;

			template <typename TTo, typename = std::enable_if_t<matchesParameterType<TTo> && containerHasRegistrationFor<TTo &>>>
			constexpr operator TTo&(void) const
			{
				return this->container.resolve<TTo &>();
			}

			template <typename TTo, typename = std::enable_if_t<
				matchesParameterType<TTo> && (
					containerHasRegistrationFor<TTo &> ||
					containerHasRegistrationFor<const TTo &>)>>
			constexpr operator const TTo&(void) const
			{
				if constexpr (containerHasRegistrationFor<const TTo &>)
					return this->container.resolve<const TTo &>();
				else
					return this->container.resolve<TTo &>();
			}

			template <typename TTo, typename = std::enable_if_t<
				matchesParameterType<TTo> && (
					containerHasRegistrationFor<TTo &> ||
					containerHasRegistrationFor<volatile TTo &>)>>
			constexpr operator volatile TTo&(void) const
			{
				if constexpr (containerHasRegistrationFor<volatile TTo &>)
					return this->container.resolve<volatile TTo &>();
				else
					return this->container.resolve<TTo &>();
			}

			template <typename TTo, typename = std::enable_if_t<
				matchesParameterType<TTo> && (
					containerHasRegistrationFor<TTo &> ||
					containerHasRegistrationFor<const volatile TTo &> ||
					containerHasRegistrationFor<const TTo &> ||
					containerHasRegistrationFor<volatile TTo &>)>>
			constexpr operator const volatile TTo&(void) const
			{
				if constexpr (containerHasRegistrationFor<const volatile TTo &>)
					return this->container.resolve<const volatile TTo &>();
				else if constexpr (containerHasRegistrationFor<const TTo &>)
					return this->container.resolve<const TTo &>();
				else if constexpr (containerHasRegistrationFor<volatile TTo &>)
					return this->container.resolve<volatile TTo &>();
				else
					return this->container.resolve<TTo &>();
			}

// TODO: Add an operator TTo&& for when there is a registration...

			template <typename TTo>
			constexpr operator TTo*(void) const
			{
				return this->container.resolve<TTo *>();
			}

			template <typename TTo>
			constexpr operator const TTo*(void) const
			{
				if constexpr (containerHasRegistrationFor<const TTo *>)
					return this->container.resolve<const TTo *>();
				else
					return this->container.resolve<TTo *>();
			}

			template <typename TTo>
			constexpr operator volatile TTo*(void) const
			{
				if constexpr (containerHasRegistrationFor<volatile TTo *>)
					return this->container.resolve<volatile TTo *>();
				else
					return this->container.resolve<TTo *>();
			}

			template <typename TTo>
			constexpr operator const volatile TTo*(void) const
			{
				if constexpr (containerHasRegistrationFor<const volatile TTo *>)
					return this->container.resolve<const volatile TTo *>();
				else if constexpr (containerHasRegistrationFor<volatile TTo *>)
					return this->container.resolve<volatile TTo *>();
				else if constexpr (containerHasRegistrationFor<const TTo *>)
					return this->container.resolve<const TTo *>();
				else
					return this->container.resolve<TTo *>();
			}

			template <typename TTo, typename = std::enable_if_t<matchesParameterType<TTo> && !std::is_pointer_v<TTo> && !containerHasRegistrationFor<TTo &>>> // TODO: && !containerHasRegistrationFor<const TTo &> as well ???
			constexpr operator TTo(void) const
			{
				return this->container.resolve<TTo>();
			}
		};

		struct NoneRegistered
		{
		};

		template <typename...>
		struct FirstContainerRegistrationFor
		{
			using Type = NoneRegistered;
		};

		template <typename TClass, typename... TClasses>
		struct FirstContainerRegistrationFor<TClass, TClasses...>
		{
			using Type = std::conditional_t<containerHasRegistrationFor<TClass>, TClass, typename FirstContainerRegistrationFor<TClasses...>::Type>;
		};

		template <typename, typename...>
		struct DeducingFactoryFor;

		template <typename TClass, typename... TParameters>
		struct DeducingFactoryFor<TClass, std::tuple<TParameters...>>
		{
			static auto createUsing(const Container<TRegistrations...> &container)
			{
				return TClass(Deduce<TParameters>(container) ...);
			}
		};

		template <typename TClass>
		struct FactoryFor
		{
			static auto createUsing(const Container<TRegistrations...> &container)
			{
				if constexpr (containerHasRegistrationFor<TClass>)
					return std::get<ContainerRegistrationFor<TClass>>(container.registrations).create(); // TODO: then try const TClass and volatile TClass and const volatile TClass _iff_ there is a copy constructor...
				else
					return DeducingFactoryFor<TClass, ConstructorParameters::For<TClass>>::createUsing(container); // TODO: this ought to be a call to a default factory really, to allow the user to determine whether to implicitly create classes or not
			}
		};

		template <typename TClass> // TODO: repeat this for the other CV qualifications
		struct FactoryFor<TClass *>
		{
			static auto createUsing(const Container<TRegistrations...> &container)
			{
				using RegisteredType = FirstContainerRegistrationFor<TClass *, const TClass *>::Type;
				static_assert(
					!std::same_as<RegisteredType, NoneRegistered>,
					"TODO: rather than a static assertion, this really ought to be a call to a default factory to allow the user to specify whether to implicitly create classes or not");

				return std::get<ContainerRegistrationFor<RegisteredType>>(container.registrations).create();
			}
		};

		template <typename TClass> // TODO: repeat this for the other CV qualifications
		struct FactoryFor<TClass *const>
		{
			static auto createUsing(const Container<TRegistrations...> &container)
			{
				using RegisteredType = FirstContainerRegistrationFor<TClass *const, const TClass *const, TClass *, const TClass *>::Type;
				static_assert(
					!std::same_as<RegisteredType, NoneRegistered>,
					"TODO: rather than a static assertion, this really ought to be a call to a default factory to allow the user to specify whether to implicitly create classes or not");

				return std::get<ContainerRegistrationFor<RegisteredType>>(container.registrations).create();
			}
		};

		template <typename TClass>
		struct FactoryFor<TClass &> // TODO: we'll need more of these specialisations for CV-qualified refs that are passed directly to the public container.resolve<cv T &>(), rather than injected into a class (test this theory...)
		{
			static auto &createUsing(const Container<TRegistrations...> &container)
			{
				using RegisteredType = FirstContainerRegistrationFor<TClass &>::Type;
				static_assert(
					!std::same_as<RegisteredType, NoneRegistered>,
					"TODO: rather than a static assertion, this really ought to be a call to a default factory to allow the user to specify whether to implicitly create classes or not");

				return std::get<ContainerRegistrationFor<RegisteredType>>(container.registrations).create();
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
		// template <ILambdaFactory... TFactories>
		// auto registerFactories(TFactories... factories) const

		// can we resolve factories from the DI container ?

		template <typename T>
		T resolve(void) const
		{
			return FactoryFor<T>::createUsing(*this);
		}
	};
}

#endif
