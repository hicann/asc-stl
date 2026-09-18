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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_UNREACHABLE_SENTINEL_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_UNREACHABLE_SENTINEL_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/concepts.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// MSVC requires an interesting workaround for a /permissive- bug
// We cannot simply define unreachable_sentinel_t with it friendfunctions,
// but we must derive from a base class in a different namespace so that they
// are only ever found through ADL

struct unreachable_sentinel_t
#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)
    ;  // NOLINT(whitespace/semicolon)
namespace __unreachable_sentinel_detail {
struct __unreachable_base
#endif  // CANN_ASC_STL_DETAIL_COMPILER(MSVC)
{
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(weakly_incrementable<_Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const unreachable_sentinel_t&, const _Iter&) noexcept
    {
        return false;
    }
#if CANN_ASC_STL_DETAIL_STD_VER < 2020
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(weakly_incrementable<_Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        const _Iter&, const unreachable_sentinel_t&) noexcept
    {
        return false;
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(weakly_incrementable<_Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const unreachable_sentinel_t&, const _Iter&) noexcept
    {
        return true;
    }
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Iter)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(weakly_incrementable<_Iter>)
    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator!=(
        const _Iter&, const unreachable_sentinel_t&) noexcept
    {
        return true;
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER < 2020
};

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)
}  // namespace __unreachable_sentinel_detail
struct unreachable_sentinel_t : __unreachable_sentinel_detail::__unreachable_base {};
#endif  // CANN_ASC_STL_DETAIL_COMPILER(MSVC)

CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT unreachable_sentinel_t unreachable_sentinel{};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD
#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_UNREACHABLE_SENTINEL_H
