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
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/partial_sort.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__bit/countl.h>
#include <asc/std/__bit/countr.h>
#include <asc/std/__bit/integral.h>
#include <asc/std/__functional/operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __sort_detail {

// Minimal local contiguous-traversal probes: the dual category/concept probes
// are SFINAE-friendly under C++17; the pointer specialization is always
// contiguous. Used by the __use_branchless_sort predicate.
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
inline constexpr bool __has_contiguous_traversal =
    __has_iterator_category_convertible_to<Iter, contiguous_iterator_tag> ||
    __has_iterator_concept_convertible_to<Iter, contiguous_iterator_tag>;

template <class Tp>
inline constexpr bool __has_contiguous_traversal<Tp*> = true;

// Block size used by the bitset partition, i.e. the number of bits in uint64_t.
enum { __block_size = sizeof(uint64_t) * 8 };

}  // namespace __sort_detail

// stable, 2-3 compares, 0-2 swaps
template <class _AlgPolicy, class _Compare, class _ForwardIterator>
CANN_ASC_STL_API constexpr unsigned __sort3(
    _ForwardIterator __x, _ForwardIterator __y, _ForwardIterator __z, _Compare __c)
{
    using _Ops = _AlgPolicy;

    unsigned __r = 0;
    if (!__c(*__y, *__x)) {      // if x <= y
        if (!__c(*__z, *__y)) {  // if y <= z
            return __r;          // x <= y && y <= z
        }
        // x <= y && y > z
        _Ops::iter_swap(__y, __z);  // x <= z && y < z
        __r = 1;
        if (__c(*__y, *__x)) {          // if x > y
            _Ops::iter_swap(__x, __y);  // x < y && y <= z
            __r = 2;
        }
        return __r;  // x <= y && y < z
    }
    if (__c(*__z, *__y)) {          // x > y, if y > z
        _Ops::iter_swap(__x, __z);  // x < y && y < z
        __r = 1;
        return __r;
    }
    _Ops::iter_swap(__x, __y);      // x > y && y <= z
    __r = 1;                        // x < y && x <= z
    if (__c(*__z, *__y)) {          // if y > z
        _Ops::iter_swap(__y, __z);  // x <= y && y < z
        __r = 2;
    }
    return __r;
}  // x <= y && y <= z

// stable, 3-6 compares, 0-5 swaps
template <class _AlgPolicy, class _Compare, class _ForwardIterator>
CANN_ASC_STL_API constexpr void __sort4(
    _ForwardIterator __x1, _ForwardIterator __x2, _ForwardIterator __x3, _ForwardIterator __x4, _Compare __c)
{
    ::asc::std::__sort3<_AlgPolicy, _Compare>(__x1, __x2, __x3, __c);
    if (__c(*__x4, *__x3)) {
        _AlgPolicy::iter_swap(__x3, __x4);
        if (__c(*__x3, *__x2)) {
            _AlgPolicy::iter_swap(__x2, __x3);
            if (__c(*__x2, *__x1)) {
                _AlgPolicy::iter_swap(__x1, __x2);
            }
        }
    }
}

// stable, 4-10 compares, 0-9 swaps
template <class _AlgPolicy, class _Comp, class _ForwardIterator>
CANN_ASC_STL_API constexpr void __sort5(_ForwardIterator __x1, _ForwardIterator __x2, _ForwardIterator __x3,
    _ForwardIterator __x4, _ForwardIterator __x5, _Comp __comp)
{
    ::asc::std::__sort4<_AlgPolicy, _Comp>(__x1, __x2, __x3, __x4, __comp);
    if (__comp(*__x5, *__x4)) {
        _AlgPolicy::iter_swap(__x4, __x5);
        if (__comp(*__x4, *__x3)) {
            _AlgPolicy::iter_swap(__x3, __x4);
            if (__comp(*__x3, *__x2)) {
                _AlgPolicy::iter_swap(__x2, __x3);
                if (__comp(*__x2, *__x1)) {
                    _AlgPolicy::iter_swap(__x1, __x2);
                }
            }
        }
    }
}

// A sufficiently simple comparator (stateless and directly forwarding to a
// built-in comparison) is a prerequisite for the branchless sort optimization.
template <class _Tp>
inline constexpr bool __is_simple_comparator = false;

template <>
inline constexpr bool __is_simple_comparator<__less&> = true;

template <class _Tp>
inline constexpr bool __is_simple_comparator<less<_Tp>&> = true;

template <class _Tp>
inline constexpr bool __is_simple_comparator<greater<_Tp>&> = true;

