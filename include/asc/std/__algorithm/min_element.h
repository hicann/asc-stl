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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MIN_ELEMENT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MIN_ELEMENT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class ForwardIterator, class Compare>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr ForwardIterator min_element(
    ForwardIterator first, ForwardIterator last, Compare compare)
{
    if (first == last) {
        return last;
    }
    ForwardIterator result = first;
    while (++first != last) {
        if (compare(*first, *result)) {
            result = first;
        }
    }
    return result;
}

template <class ForwardIterator>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr ForwardIterator min_element(
    ForwardIterator first, ForwardIterator last)
{
    return ::asc::std::min_element(first, last, __less{});  // NOLINT(build/include_what_you_use)
}

#if CANN_ASC_STL_DETAIL_HAS_CXX20() && !defined(CANN_ASC_STL_DETAIL_RANGES_MIN_ELEMENT_DEFINED)
#define CANN_ASC_STL_DETAIL_RANGES_MIN_ELEMENT_DEFINED
namespace ranges {
struct __min_element_fn {
    template <class Iterator, class Sentinel, class Projection = identity, class Compare = __less>
    CANN_ASC_STL_API constexpr Iterator operator()(
        Iterator first, Sentinel last, Compare compare = {}, Projection projection = {}) const
    {
        if (first == last) {
            return first;
        }
        Iterator result = first;
        while (++first != last) {
            if (::asc::std::invoke(
                    compare, ::asc::std::invoke(projection, *first), ::asc::std::invoke(projection, *result))) {
                result = first;
            }
        }
        return result;
    }
};
inline constexpr __min_element_fn min_element{};
}  // namespace ranges
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MIN_ELEMENT_H
