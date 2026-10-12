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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SET_DIFFERENCE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SET_DIFFERENCE_H

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
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// 通用内部实现（dev 语义）：sentinel/转发引用形参，尾段整段复制后以 pair 返回
// 两迭代器终值。基座 copy.h 无带策略的 __copy 变体，尾段改写等价的内联循环并
// 直接构造 pair（语义等价，见 notes）。
template <class _AlgPolicy, class _Comp, class _InIter1, class _Sent1, class _InIter2, class _Sent2, class _OutIter>
CANN_ASC_STL_API constexpr pair<remove_cvref_t<_InIter1>, remove_cvref_t<_OutIter>> __set_difference(
    _InIter1&& __first1, _Sent1&& __last1, _InIter2&& __first2, _Sent2&& __last2, _OutIter&& __result, _Comp&& __comp)
{
    while (__first1 != __last1 && __first2 != __last2) {
        if (__comp(*__first1, *__first2)) {
            *__result = *__first1;
            ++__first1;
            ++__result;
        } else if (__comp(*__first2, *__first1)) {
            ++__first2;
        } else {
            ++__first1;
            ++__first2;
        }
    }
    while (__first1 != __last1) {
        *__result = *__first1;
        ++__first1;
        ++__result;
    }
    return pair<remove_cvref_t<_InIter1>, remove_cvref_t<_OutIter>>(
        ::asc::std::move(__first1), ::asc::std::move(__result));  // NOLINT(build/include_what_you_use)
}

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
CANN_ASC_STL_API constexpr OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare compare)
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // CCE 设备侧：经 pair 返回输出迭代器会附加段偏移，破坏其本地地址表示，
    // 走手写循环直接返回（与宿主路径语义等价）。
    while (first1 != last1 && first2 != last2) {
        if (compare(*first1, *first2)) {
            *result++ = *first1++;
        } else if (compare(*first2, *first1)) {
            ++first2;
        } else {
            ++first1;
            ++first2;
        }
    }
    while (first1 != last1) {
        *result++ = *first1++;
    }
    return result;
#else
    return ::asc::std::__set_difference<__classic_algorithm_iterator_operations, __comp_ref_type<Compare>>(
        first1, last1, first2, last2, result, compare)
        .second;
#endif
}

template <class InputIterator1, class InputIterator2, class OutputIterator>
CANN_ASC_STL_API constexpr OutputIterator set_difference(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
    return ::asc::std::set_difference(first1, last1, first2, last2, result, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SET_DIFFERENCE_H