template <class _Compare, class _Iter, class _Tp = typename iterator_traits<_Iter>::value_type>
inline constexpr bool __use_branchless_sort = __sort_detail::__has_contiguous_traversal<_Iter> &&
    sizeof(_Tp) <= sizeof(void*) && is_arithmetic_v<_Tp> && __is_simple_comparator<_Compare>;

// Ensure __c(*__x, *__y) is true, swapping *__x and *__y if necessary.
template <class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __cond_swap(_RandomAccessIterator __x, _RandomAccessIterator __y, _Compare __c)
{
    // Note: this function relies on value_type rather than the dereferenced
    // type, so it is also correct for proxy iterators.
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    bool __r = __c(*__x, *__y);
    value_type __tmp = __r ? *__x : *__y;
    *__y = __r ? *__y : *__x;
    *__x = __tmp;
}

// Sort *__x, *__y, *__z with respect to __c, given that *__y and *__z are
// already in order.
template <class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __partially_sorted_swap(
    _RandomAccessIterator __x, _RandomAccessIterator __y, _RandomAccessIterator __z, _Compare __c)
{
    // Note: this function relies on value_type rather than the dereferenced
    // type, so it is also correct for proxy iterators.
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    bool __r = __c(*__z, *__x);
    value_type __tmp = __r ? *__z : *__x;
    *__z = __r ? *__x : *__z;
    __r = __c(__tmp, *__y);
    *__x = __r ? *__x : *__y;
    *__y = __r ? *__y : __tmp;
}

template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __sort3_maybe_branchless(
    _RandomAccessIterator __x1, _RandomAccessIterator __x2, _RandomAccessIterator __x3, _Compare __c)
{
    if constexpr (__use_branchless_sort<_Compare, _RandomAccessIterator>) {
        ::asc::std::__cond_swap<_Compare>(__x2, __x3, __c);
        ::asc::std::__partially_sorted_swap<_Compare>(__x1, __x2, __x3, __c);
    } else {
        ::asc::std::__sort3<_AlgPolicy, _Compare>(__x1, __x2, __x3, __c);
    }
}

template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __sort4_maybe_branchless(_RandomAccessIterator __x1, _RandomAccessIterator __x2,
    _RandomAccessIterator __x3, _RandomAccessIterator __x4, _Compare __c)
{
    if constexpr (__use_branchless_sort<_Compare, _RandomAccessIterator>) {
        ::asc::std::__cond_swap<_Compare>(__x1, __x3, __c);
        ::asc::std::__cond_swap<_Compare>(__x2, __x4, __c);
        ::asc::std::__cond_swap<_Compare>(__x1, __x2, __c);
        ::asc::std::__cond_swap<_Compare>(__x3, __x4, __c);
        ::asc::std::__cond_swap<_Compare>(__x2, __x3, __c);
    } else {
        ::asc::std::__sort4<_AlgPolicy, _Compare>(__x1, __x2, __x3, __x4, __c);
    }
}

template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __sort5_maybe_branchless(_RandomAccessIterator __x1, _RandomAccessIterator __x2,
    _RandomAccessIterator __x3, _RandomAccessIterator __x4, _RandomAccessIterator __x5, _Compare __c)
{
    if constexpr (__use_branchless_sort<_Compare, _RandomAccessIterator>) {
        ::asc::std::__cond_swap<_Compare>(__x1, __x2, __c);
        ::asc::std::__cond_swap<_Compare>(__x4, __x5, __c);
        ::asc::std::__partially_sorted_swap<_Compare>(__x3, __x4, __x5, __c);
        ::asc::std::__cond_swap<_Compare>(__x2, __x5, __c);
        ::asc::std::__partially_sorted_swap<_Compare>(__x1, __x3, __x4, __c);
        ::asc::std::__partially_sorted_swap<_Compare>(__x2, __x3, __x4, __c);
    } else {
        ::asc::std::__sort5<_AlgPolicy, _Compare, _RandomAccessIterator>(::asc::std::move(__x1), ::asc::std::move(__x2),
            ::asc::std::move(__x3), ::asc::std::move(__x4), ::asc::std::move(__x5), __c);
    }
}

// Sort the range [__first, __last) with the comparator __comp using insertion
// sort.
template <class _AlgPolicy, class _Compare, class _BidirectionalIterator>
CANN_ASC_STL_API constexpr void __insertion_sort(
    _BidirectionalIterator __first, _BidirectionalIterator __last, _Compare __comp)
{
    using _Ops = _AlgPolicy;

    using value_type = typename iterator_traits<_BidirectionalIterator>::value_type;
    if (__first == __last) {
        return;
    }
    _BidirectionalIterator __i = __first;
    for (++__i; __i != __last; ++__i) {
        _BidirectionalIterator __j = __i;
        --__j;
        if (__comp(*__i, *__j)) {
            value_type __t(_Ops::iter_move(__i));
            _BidirectionalIterator __k = __j;
            __j = __i;
            do {
                *__j = _Ops::iter_move(__k);
                __j = __k;
            } while (__j != __first && __comp(__t, *--__k));
            *__j = ::asc::std::move(__t);
        }
    }
}

