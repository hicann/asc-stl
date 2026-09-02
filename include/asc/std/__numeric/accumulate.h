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

#ifndef CANN_ASC_STL_STD_DETAIL_NUMERIC_ACCUMULATE_H
#define CANN_ASC_STL_STD_DETAIL_NUMERIC_ACCUMULATE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _InputIterator, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init)
{
    for (; __first != __last; ++__first) {
        __init = ::asc::std::move(__init) + *__first;
    }
    return __init;
}

template <class _InputIterator, class _Tp, class _BinaryOperation>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp accumulate(
    _InputIterator __first, _InputIterator __last, _Tp __init, _BinaryOperation __binary_op)
{
    for (; __first != __last; ++__first) {
        __init = __binary_op(::asc::std::move(__init), *__first);  // NOLINT(build/include_what_you_use)
    }
    return __init;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_NUMERIC_ACCUMULATE_H
