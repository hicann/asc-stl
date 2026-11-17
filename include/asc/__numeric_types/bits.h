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

#ifndef CANN_ASC_STL_ASC___NUMERIC_TYPES_BITS_H
#define CANN_ASC_STL_ASC___NUMERIC_TYPES_BITS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__numeric_types/traits.h>
#include <asc/std/__exception/terminate.h>
#include <asc/std/__type_traits/enable_if.h>

namespace asc {

template <class T>
CANN_ASC_STL_DETAIL_NUMERIC_API constexpr typename numeric_format_traits<T>::storage_type to_bits(T value) noexcept
{
    return detail::numeric_access::read(value);
}

template <class T>
CANN_ASC_STL_DETAIL_NUMERIC_API constexpr T from_bits(typename numeric_format_traits<T>::storage_type bits) noexcept
{
    if constexpr (numeric_format_traits<T>::format == numeric_format::int4) {
        if (bits > 15) {
            asc::std::terminate();
        }
    }
    return detail::numeric_access::make<numeric_format_traits<T>::format>(bits);
}

template <class Packed, asc::std::enable_if_t<(numeric_format_traits<Packed>::lanes == 2), int> = 0>
CANN_ASC_STL_DETAIL_NUMERIC_API constexpr Packed pack_elements(asc::std::uint8_t low, asc::std::uint8_t high) noexcept
{
    if (low > 15 || high > 15) {
        asc::std::terminate();
    }
    return asc::from_bits<Packed>(static_cast<asc::std::uint8_t>(low | (high << 4)));
}

template <class Packed, asc::std::enable_if_t<(numeric_format_traits<Packed>::lanes == 2), int> = 0>
CANN_ASC_STL_DETAIL_NUMERIC_API constexpr asc::std::uint8_t unpack_element(Packed value, unsigned index) noexcept
{
    if (index > 1) {
        asc::std::terminate();
    }
    return static_cast<asc::std::uint8_t>((asc::to_bits(value) >> (index * 4)) & 15);
}

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___NUMERIC_TYPES_BITS_H