// Sort the range [__first, __last) with the comparator __comp using insertion
// sort. Unlike the version above, the inner loop performs no bounds check
// (unguarded): it assumes an element exists at (__first - 1) and that every
// element in the input range is not less than the element at __first - 1.
template <class _AlgPolicy, class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __insertion_sort_unguarded(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    if (__first == __last) {
        return;
    }
    const _RandomAccessIterator __leftmost = __first - difference_type(1);
    (void)__leftmost;  // avoid an unused-variable warning when assertions are off
    for (_RandomAccessIterator __i = __first + difference_type(1); __i != __last; ++__i) {
        _RandomAccessIterator __j = __i - difference_type(1);
        if (__comp(*__i, *__j)) {
            value_type __t(_Ops::iter_move(__i));
            _RandomAccessIterator __k = __j;
            __j = __i;
            do {
                *__j = _Ops::iter_move(__k);
                __j = __k;
                CANN_ASC_STL_DETAIL_ASSERT(__k != __leftmost,
                    "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
            } while (__comp(__t, *--__k));  // no bounds check needed due to the assumption above
            *__j = ::asc::std::move(__t);
        }
    }
}

template <class _AlgPolicy, class _Comp, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr bool __insertion_sort_incomplete(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Comp __comp)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    switch (__last - __first) {
        case 0:
        case 1:
            return true;
        case 2:
            if (__comp(*--__last, *__first)) {
                _Ops::iter_swap(__first, __last);
            }
            return true;
        case 3:
            ::asc::std::__sort3_maybe_branchless<_AlgPolicy, _Comp>(
                __first, __first + difference_type(1), --__last, __comp);
            return true;
        case 4:
            ::asc::std::__sort4_maybe_branchless<_AlgPolicy, _Comp>(
                __first, __first + difference_type(1), __first + difference_type(2), --__last, __comp);
            return true;
        case 5:
            ::asc::std::__sort5_maybe_branchless<_AlgPolicy, _Comp>(__first, __first + difference_type(1),
                __first + difference_type(2), __first + difference_type(3), --__last, __comp);
            return true;
        default:
            break;
    }
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    _RandomAccessIterator __j = __first + difference_type(2);
    ::asc::std::__sort3_maybe_branchless<_AlgPolicy, _Comp>(__first, __first + difference_type(1), __j, __comp);
    const unsigned __limit = 8;
    unsigned __count = 0;
    for (_RandomAccessIterator __i = __j + difference_type(1); __i != __last; ++__i) {
        if (__comp(*__i, *__j)) {
            value_type __t(_Ops::iter_move(__i));
            _RandomAccessIterator __k = __j;
            __j = __i;
            do {
                *__j = _Ops::iter_move(__k);
                __j = __k;
            } while (__j != __first && __comp(__t, *--__k));
            *__j = ::asc::std::move(__t);
            if (++__count == __limit) {
                return ++__i == __last;
            }
        }
        __j = __i;
    }
    return true;
}

// Keep swapping in pairs while each side's bitset still has at least one
// element to swap.
template <class _AlgPolicy, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __swap_bitmap_pos(
    _RandomAccessIterator __first, _RandomAccessIterator __last, uint64_t& __left_bitset, uint64_t& __right_bitset)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    while (__left_bitset != 0 && __right_bitset != 0) {
        difference_type __tz_left = ::asc::std::countr_zero(__left_bitset);
        __left_bitset &= __left_bitset - 1;  // clear the lowest set bit (blsr semantics)
        difference_type __tz_right = ::asc::std::countr_zero(__right_bitset);
        __right_bitset &= __right_bitset - 1;
        _Ops::iter_swap(__first + __tz_left, __last - __tz_right);
    }
}

// Record the comparison results of the left-side elements against the pivot.
// With suitable compiler options this loop can be vectorized.
template <class _Compare, class _RandomAccessIterator,
    class _ValueType = typename iterator_traits<_RandomAccessIterator>::value_type>
