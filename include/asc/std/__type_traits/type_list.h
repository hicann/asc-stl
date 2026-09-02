/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_TYPE_LIST_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_TYPE_LIST_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__type_traits/type_set.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/undefined.h>

CANN_ASC_STL_BEGIN_NAMESPACE

//! \file type_list.h
//! This file defines a type-list type and some fundamental algorithms on type
//! lists.
//!
//! It also defines a "meta-callable" protocol for parameterizing the type list
//! algorithms, and some higher-order meta-callables. A meta-callable is a class
//! type with a nested \c __call template alias.
//!
//! For the purpose of this file, a "trait type" is a class type with a nested
//! type alias named \c type.

template <class... Ts>
struct __type_list;

template <class Ty>
using __type = typename Ty::type;

//! \brief Evaluate a meta-callable with the given arguments
template <class Fn, class... Ts>
using __type_call = typename Fn::template __call<Ts...>;

//! \brief Evaluate a unary meta-callable with the given argument
template <class Fn, class Ty>
using __type_call1 = typename Fn::template __call<Ty>;

//! \brief Evaluate a binary meta-callable with the given arguments
template <class Fn, class Ty, class Uy>
using __type_call2 = typename Fn::template __call<Ty, Uy>;

namespace __detail {
template <size_t DependentValue>
struct __type_call_indirect_fn {
    template <template <class...> class Fn, class... Ts>
    using __call = Fn<Ts...>;
};
}  // namespace __detail

//! \brief Evaluate a meta-callable with the given arguments, with an indirection
//! to avoid the dreaded "pack expansion argument for non-pack parameter" error.
template <class Fn, class... Ts>
using __type_call_indirect = typename __detail::__type_call_indirect_fn<sizeof(
    __type_list<Fn, Ts...>*)>::template __call<Fn::template __call, Ts...>;

//! \brief Turns a class or alias template into a meta-callable
template <template <class...> class Fn>
struct __type_quote {
    template <class... Ts>
    using __call = Fn<Ts...>;
};

//! \brief Turns a unary class or alias template into a meta-callable
template <template <class> class Fn>
struct __type_quote1 {
    template <class Ty>
    using __call = Fn<Ty>;
};

//! \brief Turns a binary class or alias template into a meta-callable
template <template <class, class> class Fn>
struct __type_quote2 {
    template <class Ty, class Uy>
    using __call = Fn<Ty, Uy>;
};

//! \brief Turns a trait class template \c Fn into a meta-callable \c
//! __type_quote_trait such that \c __type_quote_trait<Fn>::__call<Ts...> is
//! equivalent to \c Fn<Ts...>::type.
template <template <class...> class Fn>
struct __type_quote_trait {
    template <class... Ts>
    using __call = __type<Fn<Ts...>>;
};

//! \brief Turns a unary trait class template \c Fn into a meta-callable
//! \c __type_quote_trait1 such that \c __type_quote_trait1<Fn>::__call<Ty> is
//! equivalent to \c Fn<Ty>::type.
template <template <class> class Fn>
struct __type_quote_trait1 {
    template <class Ty>
    using __call = __type<Fn<Ty>>;
};

//! \brief Turns a binary trait class template \c Fn into a meta-callable
//! \c __type_quote_trait2 such that \c __type_quote_trait2<Fn>::__call<Ty,Uy>
//! is equivalent to \c Fn<Ty,Uy>::type.
template <template <class, class> class Fn>
struct __type_quote_trait2 {
    template <class Ty, class Uy>
    using __call = __type<Fn<Ty, Uy>>;
};

//! \brief Adds an indirection to a meta-callable to avoid the dreaded "pack
//! expansion argument for non-pack parameter" error.
template <class Fn>
struct __type_indirect {
    template <class... Ts>
    using __call = typename __detail::__type_call_indirect_fn<sizeof(
        __type_list<Ts...>*)>::template __call<Fn::template __call, Ts...>;
};

