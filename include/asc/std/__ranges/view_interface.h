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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_VIEW_INTERFACE_H
#define CANN_ASC_STL_ASC_STD___RANGES_VIEW_INTERFACE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__utility/declval.h>

// Minimal equivalent inlining of the assertion chain (#ifndef guards prevent
// redefinition): debug builds (_DEBUG/DEBUG) enable ENABLE_DEBUG_MODE, which in
// turn enables host assertions; the device side has no assertion mechanism, so the
// macro is always a no-op there.
#ifndef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#if defined(_DEBUG) || defined(DEBUG)
#define CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // defined(_DEBUG) || defined(DEBUG)
#endif  // !CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE

#ifndef ASC_ENABLE_ASSERTIONS
#ifdef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#define ASC_ENABLE_ASSERTIONS
#endif  // CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // !ASC_ENABLE_ASSERTIONS

#ifndef ASC_ENABLE_HOST_ASSERTIONS
#ifdef ASC_ENABLE_ASSERTIONS
#define ASC_ENABLE_HOST_ASSERTIONS
#endif  // ASC_ENABLE_ASSERTIONS
#endif  // !ASC_ENABLE_HOST_ASSERTIONS

#ifndef CANN_ASC_STL_DETAIL_ASSERT
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// ASC device side has no assertion mechanism
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#elif defined(ASC_ENABLE_HOST_ASSERTIONS)
#ifdef NDEBUG
// <assert.h> is not necessarily included under NDEBUG; declare the prototype manually
extern "C" {
void __assert_fail(const char* __assertion, const char* __file, unsigned int __line, const char* __function) noexcept
    __attribute__((__noreturn__));
}  // extern "C"
#else
#include <assert.h>
#endif  // NDEBUG
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    __builtin_expect(static_cast<bool>(expression), 1) ? (void)0 : __assert_fail(message, __FILE__, __LINE__, __func__)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#endif  // ASC_ENABLE_HOST_ASSERTIONS
#endif  // !CANN_ASC_STL_DETAIL_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// This file can be pulled in at the tail of enable_view.h, i.e. parsed during a
// window in the include chain where concepts.h has not yet defined its ranges
// concept bodies; the compiler checks for undeclared names already at
// template-definition time, so the ranges concepts here are expressed as private
// equivalents depending only on already-complete headers (each expansion is
// clause-for-clause equivalent to concepts.h). Iterator-level concepts and
// iterator_t are already complete in __iterator/concepts.h and access.h, so they
// can be used directly.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <class _Tp>
concept __vi_range = requires(_Tp& __t) {
    ::asc::std::ranges::begin(__t);
    ::asc::std::ranges::end(__t);
};

template <class _Tp>
concept __vi_input_range = __vi_range<_Tp> && input_iterator<iterator_t<_Tp>>;

template <class _Tp>
concept __vi_forward_range = __vi_input_range<_Tp> && forward_iterator<iterator_t<_Tp>>;

template <class _Tp>
concept __vi_bidirectional_range = __vi_forward_range<_Tp> && bidirectional_iterator<iterator_t<_Tp>>;

template <class _Tp>
concept __vi_random_access_range = __vi_bidirectional_range<_Tp> && random_access_iterator<iterator_t<_Tp>>;

template <class _Tp>
concept __vi_common_range =
    __vi_range<_Tp> && same_as<iterator_t<_Tp>, decltype(::asc::std::ranges::end(::asc::std::declval<_Tp&>()))>;

template <class _Tp>
concept __vi_view = __vi_range<_Tp> && movable<_Tp> && enable_view<_Tp>;

template <class _Tp>
concept __can_empty = requires(_Tp& __t) { ::asc::std::ranges::__empty_cpo{}(__t); };

template <class _Tp>
using __vi_sentinel_t = decltype(::asc::std::ranges::end(::asc::std::declval<_Tp&>()));

template <class _Tp>
using __vi_difference_t = iter_difference_t<iterator_t<_Tp>>;
#endif

// The default template argument of the C++17 form is already provided by the forward declaration
// in <asc/std/__ranges/enable_view.h>; it is not repeated at the definition.
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Derived>
    requires is_class_v<_Derived> && same_as<_Derived, remove_cv_t<_Derived>>
class view_interface {
#else
template <class _Derived, enable_if_t<is_class_v<_Derived> && is_same_v<_Derived, remove_cv_t<_Derived>>, int>>
class view_interface {
#endif

private:
    CANN_ASC_STL_API constexpr _Derived& __derived() noexcept
    {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        static_assert(sizeof(_Derived) && derived_from<_Derived, view_interface> && __vi_view<_Derived>);
#endif
        return static_cast<_Derived&>(*this);
    }

