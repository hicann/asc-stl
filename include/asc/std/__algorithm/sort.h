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

// 连续遍历探测的最小本地等价（与 unwrap_iter.h 等同款）：category/concept 双探测，
// C++17 下 SFINAE 友好，指针特化恒为连续。供 __use_branchless_sort 判定使用。
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

// 位集分区（bitset partition）使用的块大小，即 uint64_t 的位数。
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

// 比较器足够简单（无状态且直接转发到内建比较）是无分支排序优化的前提。
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

// 保证 __c(*__x, *__y) 为真：必要时交换 *__x 与 *__y。
template <class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __cond_swap(_RandomAccessIterator __x, _RandomAccessIterator __y, _Compare __c)
{
    // 注：本函数依赖 value_type 而非解引用类型，代理迭代器下同样正确。
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    bool __r = __c(*__x, *__y);
    value_type __tmp = __r ? *__x : *__y;
    *__y = __r ? *__y : *__x;
    *__x = __tmp;
}

// 在 *__y 与 *__z 已经有序的前提下，按比较器 __c 将 *__x、*__y、*__z 排为有序。
template <class _Compare, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __partially_sorted_swap(
    _RandomAccessIterator __x, _RandomAccessIterator __y, _RandomAccessIterator __z, _Compare __c)
{
    // 注：本函数依赖 value_type 而非解引用类型，代理迭代器下同样正确。
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

// 使用插入排序算法定义的比较器 __comp 对迭代器区间 [__first, __last) 排序。
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

// 使用插入排序算法定义的比较器 __comp 对迭代器区间 [__first, __last) 排序。
// 与上面的版本相比，本版本的内层循环没有边界检查（无守卫）：假定 (__first - 1)
// 位置存在元素，且输入区间内每个元素都不小于 __first - 1 处的元素。
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
    (void)__leftmost;  // 断言关闭时避免未使用告警
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
            } while (__comp(__t, *--__k));  // 依上述假定无需边界检查
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

// 只要在两侧位集中各剩至少一个待交换元素，就持续按对交换。
template <class _AlgPolicy, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __swap_bitmap_pos(
    _RandomAccessIterator __first, _RandomAccessIterator __last, uint64_t& __left_bitset, uint64_t& __right_bitset)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    while (__left_bitset != 0 && __right_bitset != 0) {
        difference_type __tz_left = ::asc::std::countr_zero(__left_bitset);
        __left_bitset &= __left_bitset - 1;  // 清除最低置位（blsr 语义）
        difference_type __tz_right = ::asc::std::countr_zero(__right_bitset);
        __right_bitset &= __right_bitset - 1;
        _Ops::iter_swap(__first + __tz_left, __last - __tz_right);
    }
}

// 记录左侧元素与 pivot 的比较结果。配合适的编译选项，此循环可被向量化。
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

// 记录右侧元素与 pivot 的比较结果。配合适的编译选项，此循环可被向量化。
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
        // 至少一侧是完整块
        __l_size = __remaining_len - __sort_detail::__block_size;
        __r_size = __sort_detail::__block_size;
    } else {  // if (__right_bitset == 0)
        __l_size = __sort_detail::__block_size;
        __r_size = __remaining_len - __sort_detail::__block_size;
    }
    // 记录当前位于左侧元素的比较结果。
    if (__left_bitset == 0) {
        _RandomAccessIterator __iter = __first;
        for (int __j = 0; __j < __l_size; __j++) {
            bool __comp_result = !__comp(*__iter, __pivot);
            __left_bitset |= (static_cast<uint64_t>(__comp_result) << __j);
            ++__iter;
        }
    }
    // 记录当前位于右侧元素的比较结果。
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

