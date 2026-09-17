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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_PARTITION_POINT_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_PARTITION_POINT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/half_positive.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _ForwardIterator, class _Predicate>
CANN_ASC_STL_API constexpr _ForwardIterator partition_point(
    _ForwardIterator __first, _ForwardIterator __last, _Predicate __pred)
{
    using difference_type = typename iterator_traits<_ForwardIterator>::difference_type;
    difference_type __len = ::asc::std::distance(__first, __last);
    while (__len != 0) {
        difference_type __l2 = ::asc::std::__half_positive(__len);
        _ForwardIterator __m = __first;
        ::asc::std::advance(__m, __l2);
        if (__pred(*__m)) {
            __first = ++__m;
            __len -= __l2 + 1;
        } else {
            __len = __l2;
        }
    }
    return __first;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_PARTITION_POINT_H