    CANN_ASC_STL_API constexpr const _Derived& __derived() const noexcept
    {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
        static_assert(sizeof(_Derived) && derived_from<_Derived, view_interface> && __vi_view<_Derived>);
#endif
        return static_cast<const _Derived&>(*this);
    }

public:
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class _D2 = _Derived>
        requires __vi_forward_range<_D2>
    CANN_ASC_STL_API constexpr bool empty()
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived()) == ::asc::std::ranges::__end_cpo{}(__derived());
    }

    template <class _D2 = _Derived>
        requires __vi_forward_range<const _D2>
    CANN_ASC_STL_API constexpr bool empty() const
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived()) == ::asc::std::ranges::__end_cpo{}(__derived());
    }

    template <class _D2 = _Derived>
        requires __can_empty<_D2>
    CANN_ASC_STL_API constexpr explicit operator bool()
    {
        return !::asc::std::ranges::__empty_cpo{}(__derived());
    }

    template <class _D2 = _Derived>
        requires __can_empty<const _D2>
    CANN_ASC_STL_API constexpr explicit operator bool() const
    {
        return !::asc::std::ranges::__empty_cpo{}(__derived());
    }

    template <class _D2 = _Derived>
        requires contiguous_iterator<iterator_t<_D2>>
    CANN_ASC_STL_API constexpr auto data()
    {
        return ::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    template <class _D2 = _Derived>
        requires __vi_range<const _D2> && contiguous_iterator<iterator_t<const _D2>>
    CANN_ASC_STL_API constexpr auto data() const
    {
        return ::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    template <class _D2 = _Derived>
        requires __vi_forward_range<_D2> && sized_sentinel_for<__vi_sentinel_t<_D2>, iterator_t<_D2>>
    CANN_ASC_STL_API constexpr auto size()
    {
        return ::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__derived()) - ::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    template <class _D2 = _Derived>
        requires __vi_forward_range<const _D2> && sized_sentinel_for<__vi_sentinel_t<const _D2>, iterator_t<const _D2>>
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__derived()) - ::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    template <class _D2 = _Derived>
        requires __vi_forward_range<_D2>
    CANN_ASC_STL_API constexpr decltype(auto) front()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.front()` called on an empty view.");
        return *::asc::std::ranges::__begin_cpo{}(__derived());
    }

    template <class _D2 = _Derived>
        requires __vi_forward_range<const _D2>
    CANN_ASC_STL_API constexpr decltype(auto) front() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.front()` called on an empty view.");
        return *::asc::std::ranges::__begin_cpo{}(__derived());
    }

    template <class _D2 = _Derived>
        requires __vi_bidirectional_range<_D2> && __vi_common_range<_D2>
    CANN_ASC_STL_API constexpr decltype(auto) back()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.back()` called on an empty view.");
        auto __end = ::asc::std::ranges::__end_cpo{}(__derived());
        return *--__end;
    }

    template <class _D2 = _Derived>
        requires __vi_bidirectional_range<const _D2> && __vi_common_range<const _D2>
    CANN_ASC_STL_API constexpr decltype(auto) back() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.back()` called on an empty view.");
        auto __end = ::asc::std::ranges::__end_cpo{}(__derived());
        return *--__end;
    }

    template <class _RARange = _Derived>
        requires __vi_random_access_range<_RARange>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](__vi_difference_t<_RARange> __index)
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived())[__index];
    }

    template <class _RARange = const _Derived>
        requires __vi_random_access_range<_RARange>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](__vi_difference_t<_RARange> __index) const
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived())[__index];
    }
#else
    // C++17 and device-side shape: constraints are not evaluable (no concept
    // fallback), so the members are unconstrained.
    CANN_ASC_STL_API constexpr bool empty()
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived()) == ::asc::std::ranges::__end_cpo{}(__derived());
    }

    CANN_ASC_STL_API constexpr bool empty() const
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived()) == ::asc::std::ranges::__end_cpo{}(__derived());
    }

    CANN_ASC_STL_API constexpr explicit operator bool()
    {
        return !::asc::std::ranges::__empty_cpo{}(__derived());
    }

    CANN_ASC_STL_API constexpr explicit operator bool() const
    {
        return !::asc::std::ranges::__empty_cpo{}(__derived());
    }

    CANN_ASC_STL_API constexpr auto data()
    {
        return ::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    CANN_ASC_STL_API constexpr auto data() const
    {
        return ::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    CANN_ASC_STL_API constexpr auto size()
    {
        return ::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__derived()) - ::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__derived()) - ::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    CANN_ASC_STL_API constexpr decltype(auto) front()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.front()` called on an empty view.");
        return *::asc::std::ranges::__begin_cpo{}(__derived());
    }

    CANN_ASC_STL_API constexpr decltype(auto) front() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.front()` called on an empty view.");
        return *::asc::std::ranges::__begin_cpo{}(__derived());
    }

    CANN_ASC_STL_API constexpr decltype(auto) back()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.back()` called on an empty view.");
        auto __end = ::asc::std::ranges::__end_cpo{}(__derived());
        return *--__end;
    }

    CANN_ASC_STL_API constexpr decltype(auto) back() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.back()` called on an empty view.");
        auto __end = ::asc::std::ranges::__end_cpo{}(__derived());
        return *--__end;
    }

    template <class _Difference>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](_Difference __index)
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived())[__index];
    }

    template <class _Difference>
    CANN_ASC_STL_API constexpr decltype(auto) operator[](_Difference __index) const
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived())[__index];
    }
#endif
};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_VIEW_INTERFACE_H
