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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SHIFT_RIGHT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SHIFT_RIGHT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/move.h>
#include <asc/std/__algorithm/move_backward.h>
#include <asc/std/__algorithm/swap_ranges.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator shift_right(
    _ForwardIterator __first, _ForwardIterator __last, typename iterator_traits<_ForwardIterator>::difference_type __n)
{
    if (__n == 0) {
        return __first;
    }
    _ForwardIterator __ret = __first;
    for (; __n > 0; --__n) {
        if (__ret == __last) {
            return __last;
        }
        ++__ret;
    }
    // An __n-element scratch space [__first, __ret) slides left to right; once
    // the leading edge reaches __last the remaining prefix is moved into place.
    _ForwardIterator __trail = __first;
    _ForwardIterator __lead = __ret;
    while (__trail != __ret) {
        if (__lead == __last) {
            ::asc::std::move(__first, __trail, __ret);
            return __ret;
        }
        ++__trail;
        ++__lead;
    }
    _ForwardIterator __mid = __first;
    while (true) {
        if (__lead == __last) {
            __trail = ::asc::std::move(__mid, __ret, __trail);
            ::asc::std::move(__first, __mid, __trail);
            return __ret;
        }
        ::asc::std::swap(*__mid, *__trail);  // NOLINT(build/include_what_you_use)
        ++__mid;
        ++__trail;
        ++__lead;
        if (__mid == __ret) {
            __mid = __first;
        }
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SHIFT_RIGHT_H
