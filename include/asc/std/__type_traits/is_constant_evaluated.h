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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTANT_EVALUATED_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTANT_EVALUATED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__version/features.h>

CANN_ASC_STL_BEGIN_NAMESPACE

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool is_constant_evaluated() noexcept
{
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED)
    return CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED();
#else
    return false;
#endif
}

// Conservative variant for call sites where assuming constant evaluation is the
// safe default: when the compiler has no way to tell, assume we are in a
// constant-evaluated context.
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool __default_is_constant_evaluated() noexcept
{
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED)
    return CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED();
#else
    return true;
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTANT_EVALUATED_H
