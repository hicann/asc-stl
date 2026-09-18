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

#ifndef CANN_ASC_STL_ASC_STD___TYPE_TRAITS_ALIGNED_STORAGE_H
#define CANN_ASC_STL_ASC_STD___TYPE_TRAITS_ALIGNED_STORAGE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/nat.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace detail {
CANN_ASC_STL_API constexpr size_t default_storage_alignment(size_t length) noexcept
{
    return length >= 16 ? 16 : length >= 8 ? 8 : length >= 4 ? 4 : length >= 2 ? 2 : 1;
}
}  // namespace detail

template <size_t Length, size_t Alignment = detail::default_storage_alignment(Length)>
struct aligned_storage {
    struct alignas(Alignment) type {
        unsigned char data[(Length + Alignment - 1) / Alignment * Alignment];
    };
};

template <size_t Length, size_t Alignment = detail::default_storage_alignment(Length)>
using aligned_storage_t = typename aligned_storage<Length, Alignment>::type;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TYPE_TRAITS_ALIGNED_STORAGE_H
