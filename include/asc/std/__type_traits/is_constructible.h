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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTRUCTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTRUCTIBLE_H

#include <asc/std/detail/__config>

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

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __is_construct {
struct __nat {};
}  // namespace __is_construct

#if !defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTRUCTIBLE) ||              \
    defined(CANN_ASC_STL_DETAIL_ACCL_TESTING_FALLBACK_IS_CONSTRUCTIBLE) || \
    defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_CONSTRUCTIBLE_FALLBACK)

template <class _Tp, class... _Args>
struct __accl_is_constructible;

template <class _To, class _From>
struct __is_invalid_base_to_derived_cast {
    static_assert(is_reference_v<_To>, "Wrong specialization");
    using _RawFrom = remove_cvref_t<_From>;
    using _RawTo = remove_cvref_t<_To>;
    static constexpr bool value = _And<_IsNotSame<_RawFrom, _RawTo>, is_base_of<_RawFrom, _RawTo>,
        _Not<__accl_is_constructible<_RawTo, _From>>>::value;
};

template <class _To, class _From>
struct __is_invalid_lvalue_to_rvalue_cast : false_type {
    static_assert(is_reference_v<_To>, "Wrong specialization");
};

template <class _ToRef, class _FromRef>
struct __is_invalid_lvalue_to_rvalue_cast<_ToRef&&, _FromRef&> {
    using _RawFrom = remove_cvref_t<_FromRef>;
    using _RawTo = remove_cvref_t<_ToRef>;
    static constexpr bool value =
        _And<_Not<is_function<_RawTo>>, _Or<_IsSame<_RawFrom, _RawTo>, is_base_of<_RawTo, _RawFrom>>>::value;
};

struct __is_constructible_helper {
    template <class _To>
    CANN_ASC_STL_API static void __eat(_To);

    template <class _To, class _From, class = decltype(__eat<_To>(declval<_From>()))>
    CANN_ASC_STL_API static true_type __test_cast(int);

    template <class _To, class _From, class = decltype(static_cast<_To>(declval<_From>()))>
    CANN_ASC_STL_API static integral_constant<bool,
        !__is_invalid_base_to_derived_cast<_To, _From>::value && !__is_invalid_lvalue_to_rvalue_cast<_To, _From>::value>
    __test_cast(long);

    template <class, class>
    CANN_ASC_STL_API static false_type __test_cast(...);

    template <class _Tp, class... _Args, class = decltype(_Tp(declval<_Args>()...))>
    CANN_ASC_STL_API static true_type __test_nary(int);

    template <class _Tp, class...>
    CANN_ASC_STL_API static false_type __test_nary(...);

    template <class _Tp, class _A0, class = decltype(::new _Tp(declval<_A0>()))>
    CANN_ASC_STL_API static is_destructible<_Tp> __test_unary(int);

    template <class, class>
    CANN_ASC_STL_API static false_type __test_unary(...);
};

template <class _Tp, bool = is_void_v<_Tp>>
struct __is_default_constructible : decltype(__is_constructible_helper::__test_nary<_Tp>(0)) {};

template <class _Tp>
struct __is_default_constructible<_Tp, true> : false_type {};

template <class _Tp>
struct __is_default_constructible<_Tp[], false> : false_type {};

template <class _Tp, size_t _Nx>
struct __is_default_constructible<_Tp[_Nx], false> : __is_default_constructible<remove_all_extents_t<_Tp>> {};

template <class _Tp, class... _Args>
struct __accl_is_constructible {
    static_assert(sizeof...(_Args) > 1, "Wrong specialization");
    using type = decltype(__is_constructible_helper::__test_nary<_Tp, _Args...>(0));
};

template <class _Tp>
struct __accl_is_constructible<_Tp> : __is_default_constructible<_Tp> {};

template <class _Tp, class _A0>
struct __accl_is_constructible<_Tp, _A0> : decltype(__is_constructible_helper::__test_unary<_Tp, _A0>(0)) {};

template <class _Tp, class _A0>
struct __accl_is_constructible<_Tp&, _A0> : decltype(__is_constructible_helper::__test_cast<_Tp&, _A0>(0)) {};

template <class _Tp, class _A0>
struct __accl_is_constructible<_Tp&&, _A0> : decltype(__is_constructible_helper::__test_cast<_Tp&&, _A0>(0)) {};

#endif

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTRUCTIBLE) && \
    !defined(CANN_ASC_STL_DETAIL_ACCL_USE_IS_CONSTRUCTIBLE_FALLBACK)

template <class _Tp, class... _Args>
struct is_constructible : integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTRUCTIBLE(_Tp, _Args...)> {};

template <class _Tp, class... _Args>
inline constexpr bool is_constructible_v = CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTRUCTIBLE(_Tp, _Args...);

#else

template <class _Tp, class... _Args>
struct is_constructible : __accl_is_constructible<_Tp, _Args...>::type {};

template <class _Tp, class... _Args>
inline constexpr bool is_constructible_v = is_constructible<_Tp, _Args...>::value;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTRUCTIBLE_H
