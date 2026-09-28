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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_EQUAL_RANGE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_EQUAL_RANGE_H

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
#include <asc/std/__algorithm/lower_bound.h>
#include <asc/std/__algorithm/upper_bound.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class ForwardIterator, class T, class Compare>
CANN_ASC_STL_API constexpr pair<ForwardIterator, ForwardIterator> equal_range(  // NOLINT(build/include_what_you_use)
    ForwardIterator first, ForwardIterator last, const T& value, Compare compare)
{
    const ForwardIterator lower = ::asc::std::lower_bound(first, last, value, compare);
    return pair<ForwardIterator, ForwardIterator>(  // NOLINT(build/include_what_you_use)
        lower, ::asc::std::upper_bound(lower, last, value, compare));
}

template <class ForwardIterator, class T>
CANN_ASC_STL_API constexpr pair<ForwardIterator, ForwardIterator> equal_range(  // NOLINT(build/include_what_you_use)
    ForwardIterator first, ForwardIterator last, const T& value)
{
    return ::asc::std::equal_range(first, last, value, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_EQUAL_RANGE_H
