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

#ifndef CANN_ASC_STL_DETAIL_MEMORY_CHECK_ADDRESS_H
#define CANN_ASC_STL_DETAIL_MEMORY_CHECK_ADDRESS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__cstddef/types.h>
#include <asc/std/cstdint>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

[[nodiscard]] CANN_ASC_STL_API bool __is_valid_address_range(const void* __ptr, ::asc::std::size_t __n) noexcept
{
    if (__n == 0) {
        return false;
    }

    const auto __limit = (~::asc::std::uintptr_t{0}) - static_cast<::asc::std::uintptr_t>(__n);
    const auto __address = reinterpret_cast<::asc::std::uintptr_t>(__ptr);
    return __ptr != nullptr && __address <= __limit;
}

[[nodiscard]] CANN_ASC_STL_API bool __is_valid_address(const void* __ptr) noexcept
{
    return ::asc::__is_valid_address_range(__ptr, 0);
}

[[nodiscard]] CANN_ASC_STL_API bool __are_ptrs_overlapping(
    const void* __ptr_lhs, const void* __ptr_rhs, ::asc::std::size_t __n) noexcept
{
    const auto __lhs = reinterpret_cast<::asc::std::uintptr_t>(__ptr_lhs);
    const auto __rhs = reinterpret_cast<::asc::std::uintptr_t>(__ptr_rhs);
    return __lhs < __rhs + __n && __rhs < __lhs + __n;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_MEMORY_CHECK_ADDRESS_H
