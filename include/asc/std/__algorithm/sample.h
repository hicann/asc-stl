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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SAMPLE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SAMPLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/min.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__random/uniform_int_distribution.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/move.h>

// Always a no-op on the device side (no assertion mechanism there); checked on
// the host side only when ASC_ENABLE_HOST_ASSERTIONS is explicitly enabled.
#ifndef CANN_ASC_STL_DETAIL_ASSERT
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __sample_detail {

// Minimal local traversal-category probes: a category probe against
// iterator_traits and a probe for the member iterator_concept, both
// SFINAE-friendly under C++17.
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
inline constexpr bool __has_forward_traversal = __has_iterator_category_convertible_to<Iter, forward_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, forward_iterator_tag>;

template <class Iter>
inline constexpr bool __has_random_access_traversal =
    __has_iterator_category_convertible_to<Iter, random_access_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, random_access_iterator_tag>;

template <class Iter, class = void>
inline constexpr bool __has_member_iterator_concept = false;

template <class Iter>
inline constexpr bool __has_member_iterator_concept<Iter, void_t<typename Iter::iterator_concept>> = true;

// C++20 iterators often declare a stronger traversal category in
// iterator_concept than in iterator_category; deduce the effective dispatch
// tag from the stronger of the two.
template <class Iter>
CANN_ASC_STL_API constexpr auto __iterator_traits_category_or_concept() noexcept
{
    if constexpr (!__has_member_iterator_concept<Iter>) {
        return typename iterator_traits<Iter>::iterator_category{};
    } else if constexpr (__has_random_access_traversal<Iter>) {
        return random_access_iterator_tag{};
    } else if constexpr (__has_forward_traversal<Iter>) {
        return forward_iterator_tag{};
    } else {
        return typename Iter::iterator_category{};
    }
}

template <class Iter>
using __iterator_traits_category_or_concept_t = decltype(__iterator_traits_category_or_concept<Iter>());

}  // namespace __sample_detail

template <class _PopulationIterator, class _SampleIterator, class _Distance, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API _SampleIterator __sample(_PopulationIterator __first, _PopulationIterator __last,
    _SampleIterator __output_iter, _Distance __n, _UniformRandomNumberGenerator& __g, input_iterator_tag)
{
    _Distance __k = 0;
    for (; __first != __last && __k < __n; ++__first, (void)++__k) {
        __output_iter[__k] = *__first;
    }
    _Distance __sz = __k;
    for (; __first != __last; ++__first, (void)++__k) {
        _Distance __r = ::asc::std::uniform_int_distribution<_Distance>(0, __k)(__g);
        if (__r < __sz) {
            __output_iter[__r] = *__first;
        }
    }
    return __output_iter + ::asc::std::min(__n, __k);
}

template <class _PopulationIterator, class _SampleIterator, class _Distance, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API _SampleIterator __sample(_PopulationIterator __first, _PopulationIterator __last,
    _SampleIterator __output_iter, _Distance __n, _UniformRandomNumberGenerator& __g, forward_iterator_tag)
{
    _Distance __unsampled_sz = ::asc::std::distance(__first, __last);
    for (__n = ::asc::std::min(__n, __unsampled_sz);  // NOLINT(build/include_what_you_use)
         __n != 0; ++__first) {
        _Distance __r = ::asc::std::uniform_int_distribution<_Distance>(0, --__unsampled_sz)(__g);
        if (__r < __n) {
            *__output_iter++ = *__first;
            --__n;
        }
    }
    return __output_iter;
}

template <class _PopulationIterator, class _SampleIterator, class _Distance, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API _SampleIterator __sample(_PopulationIterator __first, _PopulationIterator __last,
    _SampleIterator __output_iter, _Distance __n, _UniformRandomNumberGenerator& __g)
{
    using _PopCategory = __sample_detail::__iterator_traits_category_or_concept_t<_PopulationIterator>;
    using _Difference = typename iterator_traits<_PopulationIterator>::difference_type;
    static_assert(__sample_detail::__has_forward_traversal<_PopulationIterator> ||
            __sample_detail::__has_random_access_traversal<_SampleIterator>,
        "SampleIterator must meet the requirements of RandomAccessIterator");
    using _CommonType = typename common_type<_Distance, _Difference>::type;
    CANN_ASC_STL_DETAIL_ASSERT(!is_signed_v<_Distance> || __n >= 0, "N must be a positive number.");
    return ::asc::std::__sample(__first, __last, __output_iter, _CommonType(__n), __g, _PopCategory());
}

template <class _PopulationIterator, class _SampleIterator, class _Distance, class _UniformRandomNumberGenerator>
CANN_ASC_STL_API _SampleIterator sample(_PopulationIterator __first, _PopulationIterator __last,
    _SampleIterator __output_iter, _Distance __n, _UniformRandomNumberGenerator&& __g)
{
    return ::asc::std::__sample(__first, __last, __output_iter, __n, __g);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SAMPLE_H