//! \brief Turns a class or alias template into a meta-callable with an
//! indirection to avoid the "pack expansion argument for non-pack parameter"
//! error.
template <template <class...> class Fn>
struct __type_indirect_quote {
    template <class... Ts>
    using __call = typename __detail::__type_call_indirect_fn<sizeof(__type_list<Ts...>*)>::template __call<Fn, Ts...>;
};

//! \brief A meta-callable that composes two meta-callables
template <class Fn1, class Fn2>
struct __type_compose {
    template <class... Ts>
    using __call = __type_call1<Fn1, __type_call<Fn2, Ts...>>;
};

template <template <class...> class Fn, class... Ts>
struct __type_bind_front_quote {
    template <class... Us>
    using __call = Fn<Ts..., Us...>;
};

//! \brief A meta-callable that binds the front arguments to a meta-callable
template <class Fn, class... Ts>
struct __type_bind_front : __type_bind_front_quote<Fn::template __call, Ts...> {};

template <template <class...> class Fn, class... Ts>
struct __type_bind_back_quote {
    template <class... Us>
    using __call = Fn<Us..., Ts...>;
};

//! \brief A meta-callable that binds the back arguments to a meta-callable
template <class Fn, class... Ts>
struct __type_bind_back : __type_bind_back_quote<Fn::template __call, Ts...> {};

//! \brief A meta-callable that always evaluates to \c Ty.
template <class Ty>
struct __type_always {
    template <class...>
    using __call = Ty;
};

//! \brief A unary meta-callable that returns its argument unmodified.
struct __type_self {
    template <class Ty>
    using __call = Ty;
};

template <class Ty>
using __type_self_t = Ty;

//! \brief Perform a logical AND operation on a list of Boolean types.
//!
//! \note The AND operation is not short-circuiting.
struct __type_strict_and {
    template <class... Ts>
    using __call = __fold_and<Ts::value...>;
};

//! \brief Perform a logical OR operation on a list of Boolean types.
//!
//! \note The OR operation is not short-circuiting.
struct __type_strict_or {
    template <class... Ts>
    using __call = __fold_or<Ts::value...>;
};

//! \brief Perform a logical NOT operation on a Boolean type.
struct __type_not {
    template <class Ty>
    using __call = bool_constant<(!Ty::value)>;
};

//! \brief Test whether two integral constants are equal.
struct __type_equal {
    template <class Ty, class Uy>
    using __call = bool_constant<(Ty::value == Uy::value)>;
};

//! \brief Test whether two integral constants are not equal.
struct __type_not_equal {
    template <class Ty, class Uy>
    using __call = bool_constant<(Ty::value != Uy::value)>;
};

//! \brief Test whether one integral constant is less than another.
struct __type_less {
    template <class Ty, class Uy>
    using __call = bool_constant<(Ty::value < Uy::value)>;
};

//! \brief Test whether one integral constant is less than or equal to another.
struct __type_less_equal {
    template <class Ty, class Uy>
    using __call = bool_constant<(Ty::value <= Uy::value)>;
};

//! \brief Test whether one integral constant is greater than another.
struct __type_greater {
    template <class Ty, class Uy>
    using __call = bool_constant<(Ty::value > Uy::value)>;
};

//! \brief Test whether one integral constant is greater than or equal to another.
struct __type_greater_equal {
    template <class Ty, class Uy>
    using __call = bool_constant<(Ty::value >= Uy::value)>;
};

//! \brief A functional adaptor that negates a unary predicate
template <class Fn>
struct __type_negate1 {
    template <class Ty>
    using __call = __type_call1<__type_not, __type_call1<Fn, Ty>>;
};

//! \brief A functional adaptor that negates a binary predicate
template <class Fn>
struct __type_negate2 {
    template <class Ty, class Uy>
    using __call = __type_call1<__type_not, __type_call2<Fn, Ty, Uy>>;
};

