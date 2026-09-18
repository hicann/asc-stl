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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_FILL_N_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_FILL_N_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/convert_to_integral.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _OutputIterator, class _Size, class _Tp>
CANN_ASC_STL_API constexpr _OutputIterator __fill_n(_OutputIterator __first, _Size __n, const _Tp& __value_)
{
    for (; __n > 0; ++__first, (void)--__n) {
        *__first = __value_;
    }
    return __first;
}

template <class _OutputIterator, class _Size, class _Tp>
CANN_ASC_STL_API constexpr _OutputIterator fill_n(_OutputIterator __first, _Size __n, const _Tp& __value_)
{
    return ::asc::std::__fill_n(__first, __convert_to_integral(__n), __value_);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_FILL_N_H
