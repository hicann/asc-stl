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

#ifndef CANN_ASC_STL_ASC_STD___CSTDLIB_ABS_H
#define CANN_ASC_STL_ASC_STD___CSTDLIB_ABS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

CANN_ASC_STL_BEGIN_NAMESPACE

CANN_ASC_STL_API constexpr int abs(int value) noexcept
{
    return (value < 0) ? -value : value;
}

CANN_ASC_STL_API constexpr long labs(long value) noexcept
{
    return (value < 0l) ? -value : value;
}

CANN_ASC_STL_API constexpr long abs(long value) noexcept
{
    return ::asc::std::labs(value);
}

CANN_ASC_STL_API constexpr long long llabs(long long value) noexcept
{
    return (value < 0ll) ? -value : value;
}

CANN_ASC_STL_API constexpr long long abs(long long value) noexcept
{
    return ::asc::std::llabs(value);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CSTDLIB_ABS_H
