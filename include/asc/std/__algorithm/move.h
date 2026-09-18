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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MOVE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MOVE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/copy.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class InputIterator, class OutputIterator>
CANN_ASC_STL_API constexpr OutputIterator move(  // NOLINT(build/include_what_you_use)
    InputIterator first, InputIterator last, OutputIterator result)
{
    for (; first != last; ++first, ++result) {
        *result = ::asc::std::move(*first);  // NOLINT(build/include_what_you_use)
    }
    return result;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MOVE_H
