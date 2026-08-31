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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_NBIT_INT_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_NBIT_INT_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/cstdint>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <size_t _NBits, bool _IsSigned>
CANN_ASC_STL_API constexpr auto __make_nbit_int_impl() noexcept
{
    if constexpr (_IsSigned) {
        if constexpr (_NBits == 8) {
            return int8_t{};
        } else if constexpr (_NBits == 16) {
            return int16_t{};
        } else if constexpr (_NBits == 32) {
            return int32_t{};
        } else if constexpr (_NBits == 64) {
            return int64_t{};
        }
#if CANN_ASC_STL_DETAIL_HAS_INT128()
        else if constexpr (_NBits == 128) {
            return __int128_t{};
        }
#endif          // CANN_ASC_STL_DETAIL_HAS_INT128()
        else {  // NOLINT(readability/braces)
            static_assert(__always_false_v<decltype(_NBits)>, "Unsupported signed integer size");
            CANN_ASC_STL_DETAIL_UNREACHABLE();
        }
    } else {
        if constexpr (_NBits == 8) {
            return uint8_t{};
        } else if constexpr (_NBits == 16) {
            return uint16_t{};
        } else if constexpr (_NBits == 32) {
            return uint32_t{};
        } else if constexpr (_NBits == 64) {
            return uint64_t{};
        }
#if CANN_ASC_STL_DETAIL_HAS_INT128()
        else if constexpr (_NBits == 128) {
            return __uint128_t{};
        }
#endif          // CANN_ASC_STL_DETAIL_HAS_INT128()
        else {  // NOLINT(readability/braces)
            static_assert(__always_false_v<decltype(_NBits)>, "Unsupported unsigned integer size");
            CANN_ASC_STL_DETAIL_UNREACHABLE();
        }
    }
}

template <size_t _NBits, bool _IsSigned = true>
using __make_nbit_int_t = decltype(__make_nbit_int_impl<_NBits, _IsSigned>());

template <size_t _NBits>
using __make_nbit_uint_t = __make_nbit_int_t<_NBits, false>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_NBIT_INT_H
