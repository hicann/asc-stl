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

#include <asc/std/detail/__config>

// CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED is checked in <asc/std/__asc/builtin.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

[[nodiscard]] CANN_ASC_STL_API constexpr bool is_constant_evaluated() noexcept
{
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED)
    return CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED();
#else   // ^^^ CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED vvv
    return false;
#endif  // ^^^ !CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED ^^^
}

[[nodiscard]] CANN_ASC_STL_API constexpr bool __accl_default_is_constant_evaluated() noexcept
{
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED)
    return CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED();
#else   // ^^^ CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED vvv
    return true;
#endif  // ^^^ !CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED ^^^
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_CONSTANT_EVALUATED_H
