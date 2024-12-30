#ifndef __SMEG_KERNEL_DI_CONSTRUCTORPARAMETERS_HH
#define __SMEG_KERNEL_DI_CONSTRUCTORPARAMETERS_HH
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

namespace smeg::kernel::di
{
	/*
		Uncle Bob says comments are an excuse for poor code.  This abomination certainly warrants explanation.

		Here we are leveraging stateful metaprogramming via the 'type loophole' technique documented by Alexandr Poltavsky
		<https://alexpolt.github.io/type-loophole.html>.  The starting point and inspiration was Deni's stackoverflow answer
		<https://stackoverflow.com/a/54493136> which forms the basis of constructor parameter type deduction and the reveals
		that multiple friend declarations can be belong to a template, with the template arguments captured and available to
		all friends once one has been instantiated.

		CWG2118 <https://www.open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#2118> has declared such trickery as ill-formed
		but since it is in relatively widespead use and accepted by GCC, we shall leverage it as a 'poor man's (desperate
		man's ?) reflection until reflexpr and the like are formalised and generally available in standard C++.

		The technique relies on the fact that friend member declarations and definitions move the function to the outer scope.
		If a class ('Tag' in our case) contains a friend declaration with an 'auto' return type, whilst another class
		('Loophole') contains the friend definitions, then instantiating 'Loophole' can capture a template argument to force
		the 'auto' return type.

		By using some template conversion operators and forcing instantiation of 'Loophole' via the 'captureParameterType(X)'
		friend, in turn based on the compiler's deduction of the constructor parameter type passed to the operator, we can
		later retrieve the compiler's deduced type by 'decltype(capturedParameterType(X))', where 'X' is some unique type
		over our context space; the class type and constructor's parameter index serve our purpose here.

		There are plenty of gotchas and indirection and hoops to jump through to satisfy (trick) the compiler, but the most
		notable limitations are:

			1. We can only really figure out the unqualified type of the parameter - we do not know whether it is an lvalue
			reference, an rvalue reference, etc.  Even though we can have multiple overloads of the conversion operators,
			because of the captured state, the last operator to be declared 'wins', ie. determines the perceived type.  I
			tried various ways to work around this, but I failed - instead we will deduce references in another stage during
			the instantiation and only return the unqualified parameter types.

			2. Ideally a dependency injection mechanism should be greedy and use the constructor with the most parameters,
			but in reality due to language complications such as varargs, it is simpler and more intuitive to go for the
			first unambiguous constructor with the least parameters.
	*/

	class ConstructorParameters
	{
	private:
		template <typename T>
		struct ConstructorParameter
		{
			using UnqualifiedType = T;
		};

		template <typename TClass, std::size_t ParameterIndex>
		struct Tag
		{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-template-friend"
			friend consteval int captureParameterType(Tag<TClass, ParameterIndex>);
			friend consteval auto capturedParameterType(Tag<TClass, ParameterIndex>);
#pragma GCC diagnostic pop
		};

		template <typename TClass, typename TParameter>
		static constexpr bool notCopyOrMoveConstructorOrRecursive = !std::is_same_v<
			std::remove_cv_t<std::remove_cvref_t<TClass>>,
			std::remove_cv_t<std::remove_cvref_t<TParameter>>>;

		template <
			typename TClass,
			typename TParameter,
			std::size_t ParameterIndex,
			bool,
			typename = typename std::enable_if_t<notCopyOrMoveConstructorOrRecursive<TClass, TParameter>>>
		struct Loophole
		{
			friend consteval int captureParameterType(Tag<TClass, ParameterIndex>) { return 0; }
			friend consteval auto capturedParameterType(Tag<TClass, ParameterIndex>) { return ConstructorParameter<TParameter>(); }
		};

		template <typename TClass, typename TParameter, std::size_t ParameterIndex>
		struct Loophole<TClass, TParameter, ParameterIndex, true>
		{
		};

		template <typename TClass, std::size_t ParameterIndex>
		struct Deduce
		{
			template <typename, std::size_t>
			static auto instantiateLoophole(...) -> std::size_t;

			template <typename, std::size_t N, auto = captureParameterType(Tag<TClass, N>{})>
			static auto instantiateLoophole(int) -> char;

			template <
				typename TParameter,
				std::size_t = sizeof(Loophole<
					TClass,
					std::remove_cvref_t<TParameter>,
					ParameterIndex,
					sizeof(instantiateLoophole<std::remove_cvref_t<TParameter>, ParameterIndex>(0)) == sizeof(char)>)>
			operator TParameter&();

			template <
				typename TParameter,
				std::size_t = sizeof(Loophole<
					TClass,
					std::remove_cvref_t<TParameter>,
					ParameterIndex,
					sizeof(instantiateLoophole<std::remove_cvref_t<TParameter>, ParameterIndex>(0)) == sizeof(char)>)>
			operator TParameter&&();
		};

		template <typename TClass, std::size_t... ParameterIndices>
		static constexpr auto numberOfConstructorParametersFor(int) -> decltype(TClass(Deduce<TClass, ParameterIndices>() ...), 0)
		{
			return sizeof...(ParameterIndices);
		}

		template <typename TClass, std::size_t... ParameterIndices>
		static constexpr std::size_t numberOfConstructorParametersFor(...)
		{
			return numberOfConstructorParametersFor<TClass, ParameterIndices..., sizeof...(ParameterIndices)>(0);
		}

		template <typename, typename>
		struct DeduceParameters;

		template <typename T, std::size_t... ParameterIndices>
		struct DeduceParameters<T, std::integer_sequence<std::size_t, ParameterIndices...>>
		{
			using AsTuple = std::tuple<typename decltype(capturedParameterType(Tag<T, ParameterIndices>()))::UnqualifiedType ...>;
		};

		template <typename T>
		struct From
		{
			using AsTuple = DeduceParameters<T, std::make_index_sequence<numberOfConstructorParametersFor<T>(0)>>::AsTuple;
		};

	public:
		template <typename T>
		using For = From<T>::AsTuple;
	};
}

#endif
