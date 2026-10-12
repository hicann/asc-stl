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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_FIND_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_FIND_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/invoke.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Iter, class _Sent, class _Tp, class _Proj>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _Iter __find_impl(
    _Iter __first, _Sent __last, const _Tp& __value, _Proj& __proj)
{
    for (; __first != __last; ++__first)
        if (::asc::std::invoke(__proj, *__first) == __value)
            break;
    return __first;
}

template <class _InputIterator, class _Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _InputIterator find(
    _InputIterator __first, _InputIterator __last, const _Tp& __value)
{
    for (; __first != __last; ++__first)
        if (*__first == __value)
            break;
    return __first;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_FIND_H
