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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_GENERATE_N_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_GENERATE_N_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__utility/convert_to_integral.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _OutputIterator, class _Size, class _Generator>
CANN_ASC_STL_API constexpr _OutputIterator generate_n(_OutputIterator __first, _Size __orig_n, _Generator __gen)
{
    using _IntegralSize = decltype(::asc::std::__convert_to_integral(__orig_n));
    _IntegralSize __n = static_cast<_IntegralSize>(__orig_n);
    for (; __n > 0; ++__first, (void)--__n) {
        *__first = __gen();
    }
    return __first;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_GENERATE_N_H
