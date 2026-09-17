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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_VIEW_INTERFACE_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_VIEW_INTERFACE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/prev.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/empty.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Tp>
concept __can_empty = requires(_Tp& __t) { ::asc::std::ranges::__empty_cpo{}(__t); };
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(
    __can_empty_, requires(_Tp& __t)(typename(decltype(::asc::std::ranges::__empty_cpo{}(__t)))));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __can_empty = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__can_empty_, _Tp);
#endif  // !concepts

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Derived>
    requires is_class_v<_Derived> && same_as<_Derived, remove_cv_t<_Derived>>
class view_interface {
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
// The default template argument is already provided by the forward declaration in <__ranges/enable_view.h>; it is not
// repeated at the definition.
template <class _Derived, enable_if_t<is_class_v<_Derived> && same_as<_Derived, remove_cv_t<_Derived>>, int>>
class view_interface {
#endif  // !concepts
    CANN_ASC_STL_API constexpr _Derived& __derived() noexcept
    {
        static_assert(sizeof(_Derived) && derived_from<_Derived, view_interface> && view<_Derived>);
        return static_cast<_Derived&>(*this);
    }

    CANN_ASC_STL_API constexpr _Derived const& __derived() const noexcept
    {
        static_assert(sizeof(_Derived) && derived_from<_Derived, view_interface> && view<_Derived>);
        return static_cast<_Derived const&>(*this);
    }

public:
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(forward_range<_D2>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool empty()
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived()) == ::asc::std::ranges::__end_cpo{}(__derived());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(forward_range<const _D2>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool empty() const
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived()) == ::asc::std::ranges::__end_cpo{}(__derived());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_empty<_D2>)
    CANN_ASC_STL_API constexpr explicit operator bool()
    {
        return !::asc::std::ranges::__empty_cpo{}(__derived());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_empty<const _D2>)
    CANN_ASC_STL_API constexpr explicit operator bool() const
    {
        return !::asc::std::ranges::__empty_cpo{}(__derived());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(contiguous_iterator<iterator_t<_D2>>)
    CANN_ASC_STL_API constexpr auto data()
    {
        return ::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        range<const _D2> CANN_ASC_STL_DETAIL_ACCL_AND contiguous_iterator<iterator_t<const _D2>>)
    CANN_ASC_STL_API constexpr auto data() const
    {
        return ::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        forward_range<_D2> CANN_ASC_STL_DETAIL_ACCL_AND sized_sentinel_for<sentinel_t<_D2>, iterator_t<_D2>>)
    CANN_ASC_STL_API constexpr auto size()
    {
        return ::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__derived()) - ::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(forward_range<const _D2> CANN_ASC_STL_DETAIL_ACCL_AND
            sized_sentinel_for<sentinel_t<const _D2>, iterator_t<const _D2>>)
    CANN_ASC_STL_API constexpr auto size() const
    {
        return ::asc::std::__to_unsigned_like(
            ::asc::std::ranges::__end_cpo{}(__derived()) - ::asc::std::ranges::__begin_cpo{}(__derived()));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(forward_range<_D2>)
    CANN_ASC_STL_API constexpr decltype(auto) front()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.front()` called on an empty view.");
        return *::asc::std::ranges::__begin_cpo{}(__derived());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(forward_range<const _D2>)
    CANN_ASC_STL_API constexpr decltype(auto) front() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.front()` called on an empty view.");
        return *::asc::std::ranges::__begin_cpo{}(__derived());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(bidirectional_range<_D2> CANN_ASC_STL_DETAIL_ACCL_AND common_range<_D2>)
    CANN_ASC_STL_API constexpr decltype(auto) back()
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.back()` called on an empty view.");
        return *::asc::std::ranges::__prev_cpo{}(::asc::std::ranges::__end_cpo{}(__derived()));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _D2 = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
        bidirectional_range<const _D2> CANN_ASC_STL_DETAIL_ACCL_AND common_range<const _D2>)
    CANN_ASC_STL_API constexpr decltype(auto) back() const
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            !empty(), "Precondition `!empty()` not satisfied. `.back()` called on an empty view.");
        return *::asc::std::ranges::__prev_cpo{}(::asc::std::ranges::__end_cpo{}(__derived()));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _RARange = _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_range<_RARange>)
    CANN_ASC_STL_API constexpr decltype(auto) operator[](range_difference_t<_RARange> __index)
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived())[__index];
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _RARange = const _Derived)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_range<_RARange>)
    CANN_ASC_STL_API constexpr decltype(auto) operator[](range_difference_t<_RARange> __index) const
    {
        return ::asc::std::ranges::__begin_cpo{}(__derived())[__index];
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_VIEW_INTERFACE_H