//! \brief A type list
template <class... Ts>
struct __type_list {
    static constexpr size_t const __size = sizeof...(Ts);

    // A type_list behaves like a meta-callable
    // that takes a meta-callable and applies the
    // elements of the list to it.
    template <class Fn, class... Us>
    using __call = __type_call<Fn, Ts..., Us...>;
};

//! \brief A pointer to a type list, often used as a function argument.
template <class... Ts>
using __type_list_ptr = __type_list<Ts...>*;

//! \brief Return the size of a type list.
template <class List>
using __type_list_size = integral_constant<size_t, List::__size>;

//! \brief Given a type list and a list of types, append the types to the list.
template <class List, class... Ts>
using __type_push_back = __type_call<List, __type_quote<__type_list>, Ts...>;

//! \brief Given a type list and a list of types, prepend the types to the list.
template <class List, class... Ts>
using __type_push_front = __type_call1<List, __type_bind_front_quote<__type_list, Ts...>>;

namespace __detail {
template <class Ret, class... Args>
using __fn_ptr_t = Ret (*)(Args...);

template <class List>
extern __undefined<List> __as_type_list_v;

template <template <class...> class Cy, class... Ts>
extern __fn_ptr_t<__type_list<Ts...>> __as_type_list_v<Cy<Ts...>>;

template <template <class Ty, Ty...> class Fn, class Ty, Ty... Us>
extern __fn_ptr_t<__type_list<integral_constant<Ty, Us>...>> __as_type_list_v<Fn<Ty, Us...>>;

template <class Ret, class... Args>
extern __fn_ptr_t<__type_list<Ret, Args...>> __as_type_list_v<Ret(Args...)>;
}  // namespace __detail

//! \brief Given a type that can be interpreted as a type list, return its
//! type list interpretation. Types that can be interpreted as a type
//! list are of the following forms:
//!
//! \li `C<Ts...>`, for any class template `C` and types `Ts...`.
//! \li `C<T, T... Vs>`, for any class template `C`, type `T` and values `Vs...`.
//!     The resulting type is `_Fn<integral_constant<T, Vs>...>`.
//! \li `R(As...)`, for any function type `R(As...)`. The resulting type is
//!     `_Fn<R, As...>`.
template <class List>
using __as_type_list = decltype(__detail::__as_type_list_v<List>());

//! \brief Given a type that can be interpreted as a type list and a
//! meta-callable, invoke the meta-callable with the types in the list.
//! \c __as_type_list is used to convert the \c List type to a specialization
//! of \c __type_list.
//!
//! \sa __as_type_list
template <class Fn, class List>
using __type_apply = __type_call<__as_type_list<List>, Fn>;

//! \brief Given a type that can be interpreted as a type list and a class or
//! alias template, instantiate the template with the types in the list.
//! \c __as_type_list is used to convert the \c List type to a specialization
//! of \c __type_list.
//!
//! \sa __as_type_list
template <template <class...> class Fn, class List>
using __type_apply_q = __type_call<__as_type_list<List>, __type_quote<Fn>>;

namespace __detail {
// Only the following precise formulation works with older compilers.
template <class Fn, class... Ts, template <class...> class Fn2 = Fn::template __call, class = Fn2<Ts...>>
CANN_ASC_STL_API auto __type_callable_fn(__type_list<Fn, Ts...>*) -> true_type;

CANN_ASC_STL_API auto __type_callable_fn(void*) -> false_type;
}  // namespace __detail

//! \brief Test whether a meta-callable is callable with a given set of
//! arguments.
//!
//! Given a meta-callable and a list of arguments, return \c true_type if
//! the meta-callable can be called with the arguments, and \c false_type
//! otherwise.
template <class Fn, class... Ts>
using __type_callable = decltype(__detail::__type_callable_fn(static_cast<__type_list<Fn, Ts...>*>(nullptr)));

