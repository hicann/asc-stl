/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTRUCTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTRUCTIBLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/conjunction.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_destructible.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/negation.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __is_construct {
struct __nat {};
}  // namespace __is_construct

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_constructible)

template <class Tp, class... Args>
struct is_constructible : integral_constant<bool, __is_constructible(Tp, Args...)> {};

template <class Tp, class... Args>
inline constexpr bool is_constructible_v = __is_constructible(Tp, Args...);

#else

template <class Tp, class... Args>
struct __asc_is_constructible;

template <class To, class From>
struct __is_invalid_base_to_derived_cast {
    static_assert(is_reference_v<To>, "Wrong specialization");
    using RawFrom = remove_cvref_t<From>;
    using RawTo = remove_cvref_t<To>;
    static const bool value = _And<_IsNotSame<RawFrom, RawTo>, is_base_of<RawFrom, RawTo>,
        _Not<__asc_is_constructible<RawTo, From> > >::value;
};

template <class To, class From>
struct __is_invalid_lvalue_to_rvalue_cast : false_type {
    static_assert(is_reference_v<To>, "Wrong specialization");
};

template <class ToRef, class FromRef>
struct __is_invalid_lvalue_to_rvalue_cast<ToRef&&, FromRef&> {
    using RawFrom = remove_cvref_t<FromRef>;
    using RawTo = remove_cvref_t<ToRef>;
    static const bool value =
        _And<_Not<is_function<RawTo> >, _Or<_IsSame<RawFrom, RawTo>, is_base_of<RawTo, RawFrom> > >::value;
};

// The __eat probe works around compilers that disallow static_cast<T&&>(e)
// for non-reference-compatible types and keeps classes with explicit
// conversion operators detectable.
template <class To>
CANN_ASC_STL_API void __constructible_eat(To);

// The __test_nary/__test_unary catch-alls __test(...) are not
// portable to CCE aicore, so the negative overloads take long: the int
// overloads still win exactly when the construction expression is well-formed
// and the conversion fallback covers the rest.
template <class Tp, class... Args, class = decltype(Tp(asc::std::declval<Args>()...))>
CANN_ASC_STL_API true_type __constructible_test_nary(int);
template <class, class...>
CANN_ASC_STL_API false_type __constructible_test_nary(long);

template <class Tp, class A0, class = decltype(::new Tp(asc::std::declval<A0>()))>
CANN_ASC_STL_API is_destructible<Tp> __constructible_test_unary(int);
template <class, class>
CANN_ASC_STL_API false_type __constructible_test_unary(long);

// The usual three-rank __test_cast probe ends in a __test(...) catch-all.
// The cast detection is instead a two-stage partial-specialization probe over
// a local void alias (the __type_traits/promote.h detection pattern): the
// __eat copy-initialization wins when well-formed, otherwise the static_cast
// form applies the invalid-cast exclusions.
template <class...>
using __constructible_void_t = void;

template <class To, class From, class = void>
struct __cast_eat : false_type {};

template <class To, class From>
struct __cast_eat<To, From,
    __constructible_void_t<decltype(asc::std::__constructible_eat<To>(asc::std::declval<From>()))> > : true_type {};

template <class To, class From, class = void>
struct __cast_static : false_type {};

template <class To, class From>
struct __cast_static<To, From, __constructible_void_t<decltype(static_cast<To>(asc::std::declval<From>()))> >
    : integral_constant<bool,
          !__is_invalid_base_to_derived_cast<To, From>::value && !__is_invalid_lvalue_to_rvalue_cast<To, From>::value> {
};

template <class To, class From, bool = __cast_eat<To, From>::value>
struct __test_cast_result;

template <class To, class From>
struct __test_cast_result<To, From, true> : true_type {};

template <class To, class From>
struct __test_cast_result<To, From, false> : __cast_static<To, From> {};

template <class Tp, bool = is_void_v<Tp> >
struct __is_default_constructible : decltype(asc::std::__constructible_test_nary<Tp>(0)) {};

template <class Tp>
struct __is_default_constructible<Tp, true> : false_type {};

template <class Tp>
struct __is_default_constructible<Tp[], false> : false_type {};

template <class Tp, size_t Ns>
struct __is_default_constructible<Tp[Ns], false> : __is_default_constructible<remove_all_extents_t<Tp> > {};

template <class Tp, class... Args>
struct __asc_is_constructible {
    static_assert(sizeof...(Args) > 1, "Wrong specialization");
    using type = decltype(asc::std::__constructible_test_nary<Tp, Args...>(0));
};

template <class Tp>
struct __asc_is_constructible<Tp> : __is_default_constructible<Tp> {};

template <class Tp, class A0>
struct __asc_is_constructible<Tp, A0> : public decltype(asc::std::__constructible_test_unary<Tp, A0>(0)) {};

template <class Tp, class A0>
struct __asc_is_constructible<Tp&, A0> : public __test_cast_result<Tp&, A0> {};

template <class Tp, class A0>
struct __asc_is_constructible<Tp&&, A0> : public __test_cast_result<Tp&&, A0> {};

template <class Tp, class... Args>
struct is_constructible : __asc_is_constructible<Tp, Args...>::type {};

template <class Tp, class... Args>
inline constexpr bool is_constructible_v = is_constructible<Tp, Args...>::value;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTRUCTIBLE_H
