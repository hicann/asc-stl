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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MAKE_HEAP_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MAKE_HEAP_H

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
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/sift_down.h>
#include <asc/std/__iterator/iterator_traits.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class RandomAccessIterator, class Compare>
CANN_ASC_STL_API constexpr void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    using difference_type = typename iterator_traits<RandomAccessIterator>::difference_type;
    const difference_type length = last - first;
    if (length > 1) {
        for (difference_type start = (length - 2) / 2;; --start) {
            ::asc::std::__sift_down<__classic_algorithm_iterator_operations>(first, compare, length, first + start);
            if (start == 0) {
                break;
            }
        }
    }
}

template <class RandomAccessIterator>
CANN_ASC_STL_API constexpr void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    ::asc::std::make_heap(first, last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MAKE_HEAP_H
