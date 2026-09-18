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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_PARTITION_COPY_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_PARTITION_COPY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _InputIterator, class _OutputIterator1, class _OutputIterator2, class _Predicate>
CANN_ASC_STL_API constexpr pair<_OutputIterator1, _OutputIterator2> partition_copy(_InputIterator __first,
    _InputIterator __last, _OutputIterator1 __out_true, _OutputIterator2 __out_false, _Predicate __pred)
{
    for (; __first != __last; ++__first) {
        if (__pred(*__first)) {
            *__out_true = *__first;
            ++__out_true;
        } else {
            *__out_false = *__first;
            ++__out_false;
        }
    }
    return pair<_OutputIterator1, _OutputIterator2>(__out_true, __out_false);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_PARTITION_COPY_H
