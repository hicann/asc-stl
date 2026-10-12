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
#include <asc/std/__iterator/next.h>
#include <asc/std/__type_traits/is_trivially_move_assignable.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _AlgPolicy, class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __rotate_left(_ForwardIterator __first, _ForwardIterator __last)
{
    // Moves the leading element to the back of the range and returns the new
    // last position; valid when the rotated prefix is exactly one element.
    using value_type = typename iterator_traits<_ForwardIterator>::value_type;

    value_type __tmp = _AlgPolicy::iter_move(__first);
    _ForwardIterator __lm1 = ::asc::std::move(::asc::std::next(__first), __last, __first);
    *__lm1 = ::asc::std::move(__tmp);  // NOLINT(build/include_what_you_use)
    return __lm1;
}

template <class _AlgPolicy, class _BidirectionalIterator>
CANN_ASC_STL_API constexpr _BidirectionalIterator __rotate_right(
    _BidirectionalIterator __first, _BidirectionalIterator __last)
{
    // Rotates the trailing element to the front of the range and returns the
    // new first position; valid when the rotated suffix is one element.
    using value_type = typename iterator_traits<_BidirectionalIterator>::value_type;

    _BidirectionalIterator __lm1 = __last;
    --__lm1;
    value_type __tmp = _AlgPolicy::iter_move(__lm1);
    _BidirectionalIterator __fp1 = ::asc::std::move_backward(__first, __lm1, __last);
    *__first = ::asc::std::move(__tmp);  // NOLINT(build/include_what_you_use)
    return __fp1;
}

template <class _AlgPolicy, class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __rotate_forward(
    _ForwardIterator __first, _ForwardIterator __middle, _ForwardIterator __last)
{
    // Universal swap-loop rotation for forward iterators; also correct for
    // bidirectional and random-access iterators.
    _ForwardIterator __i = __middle;
    while (true) {
        _AlgPolicy::iter_swap(__first, __i);
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
            _AlgPolicy::iter_swap(__first, __i);
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

template <typename _Integral>
CANN_ASC_STL_API constexpr _Integral __algo_gcd(_Integral __x, _Integral __y)
{
    while (__y) {
        _Integral __t = __x % __y;
        __x = __y;
        __y = __t;
    }
    return __x;
}

template <class _AlgPolicy, typename _RandomAccessIterator>
CANN_ASC_STL_API constexpr _RandomAccessIterator __rotate_gcd(
    _RandomAccessIterator __first, _RandomAccessIterator __middle, _RandomAccessIterator __last)
{
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;

    const difference_type __m1 = __middle - __first;
    const difference_type __m2 = __last - __middle;
    if (__m1 == __m2) {
        ::asc::std::swap_ranges(__first, __middle, __middle);
        return __middle;
    }
    const difference_type __g = ::asc::std::__algo_gcd(__m1, __m2);
    for (_RandomAccessIterator __p = __first + __g; __p != __first;) {
        value_type __t(_AlgPolicy::iter_move(--__p));
        _RandomAccessIterator __p1 = __p;
        _RandomAccessIterator __p2 = __p1 + __m1;
        do {
            *__p1 = _AlgPolicy::iter_move(__p2);
            __p1 = __p2;
            const difference_type __d = __last - __p2;
            if (__m1 < __d) {
                __p2 += __m1;
            } else {
                __p2 = __first + (__m1 - __d);
            }
        } while (__p2 != __p);
        *__p1 = ::asc::std::move(__t);  // NOLINT(build/include_what_you_use)
    }
    return __first + __m2;
}

template <class _AlgPolicy, class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __rotate_impl(
    _ForwardIterator __first, _ForwardIterator __middle, _ForwardIterator __last, forward_iterator_tag)
{
    using value_type = typename iterator_traits<_ForwardIterator>::value_type;
    if (is_trivially_move_assignable_v<value_type>) {
        if (::asc::std::next(__first) == __middle) {
            return ::asc::std::__rotate_left<_AlgPolicy>(__first, __last);
        }
    }
    return ::asc::std::__rotate_forward<_AlgPolicy>(__first, __middle, __last);
}

template <class _AlgPolicy, class _BidirectionalIterator>
CANN_ASC_STL_API constexpr _BidirectionalIterator __rotate_impl(_BidirectionalIterator __first,
    _BidirectionalIterator __middle, _BidirectionalIterator __last, bidirectional_iterator_tag)
{
    using value_type = typename iterator_traits<_BidirectionalIterator>::value_type;
    if (is_trivially_move_assignable_v<value_type>) {
        if (::asc::std::next(__first) == __middle) {
            return ::asc::std::__rotate_left<_AlgPolicy>(__first, __last);
        }
        if (::asc::std::next(__middle) == __last) {
            return ::asc::std::__rotate_right<_AlgPolicy>(__first, __last);
        }
    }
    return ::asc::std::__rotate_forward<_AlgPolicy>(__first, __middle, __last);
}

template <class _AlgPolicy, typename _RandomAccessIterator>
CANN_ASC_STL_API constexpr _RandomAccessIterator __rotate_impl(_RandomAccessIterator __first,
    _RandomAccessIterator __middle, _RandomAccessIterator __last, random_access_iterator_tag)
{
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    if (is_trivially_move_assignable_v<value_type>) {
        if (::asc::std::next(__first) == __middle) {
            return ::asc::std::__rotate_left<_AlgPolicy>(__first, __last);
        }
        if (::asc::std::next(__middle) == __last) {
            return ::asc::std::__rotate_right<_AlgPolicy>(__first, __last);
        }
        return ::asc::std::__rotate_gcd<_AlgPolicy>(__first, __middle, __last);
    }
    return ::asc::std::__rotate_forward<_AlgPolicy>(__first, __middle, __last);
}

template <class _AlgPolicy, class _Iterator, class _Sentinel>
CANN_ASC_STL_API constexpr pair<_Iterator, _Iterator> __rotate(_Iterator __first, _Iterator __middle, _Sentinel __last)
{
    using _Ret = pair<_Iterator, _Iterator>;
    _Iterator __last_iter = __middle;
    while (__last_iter != __last) {
        ++__last_iter;
    }

    if (__first == __middle) {
        return _Ret(__last_iter, __last_iter);
    }
    if (__middle == __last) {
        return _Ret(::asc::std::move(__first), ::asc::std::move(__last_iter));
    }

    using _IterCategory = typename iterator_traits<_Iterator>::iterator_category;
    auto __result = ::asc::std::__rotate_impl<_AlgPolicy>(
        ::asc::std::move(__first), ::asc::std::move(__middle), __last_iter, _IterCategory());

    return _Ret(::asc::std::move(__result), ::asc::std::move(__last_iter));
}

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator rotate(
    _ForwardIterator __first, _ForwardIterator __middle, _ForwardIterator __last)
{
    return ::asc::std::__rotate<__classic_algorithm_iterator_operations>(
        // NOLINTNEXTLINE(build/include_what_you_use)
        ::asc::std::move(__first), ::asc::std::move(__middle), ::asc::std::move(__last))
        .first;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_ROTATE_H
