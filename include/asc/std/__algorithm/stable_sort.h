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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_STABLE_SORT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_STABLE_SORT_H

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
#include <asc/std/__algorithm/inplace_merge.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/sort.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/construct_at.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_copy_assignable.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
#define CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API CANN_ASC_STL_HOST_API
#else
#define CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API CANN_ASC_STL_API
#endif

template <class RandomAccessIterator, class Compare>
CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API constexpr void stable_sort(
    RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
    using difference_type = typename iterator_traits<RandomAccessIterator>::difference_type;
    const difference_type count = last - first;
    for (difference_type width = 1; width < count;) {
        for (difference_type offset = 0; offset < count - width; offset += width * 2) {
            const auto right = count - offset < width * 2 ? count : offset + width * 2;
            ::asc::std::inplace_merge(first + offset, first + offset + width, first + right, compare);
        }
        if (width > count / 2) {
            break;
        }
        width *= 2;
    }
}

template <class RandomAccessIterator>
CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API constexpr void stable_sort(
    RandomAccessIterator first, RandomAccessIterator last)
{
    ::asc::std::stable_sort(first, last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#undef CANN_ASC_STL_DETAIL_STABLE_ALGORITHM_API

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_STABLE_SORT_H
