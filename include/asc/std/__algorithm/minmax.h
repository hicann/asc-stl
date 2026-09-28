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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MINMAX_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MINMAX_H

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
#include <asc/std/__algorithm/minmax_element.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Tp, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr pair<const _Tp&, const _Tp&> minmax(
    const _Tp& __a, const _Tp& __b, _Compare __comp)
{
    return __comp(__b, __a) ? pair<const _Tp&, const _Tp&>(__b, __a) : pair<const _Tp&, const _Tp&>(__a, __b);
}

template <class _Tp>
// NOLINTNEXTLINE(build/include_what_you_use)
[[nodiscard]] CANN_ASC_STL_API constexpr pair<const _Tp&, const _Tp&> minmax(const _Tp& __a, const _Tp& __b)
{
    return ::asc::std::minmax(__a, __b, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MINMAX_H
