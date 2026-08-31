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

#ifndef CANN_ASC_STL_STD_DETAIL_BIT_BLSR_H
#define CANN_ASC_STL_STD_DETAIL_BIT_BLSR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4146)  // unary minus operator applied to unsigned type, result still unsigned

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

[[nodiscard]] CANN_ASC_STL_API constexpr unsigned __accl_blsr(unsigned __x) noexcept
{
    return __x ^ (__x & -__x);
}

[[nodiscard]] CANN_ASC_STL_API constexpr unsigned long __accl_blsr(unsigned long __x) noexcept
{
    return __x ^ (__x & -__x);
}

[[nodiscard]] CANN_ASC_STL_API constexpr unsigned long long __accl_blsr(unsigned long long __x) noexcept
{
    return __x ^ (__x & -__x);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_DIAG_POP

#endif  // CANN_ASC_STL_STD_DETAIL_BIT_BLSR_H
