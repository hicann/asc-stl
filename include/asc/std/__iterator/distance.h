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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_DISTANCE_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_DISTANCE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __distance_detail {

// Minimal local equivalents of the traversal probes used by the migrated
// implementation: a category probe against iterator_traits and a concept probe
// against a member iterator_concept, both SFINAE-friendly in C++17 mode.
template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_category_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool
    __has_iterator_category_convertible_to<Iter, Tag, void_t<typename iterator_traits<Iter>::iterator_category>> =
        is_convertible_v<typename iterator_traits<Iter>::iterator_category, Tag>;

template <class Iter, class Tag, class = void>
inline constexpr bool __has_iterator_concept_convertible_to = false;

template <class Iter, class Tag>
inline constexpr bool __has_iterator_concept_convertible_to<Iter, Tag, void_t<typename Iter::iterator_concept>> =
    is_convertible_v<typename Iter::iterator_concept, Tag>;

template <class Iter>
inline constexpr bool __has_random_access_traversal =
    __has_iterator_category_convertible_to<Iter, random_access_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, random_access_iterator_tag>;

}  // namespace __distance_detail

template <class _InputIter>
CANN_ASC_STL_API constexpr typename iterator_traits<_InputIter>::difference_type distance(
    _InputIter __first, _InputIter __last)
{
    // To support pointers to incomplete types
    if constexpr (__distance_detail::__has_random_access_traversal<_InputIter>) {
        return __last - __first;
    }
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    else if constexpr (sized_sentinel_for<_InputIter, _InputIter>) {
        return __last - __first;
    }
#endif      // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    else {  // NOLINT(readability/braces)
        typename iterator_traits<_InputIter>::difference_type __r(0);
        for (; __first != __last; ++__first) {
            ++__r;
        }
        return __r;
    }
}

CANN_ASC_STL_END_NAMESPACE

// [range.iter.op.distance]

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

namespace __distance {
struct __fn {
    template <class _Ip, class _Sp, enable_if_t<sentinel_for<_Sp, _Ip> && !sized_sentinel_for<_Sp, _Ip>, int> = 0>
    CANN_ASC_STL_API constexpr iter_difference_t<_Ip> operator()(_Ip __first, _Sp __last) const
    {
        iter_difference_t<_Ip> __n = 0;
        while (__first != __last) {
            ++__first;
            ++__n;
        }
        return __n;
    }

    template <class _Ip, class _Sp, enable_if_t<sized_sentinel_for<_Sp, decay_t<_Ip>>, int> = 0>
    CANN_ASC_STL_API constexpr iter_difference_t<_Ip> operator()(_Ip&& __first, _Sp __last) const
    {
        if constexpr (sized_sentinel_for<_Sp, remove_cvref_t<_Ip>>) {
            return __last - __first;
        } else {
            return __last - decay_t<_Ip>(__first);
        }
    }

    template <class _Rp, enable_if_t<range<_Rp>, int> = 0>
    CANN_ASC_STL_API constexpr range_difference_t<_Rp> operator()(_Rp&& __r) const
    {
        if constexpr (sized_range<_Rp>) {
            return static_cast<range_difference_t<_Rp>>(::asc::std::ranges::__size_cpo{}(__r));
        } else {
            return operator()(::asc::std::ranges::__begin_cpo{}(__r), ::asc::std::ranges::__end_cpo{}(__r));
        }
    }
};
}  // namespace __distance

inline namespace __cpo {
inline constexpr auto distance = __distance::__fn{};

// Avoid using the CPO object internally because of __tile__ access.
using __distance_cpo = __distance::__fn;
}  // namespace __cpo

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_DISTANCE_H
