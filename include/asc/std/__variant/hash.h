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

#ifndef CANN_ASC_STL_ASC_STD___VARIANT_HASH_H
#define CANN_ASC_STL_ASC_STD___VARIANT_HASH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/hash.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__variant/variant.h>
#include <asc/std/__variant/variant_access.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Hash-combine input pair: processes both size_t values in one pass
//! through the byte-level hash of the primary hash template (no
//! __hash_combine facility is available here, so this inlines the equivalent
//! of hashing a scalar pair).
struct __variant_hash_pair {
    size_t first;
    size_t second;
};

CANN_ASC_STL_API size_t __variant_hash_combine(size_t value_hash, size_t index_hash) noexcept
{
    return hash<__variant_hash_pair>{}(__variant_hash_pair{value_hash, index_hash});
}

template <size_t Index, class... Types>
CANN_ASC_STL_API size_t __variant_hash_at(const variant<Types...>& value) noexcept
{
    if constexpr (Index == sizeof...(Types)) {
        // valueless sentinel: an arbitrary fixed constant
        return static_cast<size_t>(299792458);
    } else {
        if (value.index() == Index) {
            using alternative = variant_alternative_t<Index, variant<Types...>>;
            return hash<remove_const_t<alternative>>{}(value.template __get<Index>());
        }
        return __variant_hash_at<Index + 1>(value);
    }
}

template <class... Types>
struct hash<variant<Types...>> {
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API size_t operator()(const variant<Types...>& value) const noexcept
    {
        // Combine the hash of the active alternative's value (the sentinel
        // when valueless) with the hash of the index, so equal values held
        // under different alternatives hash reliably differently.
        return ::asc::std::__variant_hash_combine(__variant_hash_at<0>(value), hash<size_t>{}(value.index()));
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_HASH_H