CANN_ASC_STL_API constexpr void __populate_left_bitset(
    _RandomAccessIterator __first, _Compare __comp, _ValueType& __pivot, uint64_t& __left_bitset)
{
    _RandomAccessIterator __iter = __first;
    for (int __j = 0; __j < __sort_detail::__block_size;) {
        bool __comp_result = !__comp(*__iter, __pivot);
        __left_bitset |= (static_cast<uint64_t>(__comp_result) << __j);
        __j++;
        ++__iter;
    }
}

// Record the comparison results of the right-side elements against the pivot.
// With suitable compiler options this loop can be vectorized.
template <class _Compare, class _RandomAccessIterator,
    class _ValueType = typename iterator_traits<_RandomAccessIterator>::value_type>
CANN_ASC_STL_API constexpr void __populate_right_bitset(
    _RandomAccessIterator __lm1, _Compare __comp, _ValueType& __pivot, uint64_t& __right_bitset)
{
    _RandomAccessIterator __iter = __lm1;
    for (int __j = 0; __j < __sort_detail::__block_size;) {
        bool __comp_result = __comp(*__iter, __pivot);
        __right_bitset |= (static_cast<uint64_t>(__comp_result) << __j);
        __j++;
        --__iter;
    }
}

template <class _AlgPolicy, class _Compare, class _RandomAccessIterator,
    class _ValueType = typename iterator_traits<_RandomAccessIterator>::value_type>
CANN_ASC_STL_API constexpr void __bitset_partition_partial_blocks(_RandomAccessIterator& __first,
    _RandomAccessIterator& __lm1, _Compare __comp, _ValueType& __pivot, uint64_t& __left_bitset,
    uint64_t& __right_bitset)
{
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    difference_type __remaining_len = __lm1 - __first + 1;
    difference_type __l_size;
    difference_type __r_size;
    if (__left_bitset == 0 && __right_bitset == 0) {
        __l_size = __remaining_len / 2;
        __r_size = __remaining_len - __l_size;
    } else if (__left_bitset == 0) {
        // At least one side is a full block.
        __l_size = __remaining_len - __sort_detail::__block_size;
        __r_size = __sort_detail::__block_size;
    } else {  // if (__right_bitset == 0)
        __l_size = __sort_detail::__block_size;
        __r_size = __remaining_len - __sort_detail::__block_size;
    }
    // Record the comparison results of the elements currently on the left side.
    if (__left_bitset == 0) {
        _RandomAccessIterator __iter = __first;
        for (int __j = 0; __j < __l_size; __j++) {
            bool __comp_result = !__comp(*__iter, __pivot);
            __left_bitset |= (static_cast<uint64_t>(__comp_result) << __j);
            ++__iter;
        }
    }
    // Record the comparison results of the elements currently on the right side.
    if (__right_bitset == 0) {
        _RandomAccessIterator __iter = __lm1;
        for (int __j = 0; __j < __r_size; __j++) {
            bool __comp_result = __comp(*__iter, __pivot);
            __right_bitset |= (static_cast<uint64_t>(__comp_result) << __j);
            --__iter;
        }
    }
    ::asc::std::__swap_bitmap_pos<_AlgPolicy, _RandomAccessIterator>(__first, __lm1, __left_bitset, __right_bitset);
    __first += (__left_bitset == 0) ? __l_size : 0;
    __lm1 -= (__right_bitset == 0) ? __r_size : 0;
}

// At least one bitset is empty; complete the same-side gathering swaps for the
// elements still on the wrong side in the non-empty bitset.
template <class _AlgPolicy, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __swap_bitmap_pos_within(
    _RandomAccessIterator& __first, _RandomAccessIterator& __lm1, uint64_t& __left_bitset, uint64_t& __right_bitset)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    if (__left_bitset) {
        // Swaps within the left side: set-bit positions must be processed in
        // reverse order.
        while (__left_bitset != 0) {
            difference_type __tz_left = __sort_detail::__block_size - 1 - ::asc::std::countl_zero(__left_bitset);
            __left_bitset &= (static_cast<uint64_t>(1) << __tz_left) - 1;
            _RandomAccessIterator __it = __first + __tz_left;
            if (__it != __lm1) {
                _Ops::iter_swap(__it, __lm1);
            }
            --__lm1;
        }
        __first = __lm1 + difference_type(1);
    } else if (__right_bitset) {
        // Swaps within the right side: set-bit positions must be processed in
        // reverse order.
        while (__right_bitset != 0) {
            difference_type __tz_right = __sort_detail::__block_size - 1 - ::asc::std::countl_zero(__right_bitset);
            __right_bitset &= (static_cast<uint64_t>(1) << __tz_right) - 1;
            _RandomAccessIterator __it = __lm1 - __tz_right;
            if (__it != __first) {
                _Ops::iter_swap(__it, __first);
            }
            ++__first;
        }
    }
}

