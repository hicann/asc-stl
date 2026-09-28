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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_ROTATE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_ROTATE_H

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
#include <asc/std/__algorithm/move.h>
#include <asc/std/__algorithm/move_backward.h>
#include <asc/std/__algorithm/swap_ranges.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __rotate_left(_ForwardIterator __first, _ForwardIterator __last)
{
    // Moves the leading element to the back of the range and returns the new
    // last position; valid when the rotated prefix is exactly one element.
    using _Ops = __classic_algorithm_iterator_operations;

    auto __tmp = _Ops::iter_move(__first);
    _ForwardIterator __second = __first;
    ++__second;
    _ForwardIterator __lm1 = ::asc::std::move(__second, __last, __first);
    *__lm1 = ::asc::std::move(__tmp);  // NOLINT(build/include_what_you_use)
    return __lm1;
}

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __rotate_forward(
    _ForwardIterator __first, _ForwardIterator __middle, _ForwardIterator __last)
{
    // Universal swap-loop rotation for forward iterators; also correct for
    // bidirectional and random-access iterators.
    using _Ops = __classic_algorithm_iterator_operations;

    _ForwardIterator __i = __middle;
    while (true) {
        _Ops::iter_swap(__first, __i);
        ++__first;
        if (++__i == __last) {
            break;
        }
        if (__first == __middle) {
            __middle = __i;
        }
    }
    _ForwardIterator __r = __first;
    if (__first != __middle) {
        __i = __middle;
        while (true) {
            _Ops::iter_swap(__first, __i);
            ++__first;
            if (++__i == __last) {
                if (__first == __middle) {
                    break;
                }
                __i = __middle;
            } else if (__first == __middle) {
                __middle = __i;
            }
        }
    }
    return __r;
}

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __rotate_right(_ForwardIterator __first, _ForwardIterator __middle)
{
    // Rotates a one-element suffix to the front using only forward-iterator
    // operations.  The original leading element moves to the returned slot.
    using _Ops = __classic_algorithm_iterator_operations;

    _ForwardIterator __result = __first;
    ++__result;
    while (__first != __middle) {
        _Ops::iter_swap(__first, __middle);
        ++__first;
    }
    return __result;
}

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator rotate(
    _ForwardIterator __first, _ForwardIterator __middle, _ForwardIterator __last)
{
    if (__first == __middle) {
        return __last;
    }
    if (__middle == __last) {
        return __first;
    }
    _ForwardIterator __next = __first;
    if (++__next == __middle) {
        return ::asc::std::__rotate_left(__first, __last);
    }
    __next = __middle;
    if (++__next == __last) {
        return ::asc::std::__rotate_right(__first, __middle);
    }
    return ::asc::std::__rotate_forward(__first, __middle, __last);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_ROTATE_H
