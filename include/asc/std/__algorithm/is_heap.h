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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_IS_HEAP_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_IS_HEAP_H

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
#include <asc/std/__algorithm/is_heap_until.h>
#include <asc/std/__iterator/iterator_traits.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _RandomAccessIterator, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr bool is_heap(
    _RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    return ::asc::std::__is_heap_until(__first, __last, static_cast<__comp_ref_type<_Compare>>(__comp)) == __last;
}

template <class _RandomAccessIterator>
[[nodiscard]] CANN_ASC_STL_API constexpr bool is_heap(_RandomAccessIterator __first, _RandomAccessIterator __last)
{
    return ::asc::std::is_heap(__first, __last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_IS_HEAP_H