namespace __detail {
template <bool IsCallable>
struct __type_defer_fn {
    template <class, class...>
    using __call = __type_defer_fn;
};

template <>
struct __type_defer_fn<true> {
    template <class Fn, class... Ts>
    using __call = type_identity<__type_call<Fn, Ts...>>;
};
}  // namespace __detail

//! \brief Defer the evaluation of a meta-callable with a list of arguments.
//!
//! Given a meta-callable and a list of arguments, return a trait type \c T
//! where \c T::type is the result of evaluating the meta-callable with the
//! arguments, or if the meta-callable is not callable with the arguments, a
//! class type without a nested \c ::type type alias.
template <class Fn, class... Ts>
struct __type_defer : __type_call<__detail::__type_defer_fn<__type_callable<Fn, Ts...>::value>, Fn, Ts...> {};

//! \brief Defer the instantiation of a template with a list of arguments.
//!
//! Given a variadic template and a list of arguments, return a trait type \c T
//! where \c T::type is the result of instantiating the template with the
//! arguments, or if the template cannot be instantiated with the arguments, a
//! class type without a nested \c ::type type alias.
template <template <class...> class Fn, class... Ts>
using __type_defer_quote = __type_defer<__type_quote<Fn>, Ts...>;

//! \brief A composition of two meta-callables that will attempt to call the
//! first, and if that fails, call the second.
//!
//! Compose two meta-callables, \c TryFn and \c CatchFn, into a new
//! meta-callable. Given arguments \c Ts... , \c __type_try_catch will try to
//! evaluate `__type_call<TryFn, Ts...>`. If this type is well-formed, it will
//! be the result of the composition. Otherwise, the result will be
//! `__type_call<CatchFn, Ts...>`.
template <class TryFn, class CatchFn>
struct __type_try_catch {
    template <class... Ts>
    using __call = __type_call<conditional_t<__type_callable<TryFn, Ts...>::value, TryFn, CatchFn>, Ts...>;
};

// Implementation for indexing into a list of types:
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__type_pack_element)

template <size_t Ip, class... Ts>
using __type_index_c = __type_pack_element<Ip, Ts...>;

template <class Ip, class... Ts>
using __type_index = __type_index_c<Ip::value, Ts...>;

#else

// Fallback implementation for __type_index uses multiple inheritance. See:
// https://ldionne.com/2015/11/29/efficient-parameter-pack-indexing/
namespace __detail {
template <size_t Ip, class Ty>
struct __type_tuple_elem {
    using type = Ty;
};

template <class Is, class... Ts>
struct __type_tupl;

template <size_t... Is, class... Ts>
struct __type_tupl<index_sequence<Is...>, Ts...> : __type_tuple_elem<Is, Ts>... {};

template <class... Ts>
using __type_tuple = __type_tupl<make_index_sequence<sizeof...(Ts)>, Ts...>;

template <size_t Ip, class Ty>
CANN_ASC_STL_API __type_tuple_elem<Ip, Ty> __type_tuple_get(__type_tuple_elem<Ip, Ty>);

template <size_t Ip, class... Ts>
using __type_tuple_element_t = __type<decltype(__detail::__type_tuple_get<Ip>(__type_tuple<Ts...>{}))>;

struct __type_index_fn {
    template <class Ip, class... Ts>
    using __call = __type_tuple_element_t<Ip::value, Ts...>;
};
}  // namespace __detail

template <class Ip, class... Ts>
using __type_index = __type_call<__detail::__type_index_fn, Ip, Ts...>;

template <size_t Ip, class... Ts>
using __type_index_c = __type_index<integral_constant<size_t, Ip>, Ts...>;

#endif

namespace __detail {
template <size_t Ip>
struct __type_at_fn {
    template <class... Ts>
    using __call = __type_index_c<Ip, Ts...>;
};
}  // namespace __detail

//! \brief Given a type list and an index, return the type at that index.
template <size_t Ip, class List>
using __type_at_c = __type_call1<List, __detail::__type_at_fn<Ip>>;

