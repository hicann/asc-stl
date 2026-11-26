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

#ifndef ASC_STL_TEST_CSTDINT_INTEGER_LIMITS_H
#define ASC_STL_TEST_CSTDINT_INTEGER_LIMITS_H

#include <asc/std/cstdint>
#include <asc/std/limits>
#include <asc/std/type_traits>

namespace asc_stl_test_cstdint {
template <class Signed, class Unsigned, unsigned Bits>
constexpr bool integer_model()
{
    return asc::std::is_integral_v<Signed> && asc::std::is_integral_v<Unsigned> &&
        asc::std::numeric_limits<Signed>::is_signed && !asc::std::numeric_limits<Unsigned>::is_signed &&
        asc::std::numeric_limits<Signed>::digits + 1 >= static_cast<int>(Bits) &&
        asc::std::numeric_limits<Unsigned>::digits >= static_cast<int>(Bits);
}

#define ASC_STL_CHECK_INTEGER_LIMITS(width, suffix, macro_suffix)                                            \
    static_assert(integer_model<asc::std::int##suffix##_t, asc::std::uint##suffix##_t, width>());            \
    static_assert(INT##macro_suffix##_MIN == asc::std::numeric_limits<asc::std::int##suffix##_t>::lowest()); \
    static_assert(INT##macro_suffix##_MAX == asc::std::numeric_limits<asc::std::int##suffix##_t>::max());    \
    static_assert(UINT##macro_suffix##_MAX == asc::std::numeric_limits<asc::std::uint##suffix##_t>::max())
#define ASC_STL_CHECK_INTEGER_WIDTH(bits)                           \
    ASC_STL_CHECK_INTEGER_LIMITS(bits, bits, bits);                 \
    ASC_STL_CHECK_INTEGER_LIMITS(bits, _least##bits, _LEAST##bits); \
    ASC_STL_CHECK_INTEGER_LIMITS(bits, _fast##bits, _FAST##bits);   \
    static_assert(INT##bits##_C(12) == 12 && UINT##bits##_C(12) == 12)
ASC_STL_CHECK_INTEGER_WIDTH(8);
ASC_STL_CHECK_INTEGER_WIDTH(16);
ASC_STL_CHECK_INTEGER_WIDTH(32);
ASC_STL_CHECK_INTEGER_WIDTH(64);
ASC_STL_CHECK_INTEGER_LIMITS(64, max, MAX);
ASC_STL_CHECK_INTEGER_LIMITS(sizeof(void*) * __CHAR_BIT__, ptr, PTR);
static_assert(INTMAX_C(12345) == 12345 && UINTMAX_C(12345) == 12345);
#undef ASC_STL_CHECK_INTEGER_WIDTH
#undef ASC_STL_CHECK_INTEGER_LIMITS
}  // namespace asc_stl_test_cstdint

#endif  // ASC_STL_TEST_CSTDINT_INTEGER_LIMITS_H
