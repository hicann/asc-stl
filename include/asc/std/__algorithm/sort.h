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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SORT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SORT_H

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
#include <asc/std/__algorithm/iter_swap.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/min_element.h>
#include <asc/std/__algorithm/partial_sort.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__bit/countl.h>
#include <asc/std/__bit/countr.h>
#include <asc/std/__bit/integral.h>
#include <asc/std/__functional/operations.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/climits>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class RandomAccessIterator, class Compare>
CANN_ASC_STL_API constexpr void sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    // In-place heapsort keeps the Device contract allocation-free and avoids
    // recursion while retaining the standard O(N log N) comparison bound.
    using difference_type = typename iterator_traits<RandomAccessIterator>::difference_type;
    const difference_type count = last - first;
    if (count < 2) {
        return;
    }
    for (difference_type root = (count - 2) / 2;; --root) {
        auto parent = root;
        while (parent * 2 + 1 < count) {
            auto child = parent * 2 + 1;
            if (child + 1 < count && compare(first[child], first[child + 1])) {
                ++child;
            }
            if (!compare(first[parent], first[child])) {
                break;
            }
            ::asc::std::iter_swap(first + parent, first + child);
            parent = child;
        }
        if (root == 0) {
            break;
        }
    }
    for (auto remaining = count; remaining > 1; --remaining) {
        ::asc::std::iter_swap(first, first + remaining - 1);
        difference_type parent = 0;
        while (parent * 2 + 1 < remaining - 1) {
            auto child = parent * 2 + 1;
            if (child + 1 < remaining - 1 && compare(first[child], first[child + 1])) {
                ++child;
            }
            if (!compare(first[parent], first[child])) {
                break;
            }
            ::asc::std::iter_swap(first + parent, first + child);
            parent = child;
        }
    }
}

template <class RandomAccessIterator>
CANN_ASC_STL_API constexpr void sort(RandomAccessIterator first, RandomAccessIterator last)
{
    ::asc::std::sort(first, last, __less{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SORT_H