//! \brief Given a type list and an index, return the type at that index.
template <class Ip, class List>
using __type_at = __type_call1<List, __detail::__type_at_fn<Ip::value>>;

//! \brief Given a type list return the type at the front of the list.
template <class List>
using __type_front = __type_at_c<0, List>;

//! \brief Given a type list return the type at the back of the list.
template <class List>
using __type_back = __type_at_c<List::__size - 1, List>;

//! \brief A pair of types
template <class First, class Second>
struct __type_pair {
    using __first = First;
    using __second = Second;
};

//! \brief Retrieve the first of a pair of types
//! \pre \c Pair is a specialization of \c __type_pair
template <class Pair>
using __type_pair_first = typename Pair::__first;

//! \brief Retrieve the second of a pair of types
//! \pre \c Pair is a specialization of \c __type_pair
template <class Pair>
using __type_pair_second = typename Pair::__second;

//! \see __type_switch
template <class Value>
struct __type_default {
    template <class>
    using __rebind = __type_default;

    using type = Value;
};

template <class Label, class Value>
struct __type_case_ {
    template <class OtherInt>
    using __rebind = __type_case_<integral_constant<OtherInt, Label::value>, Value>;

    using type = Value;
};

template <auto Label, class Value>
using __type_case = __type_case_<integral_constant<decltype(Label), Label>, Value>;

namespace __detail {
template <auto Label, class Value>
CANN_ASC_STL_API auto __type_switch_fn(__type_case<Label, Value>*, int) -> __type_case<Label, Value>;

template <auto Label, class Value>
CANN_ASC_STL_API auto __type_switch_fn(__type_default<Value>*, long) -> __type_default<Value>;
}  // namespace __detail

//! \see __type_switch
template <class Type, class... Cases>
struct __type_switch_fn : Cases::template __rebind<Type>... {
    template <class Label>
    using __call =
        __type<decltype(__detail::__type_switch_fn<Label::value>(static_cast<__type_switch_fn*>(nullptr), 0))>;
};

//! \brief Given an integral constant \c Label and a pack of "cases"
//! consisting of one or more specializations of \c __type_case and zero or
//! one specializations of \c __type_default, `__type_switch<Label, Cases...>`
//! returns the value associated with the first case whose label matches the
//! given label. If no such case exists, the value associated with the default
//! case is returned. If no default case exists, the type is ill-formed.
//!
//! \p Example:
//! \code
//! using result = __type_switch<2,
//!                              __type_case<1, char>,
//!                              __type_case<2, double>,
//!                              __type_default<float>>;
//! static_assert(is_same_v<result, double>);
//! \endcode
template <auto Label, class... Cases>
using __type_switch =
    __type_call<__type_switch_fn<decltype(Label), Cases...>, integral_constant<decltype(Label), Label>>;

namespace __detail {
// The upstream pack-pointer formulation ends in a variadic parameter that CCE
// aicore rejects at parse time, so concatenation is a recursive trait.
template <class... Lists>
struct __type_concat_impl {};

template <>
struct __type_concat_impl<> {
    using type = __type_list<>;
};

template <class... Ts>
struct __type_concat_impl<__type_list<Ts...>> {
    using type = __type_list<Ts...>;
};

template <class... Ts, class... Us, class... Rest>
struct __type_concat_impl<__type_list<Ts...>, __type_list<Us...>, Rest...> {
    using type = typename __type_concat_impl<__type_list<Ts..., Us...>, Rest...>::type;
};
}  // namespace __detail

//! \brief Concatenate a list of type lists into a single type list.
//!
//! When passed no type lists, \c __type_concat returns an empty type list.
template <class... Lists>
using __type_concat = __type<__detail::__type_concat_impl<Lists...>>;

//! \brief Given a list of type lists, concatenate all the lists into one.
//!
//! When passed an empty type list, \c __type_flatten returns an empty type list.
template <class ListOfLists>
using __type_flatten = __type_call1<ListOfLists, __type_quote<__type_concat>>;

