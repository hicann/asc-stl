/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

//===----------------------------------------------------------------------===//

#ifndef CANN_ASC_STL_STD_DETAIL_NUMERIC_EXCLUSIVE_SCAN_H
#define CANN_ASC_STL_STD_DETAIL_NUMERIC_EXCLUSIVE_SCAN_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__functional/operations.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _InputIterator, class _OutputIterator, class _Tp, class _BinaryOp>
CANN_ASC_STL_API constexpr _OutputIterator exclusive_scan(
    _InputIterator __first, _InputIterator __last, _OutputIterator __result, _Tp __init, _BinaryOp __b)
{
    if (__first != __last) {
        _Tp __tmp(__b(__init, *__first));
        while (true) {
            *__result = ::asc::std::move(__init);
            ++__result;
            ++__first;
            if (__first == __last) {
                break;
            }
            __init = ::asc::std::move(__tmp);  // NOLINT(build/include_what_you_use)
            __tmp = __b(__init, *__first);
        }
    }
    return __result;
}

template <class _InputIterator, class _OutputIterator, class _Tp>
CANN_ASC_STL_API constexpr _OutputIterator exclusive_scan(
    _InputIterator __first, _InputIterator __last, _OutputIterator __result, _Tp __init)
{
    return ::asc::std::exclusive_scan(__first, __last, __result, __init, ::asc::std::plus<>());
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_NUMERIC_EXCLUSIVE_SCAN_H
