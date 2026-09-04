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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_CONSTRUCT_AT_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_CONSTRUCT_AT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__asc/is_non_narrowing_convertible.h>
#include <asc/std/__iterator/access.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__memory/voidify.h>
#include <asc/std/__new/device_new.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_trivially_constructible.h>
#include <asc/std/__type_traits/is_trivially_destructible.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

#if CANN_ASC_STL_DETAIL_STD_VER >= 2020  // need to backfill ::std::construct_at
#include <asc/std/__host_stdlib/memory>

#if __cpp_lib_constexpr_dynamic_alloc < 201907L
namespace std {
template <class _Tp, class... _Args,
    class = decltype(::new(::asc::std::declval<void*>()) _Tp(::asc::std::declval<_Args>()...))>
CANN_ASC_STL_API constexpr _Tp* construct_at(_Tp* __location, _Args&&... __args)
{
    return ::new (::asc::std::__voidify(*__location)) _Tp(::asc::std::forward<_Args>(__args)...);
}
}  // namespace std
#endif  // __cpp_lib_constexpr_dynamic_alloc < 201907L
#endif  // CANN_ASC_STL_DETAIL_STD_VER >= 2020

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// There is a performance issue with placement new, where EDG based compiler insert a nullptr check that is superfluous
// Because this is a noticeable performance regression, we specialize it for certain types
// This is possible because we are calling ::new ignoring any user defined overloads of operator placement new
namespace __detail {
// We cannot allow narrowing conversions between arithmetic types as the assignment will generate an error
template <class _Tp, class... _Args>
using __check_narrowing =
    conditional_t<sizeof...(_Args) == 1, __asc_internal::__is_non_narrowing_convertible<_Tp, _Args...>, true_type>;

template <class _Tp, class... _Args>
inline constexpr bool __can_optimize_construct_at = is_trivially_constructible_v<_Tp, _Args...> &&
    is_trivially_move_assignable_v<_Tp> && __check_narrowing<_Tp, _Args...>::value;
}  // namespace __detail

// construct_at
#if CANN_ASC_STL_DETAIL_STD_VER >= 2020

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class... _Args)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_constructible_v<_Tp, _Args...>)
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 _Tp* construct_at(_Tp* __location, _Args&&... __args)
{
    CANN_ASC_STL_DETAIL_ASSERT(__location != nullptr, "null pointer given to construct_at");
    // Need to go through `std::construct_at` as that is the explicitly blessed function
    CANN_ASC_STL_DETAIL_IF_CONSTEVAL
    {
        return ::std::construct_at(__location, ::asc::std::forward<_Args>(__args)...);
    }
    if constexpr (__detail::__can_optimize_construct_at<_Tp, _Args...>) {
        *__location = _Tp{::asc::std::forward<_Args>(__args)...};
        return __location;
    } else {
        return ::new (::asc::std::__voidify(*__location)) _Tp(::asc::std::forward<_Args>(__args)...);
    }
}
#endif  // CANN_ASC_STL_DETAIL_STD_VER >= 2020

template <class _Tp, class... _Args>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 _Tp* __construct_at(_Tp* __location, _Args&&... __args)
{
    CANN_ASC_STL_DETAIL_ASSERT(__location != nullptr, "null pointer given to construct_at");
#if CANN_ASC_STL_DETAIL_STD_VER >= 2020
    // Need to go through `std::construct_at` as that is the explicitly blessed function
    CANN_ASC_STL_DETAIL_IF_CONSTEVAL
    {
        return ::std::construct_at(__location, ::asc::std::forward<_Args>(__args)...);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER >= 2020
    if constexpr (__detail::__can_optimize_construct_at<_Tp, _Args...>) {
        *__location = _Tp{::asc::std::forward<_Args>(__args)...};
        return __location;
    } else {
        return ::new (::asc::std::__voidify(*__location)) _Tp(::asc::std::forward<_Args>(__args)...);
    }
}

// destroy_at

// The internal functions are available regardless of the language version (with the exception of the `__destroy_at`
// taking an array).
template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __destroy(_ForwardIterator, _ForwardIterator);

template <class _Tp>
CANN_ASC_STL_API constexpr void __destroy_at([[maybe_unused]] _Tp* __loc)
{
    CANN_ASC_STL_DETAIL_ASSERT(__loc != nullptr, "null pointer given to __destroy_at");
    if constexpr (is_trivially_destructible_v<_Tp>) {
        return;
    } else if constexpr (is_array_v<_Tp>) {
        ::asc::std::__destroy(::asc::std::__begin_cpo{}(*__loc), ::asc::std::__end_cpo{}(*__loc));
    } else {
        __loc->~_Tp();
    }
}

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __destroy(_ForwardIterator __first, _ForwardIterator __last)
{
    for (; __first != __last; ++__first) {
        ::asc::std::__destroy_at(::asc::std::addressof(*__first));
    }
    return __first;
}

template <class _BidirectionalIterator>
CANN_ASC_STL_API constexpr _BidirectionalIterator __reverse_destroy(
    _BidirectionalIterator __first, _BidirectionalIterator __last)
{
    while (__last != __first) {
        --__last;
        ::asc::std::__destroy_at(::asc::std::addressof(*__last));
    }
    return __last;
}

template <class _Tp>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void destroy_at([[maybe_unused]] _Tp* __loc)
{
    CANN_ASC_STL_DETAIL_ASSERT(__loc != nullptr, "null pointer given to __destroy_at");
    if constexpr (is_trivially_destructible_v<_Tp>) {
        return;
    } else if constexpr (is_array_v<_Tp>) {
        ::asc::std::__destroy(::asc::std::__begin_cpo{}(*__loc), ::asc::std::__end_cpo{}(*__loc));
    } else {
        __loc->~_Tp();
    }
}

template <class _ForwardIterator>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 void destroy(
    _ForwardIterator __first, _ForwardIterator __last) noexcept
{
    (void)::asc::std::__destroy(
        ::asc::std::move(__first), ::asc::std::move(__last));  // NOLINT(build/include_what_you_use)
}

template <class _ForwardIterator, class _Size>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 _ForwardIterator destroy_n(_ForwardIterator __first, _Size __n)
{
    for (; __n > 0; (void)++__first, --__n) {
        ::asc::std::__destroy_at(::asc::std::addressof(*__first));
    }
    return __first;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_CONSTRUCT_AT_H