namespace __detail {
template <bool IsEmpty>
struct __type_maybe_find_if_fn;

template <bool Found>
struct __type_find_if_found {
    template <class Fn, class Head, class... Tail>
    using __call = __type_list<Head, Tail...>;
};

template <>
struct __type_find_if_found<false> {
    template <class Fn, class Head, class... Tail>
    using __call = __type_call<__type_maybe_find_if_fn<sizeof...(Tail) == 0>, Fn, Tail...>;
};

template <bool IsEmpty>
struct __type_maybe_find_if_fn  // Type list is not empty
{
    template <class Fn, class Head, class... Tail>
    using __call = __type_call<__type_find_if_found<__type_call1<Fn, Head>::value>, Fn, Head, Tail...>;
};

template <>
struct __type_maybe_find_if_fn<true>  // Type list is empty
{
    template <class, class... None>
    using __call = __type_list<>;
};

template <class Fn>
struct __type_find_if_fn {
    template <class... Ts>
    using __call = __type_call<__type_maybe_find_if_fn<sizeof...(Ts) == 0>, Fn, Ts...>;
};

template <class Ty>
struct __type_same_as {
    template <class Uy>
    using __call = bool_constant<is_same_v<Ty, Uy>>;
};
}  // namespace __detail

//! \brief Given a type list and a predicate, find the first type in the list
//! that satisfies the predicate. It returns a type list containing the first
//! type that satisfies the predicate and all the types after it.
//!
//! If no type in the list satisfies the predicate, \c __type_find_if returns an
//! empty type list.
template <class List, class Fn>
using __type_find_if = __type_call1<List, __detail::__type_find_if_fn<Fn>>;

//! \brief Given a type list and type, find the first occurrence of the type in
//! the list. It returns a type list containing the type and all the types after
//! it.
//!
//! If the type is not in the list, \c __type_find returns an empty type list.
template <class List, class Ty>
using __type_find = __type_find_if<List, __detail::__type_same_as<Ty>>;

namespace __detail {
template <class Fn>
struct __type_transform_fn {
    template <class... Ts>
    using __call = __type_list<__type_call1<Fn, Ts>...>;
};
}  // namespace __detail

//! \brief Given a type list and a unary meta-callable, apply the meta-callable
//! to each type in the list. It returns a new type list containing the results.
template <class List, class Fn>
using __type_transform = __type_call1<List, __detail::__type_transform_fn<Fn>>;

namespace __detail {
// The upstream preprocessor-generated specialization ladders are outside the
// planned dependency closure, so the folds are recursive traits.
template <class Fn, class State, class... Ts>
struct __type_fold_right_term {
    using type = State;
};

template <class Fn, class State, class Head, class... Tail>
struct __type_fold_right_term<Fn, State, Head, Tail...> {
    // The binary application goes through __type_call_indirect: an alias
    // chain expanded in a pack context hits the "pack expansion argument for
    // non-pack parameter" error on some frozen toolchains.
    using type = __type_call_indirect<Fn, Head, typename __type_fold_right_term<Fn, State, Tail...>::type>;
};

template <class Fn, class State, class... Ts>
struct __type_fold_left_term {
    using type = State;
};

template <class Fn, class State, class Head, class... Tail>
struct __type_fold_left_term<Fn, State, Head, Tail...> {
    // The binary application goes through __type_call_indirect for the same
    // reason as __type_fold_right_term.
    using type = typename __type_fold_left_term<Fn, __type_call_indirect<Fn, State, Head>, Tail...>::type;
};

template <class Init, class Fn>
struct __type_fold_right_select_fn {
    template <class... Ts>
    using __call = typename __type_fold_right_term<Fn, Init, Ts...>::type;
};

template <class Init, class Fn>
struct __type_fold_left_select_fn {
    template <class... Ts>
    using __call = typename __type_fold_left_term<Fn, Init, Ts...>::type;
};
}  // namespace __detail

