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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SORT_HEAP_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SORT_HEAP_H

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
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/pop_heap.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr void sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    static_assert(is_copy_constructible_v<_RandomAccessIterator>, "Iterators must be copy constructible.");
    static_assert(is_copy_assignable_v<_RandomAccessIterator>, "Iterators must be copy assignable.");

    __comp_ref_type<_Compare> __comp_ref = __comp;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    for (difference_type __n = __last - __first; __n > 1; --__last, (void)--__n) {
        ::asc::std::pop_heap(__first, __last, __comp_ref);
    }
}

template <class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void sort_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    ::asc::std::sort_heap(__first, __last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SORT_HEAP_H
