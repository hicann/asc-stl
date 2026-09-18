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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SIFT_DOWN_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SIFT_DOWN_H

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
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __sift_down(_RandomAccessIterator __first, _Compare&& __comp,
    typename iterator_traits<_RandomAccessIterator>::difference_type __len, _RandomAccessIterator __start)
{
    using _Ops = _AlgPolicy;

    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    // left-child of __start is at 2 * __start + 1
    // right-child of __start is at 2 * __start + 2
    difference_type __child = __start - __first;

    if (__len < 2 || (__len - 2) / 2 < __child) {
        return;
    }

    __child = 2 * __child + 1;
    _RandomAccessIterator __child_i = __first + __child;

    if ((__child + 1) < __len && __comp(*__child_i, *(__child_i + difference_type(1)))) {
        // right-child exists and is greater than left-child
        ++__child_i;
        ++__child;
    }

    // check if we are in heap-order
    if (__comp(*__child_i, *__start)) {
        // we are, __start is larger than its largest child
        return;
    }

    value_type __top(_Ops::iter_move(__start));
    do {
        // we are not in heap-order, swap the parent with its largest child
        *__start = _Ops::iter_move(__child_i);
        __start = __child_i;

        if ((__len - 2) / 2 < __child) {
            break;
        }

        // recompute the child based off of the updated parent
        __child = 2 * __child + 1;
        __child_i = __first + __child;

        if ((__child + 1) < __len && __comp(*__child_i, *(__child_i + difference_type(1)))) {
            // right-child exists and is greater than left-child
            ++__child_i;
            ++__child;
        }

        // check if we are in heap-order
    } while (!__comp(*__child_i, __top));
    *__start = ::asc::std::move(__top);  // NOLINT(build/include_what_you_use)
}

template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr _RandomAccessIterator __floyd_sift_down(_RandomAccessIterator __first, _Compare&& __comp,
    typename iterator_traits<_RandomAccessIterator>::difference_type __len)
{
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;

    _RandomAccessIterator __hole = __first;
    _RandomAccessIterator __child_i = __first;
    difference_type __child = 0;

    while (true) {
        __child_i += difference_type(__child + 1);
        __child = 2 * __child + 1;

        if ((__child + 1) < __len && __comp(*__child_i, *(__child_i + difference_type(1)))) {
            // right-child exists and is greater than left-child
            ++__child_i;
            ++__child;
        }

        // swap __hole with its largest child
        *__hole = _AlgPolicy::iter_move(__child_i);
        __hole = __child_i;

        // if __hole is now a leaf, we're done
        if (__child > (__len - 2) / 2) {
            break;
        }
    }
    return __hole;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SIFT_DOWN_H
