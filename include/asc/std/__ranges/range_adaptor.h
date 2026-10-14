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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_RANGE_ADAPTOR_H
#define CANN_ASC_STL_ASC_STD___RANGES_RANGE_ADAPTOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__functional/compose.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/ctad_support.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

//! @brief CRTP base: a type deriving from it is recognized by the library as a
//! range adaptor closure and gains the pipe operator, so `x | f` is equivalent
//! to `f(x)` and `f1 | f2` composes into a new closure equivalent to `f2(f1(x))`.
template <class _Tp, enable_if_t<is_class_v<_Tp>, int> = 0, enable_if_t<is_same_v<_Tp, remove_cv_t<_Tp>>, int> = 0>
struct __range_adaptor_closure {};

//! @brief Wraps an arbitrary function object into an adaptor closure invocable as `x | f`.
template <class _Fn>
struct __pipeable : _Fn, __range_adaptor_closure<__pipeable<_Fn>> {
    CANN_ASC_STL_API constexpr explicit __pipeable(_Fn&& __f) : _Fn(::asc::std::move(__f))
    {}
};
CANN_ASC_STL_DETAIL_CTAD_SUPPORTED_FOR_TYPE(__pipeable);

template <class _Tp>
CANN_ASC_STL_API _Tp __derived_from_range_adaptor_closure(__range_adaptor_closure<_Tp>*);

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class _Tp>
concept __is_range_adaptor_closure = requires {
    requires(!::asc::std::ranges::range<remove_cvref_t<_Tp>>);
    {
        ::asc::std::ranges::__derived_from_range_adaptor_closure(static_cast<remove_cvref_t<_Tp>*>(nullptr))
    } -> ::asc::std::same_as<remove_cvref_t<_Tp>>;
};

template <class _Range, class _Closure>
concept __range_adaptor_can_pipe_invoke = requires {
    requires(range<_Range>);
    requires(__is_range_adaptor_closure<_Closure>);
    requires(invocable<_Closure, _Range>);
};

template <class _Closure, class _OtherClosure>
concept __range_adaptor_can_pipe_compose = requires {
    requires(__is_range_adaptor_closure<_Closure>);
    requires(__is_range_adaptor_closure<_OtherClosure>);
    requires(constructible_from<decay_t<_Closure>, _Closure>);
    requires(constructible_from<decay_t<_OtherClosure>, _OtherClosure>);
};

template <class _Range, class _Closure>
    requires __range_adaptor_can_pipe_invoke<_Range, _Closure>
CANN_ASC_STL_API constexpr decltype(auto) operator|(_Range&& __range, _Closure&& __closure) noexcept(
    noexcept(::asc::std::invoke(::asc::std::declval<_Closure>(), ::asc::std::declval<_Range>())))
{
    return ::asc::std::invoke(::asc::std::forward<_Closure>(__closure), ::asc::std::forward<_Range>(__range));
}

template <class _Closure, class _OtherClosure>
    requires __range_adaptor_can_pipe_compose<_Closure, _OtherClosure>
CANN_ASC_STL_API constexpr auto operator|(_Closure&& __closure, _OtherClosure&& __other_closure) noexcept(
    is_nothrow_constructible_v<decay_t<_Closure>, _Closure> &&
    is_nothrow_constructible_v<decay_t<_OtherClosure>, _OtherClosure>)
{
    return __pipeable(::asc::std::__compose(
        ::asc::std::forward<_OtherClosure>(__other_closure), ::asc::std::forward<_Closure>(__closure)));
}

#else  // ^^^ concept-constrained version (disabled for device compilation) ^^^ / vvv SFINAE fallback version vvv

// Concept constraints are expanded here as the conventional void_t detection
// structs + enable_if_t, with semantics identical to the concepts version.
template <class _Tp, class = void>
struct __is_range_like : false_type {};
template <class _Tp>
struct __is_range_like<_Tp,
    void_t<decltype(::asc::std::ranges::__begin_cpo{}(::asc::std::declval<_Tp&>())),
        decltype(::asc::std::ranges::__end_cpo{}(::asc::std::declval<_Tp&>()))>> : true_type {};

template <class _Tp, class = void>
struct __derives_from_range_adaptor_closure : false_type {};
template <class _Tp>
struct __derives_from_range_adaptor_closure<_Tp,
    void_t<decltype(::asc::std::ranges::__derived_from_range_adaptor_closure(
        static_cast<remove_cvref_t<_Tp>*>(nullptr)))>>
    : bool_constant<is_same_v<decltype(::asc::std::ranges::__derived_from_range_adaptor_closure(
                                  static_cast<remove_cvref_t<_Tp>*>(nullptr))),
          remove_cvref_t<_Tp>>> {};

template <class _Tp>
struct __is_range_adaptor_closure : bool_constant<!__is_range_like<remove_cvref_t<_Tp>>::value &&
                                        __derives_from_range_adaptor_closure<remove_cvref_t<_Tp>>::value> {};

template <class _Range, class _Closure, class = void>
struct __can_pipe_invoke_impl : false_type {};
template <class _Range, class _Closure>
struct __can_pipe_invoke_impl<_Range, _Closure,
    void_t<decltype(::asc::std::invoke(::asc::std::declval<_Closure>(), ::asc::std::declval<_Range>()))>>
    : bool_constant<__is_range_like<_Range>::value && __is_range_adaptor_closure<_Closure>::value> {};

template <class _Range, class _Closure>
struct __range_adaptor_can_pipe_invoke : __can_pipe_invoke_impl<_Range, _Closure> {};

template <class _Closure, class _OtherClosure>
struct __range_adaptor_can_pipe_compose
    : bool_constant<__is_range_adaptor_closure<_Closure>::value && __is_range_adaptor_closure<_OtherClosure>::value &&
          is_constructible_v<decay_t<_Closure>, _Closure> &&
          is_constructible_v<decay_t<_OtherClosure>, _OtherClosure>> {};

template <class _Range, class _Closure, enable_if_t<__range_adaptor_can_pipe_invoke<_Range, _Closure>::value, int> = 0>
CANN_ASC_STL_API constexpr decltype(auto) operator|(_Range&& __range, _Closure&& __closure) noexcept(
    noexcept(::asc::std::invoke(::asc::std::declval<_Closure>(), ::asc::std::declval<_Range>())))
{
    return ::asc::std::invoke(::asc::std::forward<_Closure>(__closure), ::asc::std::forward<_Range>(__range));
}

template <class _Closure, class _OtherClosure,
    enable_if_t<__range_adaptor_can_pipe_compose<_Closure, _OtherClosure>::value, int> = 0>
CANN_ASC_STL_API constexpr auto operator|(_Closure&& __closure, _OtherClosure&& __other_closure) noexcept(
    is_nothrow_constructible_v<decay_t<_Closure>, _Closure> &&
    is_nothrow_constructible_v<decay_t<_OtherClosure>, _OtherClosure>)
{
    return __pipeable(::asc::std::__compose(::asc::std::forward<_OtherClosure>(__other_closure),
        ::asc::std::forward<_Closure>(__closure)));  // NOLINT(build/include_what_you_use)
}

#endif  // concept-constrained version / SFINAE fallback version

//! @brief Public base: derive from it to declare a custom range adaptor closure.
template <class Derived>
class range_adaptor_closure : public __range_adaptor_closure<Derived> {};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_RANGE_ADAPTOR_H
