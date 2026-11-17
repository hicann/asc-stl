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

#ifndef CANN_ASC_STL_ASC___NUMERIC_TYPES_NATIVE_H
#define CANN_ASC_STL_ASC___NUMERIC_TYPES_NATIVE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__numeric_types/bits.h>
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>

namespace asc {

template <class T>
CANN_ASC_STL_API native_numeric_t<T> to_native_numeric(T value) noexcept
{
    using Native = native_numeric_t<T>;
    if constexpr (asc::std::is_trivially_copyable_v<Native>) {
        return asc::std::bit_cast<Native>(asc::to_bits(value));
    } else {
        // The qualified legacy SDK class exposes its representation byte.
        // New SDK builtins take the ordinary bit-copy path above.
        static_assert(detail::numeric_native_byte_member<Native>::value);
        Native result;
        result.val = asc::std::bit_cast<char>(asc::to_bits(value));
        return result;
    }
}

template <class T>
CANN_ASC_STL_API T from_native_numeric(const native_numeric_t<T>& value) noexcept
{
    using Native = native_numeric_t<T>;
    if constexpr (asc::std::is_trivially_copyable_v<Native>) {
        return asc::from_bits<T>(asc::std::bit_cast<typename numeric_format_traits<T>::storage_type>(value));
    } else {
        static_assert(detail::numeric_native_byte_member<Native>::value);
        return asc::from_bits<T>(static_cast<asc::std::uint8_t>(value.val));
    }
}

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___NUMERIC_TYPES_NATIVE_H