//! \brief Fold a type list from the right with a binary meta-callable and an
//! initial state.
template <class List, class Init, class Fn>
using __type_fold_right = __type_call1<List, __detail::__type_fold_right_select_fn<Init, Fn>>;

//! \brief Fold a type list from the left with a binary meta-callable and an
//! initial state.
template <class List, class Init, class Fn>
using __type_fold_left = __type_call1<List, __detail::__type_fold_left_select_fn<Init, Fn>>;

namespace __detail {
template <class Ty>
struct __type_remove_fn {
    template <class Uy>
    using __call = conditional_t<is_same_v<Ty, Uy>, __type_list<>, __type_list<Uy>>;
};
}  // namespace __detail

//! \brief Remove all occurrences of a type from a type list
template <class List, class Ty>
using __type_remove = __type_flatten<__type_transform<List, __detail::__type_remove_fn<Ty>>>;

namespace __detail {
template <class Fn>
struct __type_remove_if_fn {
    template <class Uy>
    using __call = conditional_t<__type_call1<Fn, Uy>::value, __type_list<>, __type_list<Uy>>;
};
}  // namespace __detail

//! \brief Remove all types satisfying a unary predicate from a type list
template <class List, class Fn>
using __type_remove_if = __type_flatten<__type_transform<List, __detail::__type_remove_if_fn<Fn>>>;

//! \brief Remove all types not satisfying a unary predicate from a type list
template <class List, class Fn>
using __type_copy_if = __type_flatten<__type_transform<List, __detail::__type_remove_if_fn<__type_negate1<Fn>>>>;

//! \brief Remove all duplicate types from a type list
template <class List>
using __type_unique = __as_type_list<__type_call<List, __type_quote<__make_type_set>>>;

namespace __detail {
// State is the list of type lists being built by the __type_fold_left
template <class State, class List>
struct __type_cartesian_product_fn {
    template <class Ty>
    struct __lambda0 {
        template <class List2>
        using __lambda1 = __type_list<__type_push_front<List2, Ty>>;

        using type = __type_flatten<__type_transform<State, __type_quote1<__lambda1>>>;
    };

    using type = __type_flatten<__type_transform<List, __type_quote_trait1<__lambda0>>>;
};
}  // namespace __detail

//! \brief Given a list of lists \c Lists, return a new list of lists that is
//! the cartesian product.
//!
//! \par Complexity
//! `O(N * M)`, where `N` is the size of the outer list, and
//! `M` is the size of the inner lists.
template <class... Lists>
using __type_cartesian_product = __type_fold_left<__type_list<Lists...>, __type_list<__type_list<>>,
    __type_quote_trait2<__detail::__type_cartesian_product_fn>>;

// A unary meta-callable for converting a type to its size in bytes
struct __type_sizeof {
    template <class Ty>
    using __call = integral_constant<size_t, sizeof(Ty)>;
};

//! \brief A list of compile-time values, and a meta-callable that accepts a
//! meta-callable and evaluates it with the values, each value wrapped in an
//! integral constant wrapper.
template <class Ty, Ty... Values>
struct __type_value_list : __type_list<integral_constant<Ty, Values>...> {
    using __type = Ty;
};

namespace __detail {
template <class Ty, Ty Start, Ty Stride, Ty... Is>
CANN_ASC_STL_API auto __type_iota_fn(
    integer_sequence<Ty, Is...>*) -> __type_value_list<Ty, Ty(Start + (Is * Stride))...>;
}  // namespace __detail

//! \brief Return an \c __type_value_list of size \c Size starting at \c Start
//! and incrementing by \c Stride.
template <class Ty, Ty Start, Ty Size, Ty Stride = Ty(1)>
using __type_iota =
    decltype(__detail::__type_iota_fn<Ty, Start, Stride>(static_cast<make_integer_sequence<Ty, Size>*>(nullptr)));

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_TYPE_LIST_H
