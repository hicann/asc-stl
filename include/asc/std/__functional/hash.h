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

#ifndef CANN_ASC_STL_ASC_STD___FUNCTIONAL_HASH_H
#define CANN_ASC_STL_ASC_STD___FUNCTIONAL_HASH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__fwd/hash.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/underlying_type.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/climits>
#include <asc/std/cstdint>
#include <asc/std/cstring>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct hash {
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API size_t operator()(const T& value) const noexcept
    {
        const auto* bytes = reinterpret_cast<const unsigned char*>(&value);
        size_t result = sizeof(size_t) == 8 ? static_cast<size_t>(1469598103934665603ULL) : 2166136261U;
        const size_t prime = sizeof(size_t) == 8 ? static_cast<size_t>(1099511628211ULL) : 16777619U;
        for (size_t index = 0; index < sizeof(T); ++index) {
            result = (result ^ bytes[index]) * prime;
        }
        return result;
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FUNCTIONAL_HASH_H