// 至少一个位集已清空；对非空位集内仍处错误一侧的元素完成同侧收拢交换。
template <class _AlgPolicy, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __swap_bitmap_pos_within(
    _RandomAccessIterator& __first, _RandomAccessIterator& __lm1, uint64_t& __left_bitset, uint64_t& __right_bitset)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    if (__left_bitset) {
        // 左侧内部交换：需要按置位位置的逆序处理。
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
        // 右侧内部交换：需要按置位位置的逆序处理。
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

// 用比较器 __comp 对区间 [__first, __last) 做分区；pivot 已置于 *__first。
// 与 pivot 等价的元素保留在 pivot 左侧。返回 pivot 的新位置与一个 bool
// （输入区间本身已分区则为真）。假定区间长度至少为三。
//
// __bitset_partition 用位集记录各元素与 pivot 的比较结果。
template <class _AlgPolicy, class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr ::asc::std::pair<_RandomAccessIterator, bool> __bitset_partition(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    using _Ops = _AlgPolicy;
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    CANN_ASC_STL_DETAIL_ASSERT(__last - __first >= difference_type(3), "");
    const _RandomAccessIterator __begin = __first;  // 仅用于边界检查，不会被移动
    const _RandomAccessIterator __end = __last;
    (void)__end;

    value_type __pivot(_Ops::iter_move(__first));
    // 找第一个大于 pivot 的元素。
    if (__comp(__pivot, *(__last - difference_type(1)))) {
        // 末元素已知大于 pivot，搜索无需守卫。
        do {
            ++__first;
            CANN_ASC_STL_DETAIL_ASSERT(__first != __end,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
        } while (!__comp(__pivot, *__first));
    } else {
        while (++__first < __last && !__comp(__pivot, *__first)) {
        }
    }
    // 找最后一个小于等于 pivot 的元素。
    if (__first < __last) {
        // __introsort 在调用本函数前必做三值取样，故此搜索必有守卫。
        do {
            CANN_ASC_STL_DETAIL_ASSERT(__last != __begin,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
            --__last;
        } while (__comp(__pivot, *__last));
    }
    // 若第一个大于 pivot 的元素越过（或重合于）最后一个小于等于 pivot 的元素，
    // 说明未发生任何交换即覆盖了整个区间，即区间本身已经分区。
    bool __already_partitioned = __first >= __last;
    if (!__already_partitioned) {
        _Ops::iter_swap(__first, __last);
        ++__first;
    }

    // 以下 [__first, __last) 中的 __last 为开区间端点，两侧均改用减一后的闭区间端点。
    _RandomAccessIterator __lm1 = __last - difference_type(1);
    uint64_t __left_bitset = 0;
    uint64_t __right_bitset = 0;

    // 提示：长度 = __lm1 - __first + 1。
    while (__lm1 - __first >= 2 * __sort_detail::__block_size - 1) {
        // 记录当前左侧元素的比较结果。
        if (__left_bitset == 0) {
            ::asc::std::__populate_left_bitset<_Compare>(__first, __comp, __pivot, __left_bitset);
        }
        // 记录当前右侧元素的比较结果。
        if (__right_bitset == 0) {
            ::asc::std::__populate_right_bitset<_Compare>(__lm1, __comp, __pivot, __right_bitset);
        }
        // 交换两侧位集中记录的待交换元素。
        ::asc::std::__swap_bitmap_pos<_AlgPolicy, _RandomAccessIterator>(__first, __lm1, __left_bitset, __right_bitset);
        // 仅当该侧需要移动的元素已全部移走时才推进游标。
        __first += (__left_bitset == 0) ? difference_type(__sort_detail::__block_size) : difference_type(0);
        __lm1 -= (__right_bitset == 0) ? difference_type(__sort_detail::__block_size) : difference_type(0);
    }
    // 此时至少一侧剩余不足一个完整块。
    ::asc::std::__bitset_partition_partial_blocks<_AlgPolicy, _Compare>(
        __first, __lm1, __comp, __pivot, __left_bitset, __right_bitset);
    // 至少一个位集已清空；对非空位集内的元素完成正确的分区。
    ::asc::std::__swap_bitmap_pos_within<_AlgPolicy>(__first, __lm1, __left_bitset, __right_bitset);

    // 把 pivot 移到最终位置。
    _RandomAccessIterator __pivot_pos = __first - difference_type(1);
    if (__begin != __pivot_pos) {
        *__begin = _Ops::iter_move(__pivot_pos);
    }
    *__pivot_pos = ::asc::std::move(__pivot);
    return ::asc::std::make_pair(__pivot_pos, __already_partitioned);
}

// 用比较器 __comp 对区间 [__first, __last) 做分区；pivot 已置于 *__first。
// 与 pivot 等价的元素保留在 pivot 右侧。返回值含义同上，区间长度至少为三。
template <class _AlgPolicy, class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr ::asc::std::pair<_RandomAccessIterator, bool> __partition_with_equals_on_right(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    CANN_ASC_STL_DETAIL_ASSERT(__last - __first >= difference_type(3), "");
    const _RandomAccessIterator __begin = __first;  // 仅用于边界检查，不会被移动
    const _RandomAccessIterator __end = __last;
    (void)__end;
    value_type __pivot(_Ops::iter_move(__first));
    // 找第一个大于等于 pivot 的元素。__introsort 调用前必做三值取样，搜索必有守卫。
    do {
        ++__first;
        CANN_ASC_STL_DETAIL_ASSERT(__first != __end,
            "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
    } while (__comp(*__first, __pivot));

    // 找最后一个小于 pivot 的元素。
    if (__begin == __first - difference_type(1)) {
        while (__first < __last && !__comp(*--__last, __pivot)) {
        }
    } else {
        // 有守卫。
        do {
            CANN_ASC_STL_DETAIL_ASSERT(__last != __begin,
                "Would read out of bounds, does your comparator satisfy the strict-weak ordering requirement?");
            --__last;
        } while (!__comp(*__last, __pivot));
    }

    // 若第一个大于等于 pivot 的元素越过（或重合于）最后一个小于 pivot 的元素，
    // 说明未发生任何交换即覆盖了整个区间，即区间本身已经分区。
    bool __already_partitioned = __first >= __last;
    // 处理剩余元素：成对交换位于 pivot 错误一侧的元素。
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
    // 把 pivot 移到最终位置。
    _RandomAccessIterator __pivot_pos = __first - difference_type(1);
    if (__begin != __pivot_pos) {
        *__begin = _Ops::iter_move(__pivot_pos);
    }
    *__pivot_pos = ::asc::std::move(__pivot);
    return ::asc::std::make_pair(__pivot_pos, __already_partitioned);
}

// 与上一函数类似，但与 pivot 等价的元素置于 pivot 左侧。返回 pivot 的新位置。
template <class _AlgPolicy, class _RandomAccessIterator, class _Compare>
CANN_ASC_STL_API constexpr _RandomAccessIterator __partition_with_equals_on_left(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using value_type = typename iterator_traits<_RandomAccessIterator>::value_type;
    const _RandomAccessIterator __begin = __first;  // 仅用于边界检查，不会被移动
    const _RandomAccessIterator __end = __last;
    (void)__end;
    value_type __pivot(_Ops::iter_move(__first));
    if (__comp(__pivot, *(__last - difference_type(1)))) {
        // 有守卫。
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
        // __introsort 调用前必做三值取样，搜索必有守卫。
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

// 主排序函数。实现 introsort 并结合下列技术：
//  - 可选的位集快排分区（block quicksort partitioning），
//  - 小长度下的有守卫/无守卫插入排序，
//  - Tukey ninther 技术选取 pivot，
//  - 分区是否原本有序的快速检测。
// 实现部分基于 Orson Peters 的 pattern-defeating quicksort：
// <https://github.com/orlp/pdqsort>。
template <class _AlgPolicy, class _Compare, class _RandomAccessIterator, bool _UseBitSetPartition>
CANN_ASC_STL_API constexpr void __introsort(_RandomAccessIterator __first, _RandomAccessIterator __last,
    _Compare __comp, typename iterator_traits<_RandomAccessIterator>::difference_type __depth, bool __leftmost = true)
{
    using _Ops = _AlgPolicy;
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    using _Comp_ref = __comp_ref_type<_Compare>;
    // 启用插入排序的长度上界。
    constexpr difference_type __limit = 24;
    // 启用 Tukey ninther 取中技术的长度下界。
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
        // 长度低于阈值时改用插入排序。
        if (__len < __limit) {
            if (__leftmost) {
                ::asc::std::__insertion_sort<_AlgPolicy, _Compare>(__first, __last, __comp);
            } else {
                ::asc::std::__insertion_sort_unguarded<_AlgPolicy, _Compare>(__first, __last, __comp);
            }
            return;
        }
        if (__depth == 0) {
            // 依 introsort 思想退化为堆排序（__partial_sort 以 last 为 middle 即全区间堆排序）。
            ::asc::std::__partial_sort<_AlgPolicy, _Compare>(__first, __last, __last, __comp);
            return;
        }
        --__depth;
        {
            difference_type __half_len = __len / 2;
            // 依区间长度选用 Tukey ninther 或三值取样选 pivot。
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
        // 当前区间左侧的元素已排序。若当前区间不是整个待排序区间的最左段，且
        // pivot 与左侧已排序段的最高元素等价，则在“等价元素置于左侧”的分区
        // 约定下，[first, pivot] 内的元素都等价于 pivot，无需再排左侧。
        if (!__leftmost && !__comp(*(__first - difference_type(1)), *__first)) {
            __first = ::asc::std::__partition_with_equals_on_left<_AlgPolicy, _RandomAccessIterator, _Comp_ref>(
                __first, __last, _Comp_ref(__comp));
            continue;
        }
        // 仅在明确要求时使用位集分区。
        auto __ret = _UseBitSetPartition ?
            ::asc::std::__bitset_partition<_AlgPolicy, _RandomAccessIterator, _Compare>(__first, __last, __comp) :
            ::asc::std::__partition_with_equals_on_right<_AlgPolicy, _RandomAccessIterator, _Compare>(
                __first, __last, __comp);
        _RandomAccessIterator __i = __ret.first;
        // [__first, __i) < *__i 且 *__i <= [__i+1, __last)
        // 若分区本身已经完美，看看插入排序是否更快……
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
        // 左半部分递归排序，右半部分通过尾递归消除迭代处理。
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

    // 仅对算术类型启用位集分区，且要求使用默认比较器以确保比较过程无分支。
    ::asc::std::__introsort<_AlgPolicy, _Comp, _RandomAccessIterator,
        __use_branchless_sort<_Comp, _RandomAccessIterator>>(__first, __last, __comp, __depth_limit);
}

template <class _AlgPolicy, class _RandomAccessIterator, class _Comp>
CANN_ASC_STL_API constexpr void __sort_dispatch(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Comp& __comp)
{
    using difference_type = typename iterator_traits<_RandomAccessIterator>::difference_type;
    difference_type __depth_limit = 2 * ::asc::std::__bit_log2(static_cast<uint64_t>(__last - __first));

    // 仅对算术类型启用位集分区，且要求使用默认比较器以确保比较过程无分支。
    ::asc::std::__introsort<_AlgPolicy, _Comp&, _RandomAccessIterator,
        __use_branchless_sort<_Comp, _RandomAccessIterator>>(__first, __last, __comp, __depth_limit);
}

template <class _Type, class... _Options>
using __is_any_of = _Or<is_same<_Type, _Options>...>;

template <class _Type>
using __sort_is_specialized_in_library = __is_any_of<_Type, char, wchar_t, signed char, unsigned char, short,
    unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long, float, double, long double>;

// 库内已特化实现的算术类型裸指针 + 简单比较器：走比较器按引用、可启用无分支
// 位集分派的快速路径。
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
        // 常量求值回退堆排序：introsort 的无守卫插入排序与分区循环依赖分区不变式，
        // 常量求值的越界诊断无法证明其安全。
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
    // AI Core 禁止递归调用：设备侧沿用迭代式原地堆排（无分配、无递归，
    // 保持 O(N log N) 比较界）；宿主侧走内省排序快路径。
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