// Partition the range [__first, __last) with the comparator __comp; the pivot
// is already in *__first. Elements equivalent to the pivot are kept on its
// left. Returns the pivot's new position and a bool (true when the input range
// was already partitioned). Assumes the range has length at least three.
// __bitset_partition records each element's comparison result against the pivot
// in bitsets.
template <class _AlgPolicy, class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr ::asc::std::pair<_RandomAccessIterator, bool> __bitset_partition(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    using _Ops = _AlgPolicy;
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    CANN_ASC_STL_DETAIL_ASSERT(__last - __first >= difference_type(3), "");
    const _RandomAccessIterator __begin = __first;  // used only for bounds checks, never moved
    const _RandomAccessIterator __end = __last;
    (void)__end;

    value_type __pivot(_Ops::iter_move(__first));
    // Find the first element greater than the pivot.
    if (__comp(__pivot, *(__last - difference_type(1)))) {
        // The last element is known to be greater than the pivot, so this
        // search needs no guard.
        do {
            ++__first;
            CANN_ASC_STL_DETAIL_ASSERT(__first != __end,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
        } while (!__comp(__pivot, *__first));
    } else {
        while (++__first < __last && !__comp(__pivot, *__first)) {
        }
    }
    // Find the last element less than or equal to the pivot.
    if (__first < __last) {
        // __introsort always takes a three-value sample before calling this
        // function, so this search is guaranteed a guard.
        do {
            CANN_ASC_STL_DETAIL_ASSERT(__last != __begin,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
            --__last;
        } while (__comp(__pivot, *__last));
    }
    // If the first element greater than the pivot passes (or coincides with)
    // the last element less than or equal to it, the whole range was covered
    // without a single swap, i.e. the range is already partitioned.
    bool __already_partitioned = __first >= __last;
    if (!__already_partitioned) {
        _Ops::iter_swap(__first, __last);
        ++__first;
    }

    // Below, __last is the exclusive end of [__first, __last); both sides
    // switch to the decremented closed-interval end point.
    _RandomAccessIterator __lm1 = __last - difference_type(1);
    uint64_t __left_bitset = 0;
    uint64_t __right_bitset = 0;

    // Note: length = __lm1 - __first + 1.
    while (__lm1 - __first >= 2 * __sort_detail::__block_size - 1) {
        // Record the comparison results of the current left-side elements.
        if (__left_bitset == 0) {
            ::asc::std::__populate_left_bitset<_Compare>(__first, __comp, __pivot, __left_bitset);
        }
        // Record the comparison results of the current right-side elements.
        if (__right_bitset == 0) {
            ::asc::std::__populate_right_bitset<_Compare>(__lm1, __comp, __pivot, __right_bitset);
        }
        // Swap the elements recorded as pending in the two bitsets.
        ::asc::std::__swap_bitmap_pos<_AlgPolicy, _RandomAccessIterator>(__first, __lm1, __left_bitset, __right_bitset);
        // Advance a side's cursor only once every element that must move on
        // that side has been moved.
        __first += (__left_bitset == 0) ? difference_type(__sort_detail::__block_size) : difference_type(0);
        __lm1 -= (__right_bitset == 0) ? difference_type(__sort_detail::__block_size) : difference_type(0);
    }
    // At this point at least one side has fewer than a full block remaining.
    ::asc::std::__bitset_partition_partial_blocks<_AlgPolicy, _Compare>(
        __first, __lm1, __comp, __pivot, __left_bitset, __right_bitset);
    // At least one bitset is empty; finish partitioning the elements in the
    // non-empty bitset correctly.
    ::asc::std::__swap_bitmap_pos_within<_AlgPolicy>(__first, __lm1, __left_bitset, __right_bitset);

    // Move the pivot to its final position.
    _RandomAccessIterator __pivot_pos = __first - difference_type(1);
    if (__begin != __pivot_pos) {
        *__begin = _Ops::iter_move(__pivot_pos);
    }
    *__pivot_pos = ::asc::std::move(__pivot);
    return ::asc::std::make_pair(__pivot_pos, __already_partitioned);
}

// Partition the range [__first, __last) with the comparator __comp; the pivot
// is already in *__first. Elements equivalent to the pivot are kept on its
// right. Same return meaning as above; the range has length at least three.
template <class _AlgPolicy, class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr ::asc::std::pair<_RandomAccessIterator, bool> __partition_with_equals_on_right(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    CANN_ASC_STL_DETAIL_ASSERT(__last - __first >= difference_type(3), "");
    const _RandomAccessIterator __begin = __first;  // used only for bounds checks, never moved
    const _RandomAccessIterator __end = __last;
    (void)__end;
    value_type __pivot(_Ops::iter_move(__first));
    // Find the first element greater than or equal to the pivot. __introsort
    // always takes a three-value sample before calling, so this search is
    // guaranteed a guard.
    do {
        ++__first;
        CANN_ASC_STL_DETAIL_ASSERT(__first != __end,
            "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
    } while (__comp(*__first, __pivot));

    // Find the last element less than the pivot.
    if (__begin == __first - difference_type(1)) {
        while (__first < __last && !__comp(*--__last, __pivot)) {
        }
    } else {
        // Has a guard.
        do {
            CANN_ASC_STL_DETAIL_ASSERT(__last != __begin,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
            --__last;
        } while (!__comp(*__last, __pivot));
    }

    // If the first element greater than or equal to the pivot passes (or
    // coincides with) the last element less than it, the whole range was
    // covered without a single swap, i.e. the range is already partitioned.
    bool __already_partitioned = __first >= __last;
    // Handle the remaining elements: swap in pairs the elements on the wrong
    // side of the pivot.
    while (__first < __last) {
        _Ops::iter_swap(__first, __last);
        do {
            ++__first;
            CANN_ASC_STL_DETAIL_ASSERT(__first != __end,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
        } while (__comp(*__first, __pivot));
        do {
            CANN_ASC_STL_DETAIL_ASSERT(__last != __begin,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
            --__last;
        } while (!__comp(*__last, __pivot));
    }
    // Move the pivot to its final position.
    _RandomAccessIterator __pivot_pos = __first - difference_type(1);
    if (__begin != __pivot_pos) {
        *__begin = _Ops::iter_move(__pivot_pos);
    }
    *__pivot_pos = ::asc::std::move(__pivot);
    return ::asc::std::make_pair(__pivot_pos, __already_partitioned);
}

// Similar to the previous function, but elements equivalent to the pivot are
// placed on its left. Returns the pivot's new position.
template <class _AlgPolicy, class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr _RandomAccessIterator __partition_with_equals_on_left(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    const _RandomAccessIterator __begin = __first;  // used only for bounds checks, never moved
    const _RandomAccessIterator __end = __last;
    (void)__end;
    value_type __pivot(_Ops::iter_move(__first));
    if (__comp(__pivot, *(__last - difference_type(1)))) {
        // Has a guard.
        do {
            ++__first;
            CANN_ASC_STL_DETAIL_ASSERT(__first != __end,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
        } while (!__comp(__pivot, *__first));
    } else {
        while (++__first < __last && !__comp(__pivot, *__first)) {
        }
    }

    if (__first < __last) {
        // __introsort always takes a three-value sample before calling, so this
        // search is guaranteed a guard.
        do {
            CANN_ASC_STL_DETAIL_ASSERT(__last != __begin,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
            --__last;
        } while (__comp(__pivot, *__last));
    }
    while (__first < __last) {
        _Ops::iter_swap(__first, __last);
        do {
            ++__first;
            CANN_ASC_STL_DETAIL_ASSERT(__first != __end,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
        } while (!__comp(__pivot, *__first));
        do {
            CANN_ASC_STL_DETAIL_ASSERT(__last != __begin,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
            --__last;
        } while (__comp(__pivot, *__last));
    }
    _RandomAccessIterator __pivot_pos = __first - difference_type(1);
    if (__begin != __pivot_pos) {
        *__begin = _Ops::iter_move(__pivot_pos);
    }
    *__pivot_pos = ::asc::std::move(__pivot);
    return __first;
}

// Main sort function. Implements introsort combined with the following
// techniques:
//  - optional bitset quicksort partitioning (block quicksort partitioning),
//  - guarded/unguarded insertion sort for small lengths,
//  - Tukey ninther pivot selection,
//  - fast detection of whether the partition was already ordered.
// The implementation is partly based on Orson Peters' pattern-defeating
// quicksort: <https://github.com/orlp/pdqsort>.
template <class _AlgPolicy, class _Compare, class _RandomAccessIterator, bool _UseBitSetPartition>
CANN_ASC_STL_API constexpr void __introsort(_RandomAccessIterator __first, _RandomAccessIterator __last,
    _Compare __comp, typename iterator_traits<_RandomAccessIterator>::difference_type __depth, bool __leftmost = true)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using _Comp_ref = __comp_ref_type<_Compare>;
    // Upper length bound for switching to insertion sort.
    constexpr difference_type __limit = 24;
    // Lower length bound for enabling the Tukey ninther median technique.
    constexpr difference_type __ninther_threshold = 128;
    while (true) {
        difference_type __len = __last - __first;
        switch (__len) {
            case 0:
            case 1:
                return;
            case 2:
                if (__comp(*--__last, *__first)) {
                    _Ops::iter_swap(__first, __last);
                }
                return;
            case 3:
                ::asc::std::__sort3_maybe_branchless<_AlgPolicy, _Compare>(
                    __first, __first + difference_type(1), --__last, __comp);
                return;
            case 4:
                ::asc::std::__sort4_maybe_branchless<_AlgPolicy, _Compare>(
                    __first, __first + difference_type(1), __first + difference_type(2), --__last, __comp);
                return;
            case 5:
                ::asc::std::__sort5_maybe_branchless<_AlgPolicy, _Compare>(__first, __first + difference_type(1),
                    __first + difference_type(2), __first + difference_type(3), --__last, __comp);
                return;
            default:
                break;
        }
        // Below the threshold length, switch to insertion sort.
        if (__len < __limit) {
            if (__leftmost) {
                ::asc::std::__insertion_sort<_AlgPolicy, _Compare>(__first, __last, __comp);
            } else {
                ::asc::std::__insertion_sort_unguarded<_AlgPolicy, _Compare>(__first, __last, __comp);
            }
            return;
        }
        if (__depth == 0) {
            // Following the introsort idea, degenerate to heapsort
            // (__partial_sort with last as middle sorts the whole range).
            ::asc::std::__partial_sort<_AlgPolicy, _Compare>(__first, __last, __last, __comp);
            return;
        }
        --__depth;
        {
            difference_type __half_len = __len / 2;
            // Choose the pivot via Tukey ninther or three-value sampling
            // depending on the range length.
            if (__len > __ninther_threshold) {
                ::asc::std::__sort3<_AlgPolicy, _Compare>(
                    __first, __first + __half_len, __last - difference_type(1), __comp);
                ::asc::std::__sort3<_AlgPolicy, _Compare>(
                    __first + difference_type(1), __first + (__half_len - 1), __last - difference_type(2), __comp);
                ::asc::std::__sort3<_AlgPolicy, _Compare>(
                    __first + difference_type(2), __first + (__half_len + 1), __last - difference_type(3), __comp);
                ::asc::std::__sort3<_AlgPolicy, _Compare>(
                    __first + (__half_len - 1), __first + __half_len, __first + (__half_len + 1), __comp);
                _Ops::iter_swap(__first, __first + __half_len);
            } else {
                ::asc::std::__sort3<_AlgPolicy, _Compare>(
                    __first + __half_len, __first, __last - difference_type(1), __comp);
            }
        }
        // The elements to the left of the current range are already sorted. If
        // the current range is not the leftmost segment of the whole range being
        // sorted and the pivot is equivalent to the largest element of that
        // sorted left segment, then under the "equivalents on the left"
        // partition convention every element in [first, pivot] is equivalent to
        // the pivot, so the left side needs no further sorting.
        if (!__leftmost && !__comp(*(__first - difference_type(1)), *__first)) {
            __first = ::asc::std::__partition_with_equals_on_left<_AlgPolicy, _RandomAccessIterator, _Comp_ref>(
                __first, __last, _Comp_ref(__comp));
            continue;
        }
        // Use bitset partitioning only when explicitly requested.
        auto __ret = _UseBitSetPartition ?
            ::asc::std::__bitset_partition<_AlgPolicy, _RandomAccessIterator, _Compare>(__first, __last, __comp) :
            ::asc::std::__partition_with_equals_on_right<_AlgPolicy, _RandomAccessIterator, _Compare>(
                __first, __last, __comp);
        _RandomAccessIterator __i = __ret.first;
        // [__first, __i) < *__i and *__i <= [__i+1, __last)
        // If the partition came out perfect, see whether insertion sort is
        // faster...
        if (__ret.second) {
            bool __fs = ::asc::std::__insertion_sort_incomplete<_AlgPolicy, _Compare>(__first, __i, __comp);
            if (::asc::std::__insertion_sort_incomplete<_AlgPolicy, _Compare>(
                    __i + difference_type(1), __last, __comp)) {
                if (__fs) {
                    return;
                }
                __last = __i;
                continue;
            }
            if (__fs) {
                __first = ++__i;
                continue;
            }
        }
        // Sort the left half recursively; process the right half iteratively
        // by eliminating tail recursion.
        ::asc::std::__introsort<_AlgPolicy, _Compare, _RandomAccessIterator, _UseBitSetPartition>(
            __first, __i, __comp, __depth, __leftmost);
        __leftmost = false;
        __first = ++__i;
    }
}

template <class _AlgPolicy, class _Comp, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Comp __comp)
{
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    difference_type __depth_limit = 2 * ::asc::std::__bit_log2(static_cast<uint64_t>(__last - __first));

    // Enable bitset partitioning only for arithmetic types, and require the
    // default comparator so the comparison process stays branchless.
    ::asc::std::__introsort<_AlgPolicy, _Comp, _RandomAccessIterator,
        __use_branchless_sort<_Comp, _RandomAccessIterator>>(__first, __last, __comp, __depth_limit);
}

template <class _AlgPolicy, class _RandomAccessIterator, class _Comp>
CANN_ASC_STL_API constexpr void __sort_dispatch(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Comp& __comp)
{
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    difference_type __depth_limit = 2 * ::asc::std::__bit_log2(static_cast<uint64_t>(__last - __first));

    // Enable bitset partitioning only for arithmetic types, and require the
    // default comparator so the comparison process stays branchless.
    ::asc::std::__introsort<_AlgPolicy, _Comp&, _RandomAccessIterator,
        __use_branchless_sort<_Comp, _RandomAccessIterator>>(__first, __last, __comp, __depth_limit);
}

template <class _Type, class... _Options>
using __is_any_of = _Or<is_same<_Type, _Options>...>;

template <class _Type>
using __sort_is_specialized_in_library = __is_any_of<_Type, char, wchar_t, signed char, unsigned char, short,
    unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long, float, double, long double>;

// Bare pointers to arithmetic types already specialized in the library, plus a
// simple comparator: take the fast path with the comparator by reference and
// branchless bitset dispatch enabled.
template <class _AlgPolicy, class _Type, enable_if_t<__sort_is_specialized_in_library<_Type>::value, int> = 0>
CANN_ASC_STL_API constexpr void __sort_dispatch(_Type* __first, _Type* __last, __less& __comp)
{
    ::asc::std::__sort<_AlgPolicy, __less&, _Type*>(__first, __last, __comp);
}

template <class _AlgPolicy, class _Type, enable_if_t<__sort_is_specialized_in_library<_Type>::value, int> = 0>
CANN_ASC_STL_API constexpr void __sort_dispatch(_Type* __first, _Type* __last, less<_Type>& __comp)
{
    (void)__comp;
    __less __simple_comp{};
    ::asc::std::__sort<_AlgPolicy, __less&, _Type*>(__first, __last, __simple_comp);
}

template <class _AlgPolicy, class _Type, enable_if_t<__sort_is_specialized_in_library<_Type>::value, int> = 0>
CANN_ASC_STL_API constexpr void __sort_dispatch(_Type* __first,  // NOLINT(build/include_what_you_use)
    _Type* __last, less<>& __comp)                               // NOLINT(build/include_what_you_use)
{
    (void)__comp;
    __less __simple_comp{};
    ::asc::std::__sort<_AlgPolicy, __less&, _Type*>(__first, __last, __simple_comp);
}

template <class _AlgPolicy, class _RandomAccessIterator, class _Comp>
CANN_ASC_STL_API constexpr void __sort_impl(_RandomAccessIterator __first, _RandomAccessIterator __last, _Comp& __comp)
{
    if (::asc::std::is_constant_evaluated()) {
        // Constant evaluation falls back to heapsort: introsort's unguarded
        // insertion sort and partition loops rely on partition invariants whose
        // safety constant evaluation's out-of-bounds diagnostics cannot prove.
        ::asc::std::__partial_sort<_AlgPolicy>(::asc::std::__unwrap_iter(__first), ::asc::std::__unwrap_iter(__last),
            ::asc::std::__unwrap_iter(__last), __comp);
    } else {
        ::asc::std::__sort_dispatch<_AlgPolicy>(
            ::asc::std::__unwrap_iter(__first), ::asc::std::__unwrap_iter(__last), __comp);
    }
}

template <class RandomAccessIterator, class Compare>
CANN_ASC_STL_API constexpr void sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare)
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // Recursive calls are forbidden on the AI Core: the device side uses an
    // iterative in-place heapsort (no allocation, no recursion, preserving the
    // O(N log N) comparison bound); the host side takes the introsort fast
    // path.
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
#else
    ::asc::std::__sort_impl<__classic_algorithm_iterator_operations>(
        ::asc::std::move(first), ::asc::std::move(last), compare);  // NOLINT(build/include_what_you_use)
#endif
}

template <class RandomAccessIterator>
CANN_ASC_STL_API constexpr void sort(RandomAccessIterator first, RandomAccessIterator last)
{
    ::asc::std::sort(first, last, __less{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SORT_H
