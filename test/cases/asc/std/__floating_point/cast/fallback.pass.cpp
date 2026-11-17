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

#include <asc/std/version>

// Exercise the non-constexpr implementation even on compilers with bit_cast.
// Keep this configuration local to this single-translation-unit regression.
#undef CANN_ASC_STL_DETAIL_BUILTIN_BIT_CAST
#undef CANN_ASC_STL_DETAIL_CONSTEXPR_BIT_CAST
#undef CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_BIT_CAST
#undef CANN_ASC_STL_LIB_bit_cast
#define CANN_ASC_STL_DETAIL_CONSTEXPR_BIT_CAST
#define CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_BIT_CAST() 0

#include <asc/std/algorithm>
#include <asc/std/complex>
#include <asc/std/mdspan>
#include "support/bf16_cast_semantics.h"

int main()
{
    int failures = static_cast<int>(asc_stl_bf16_cast_test::evaluate());
    failures += asc::std::__detail::__fp8_encode(1.0f, 4, 3, true) != 0x38;
    failures += asc::std::__detail::__fp8_decode(0x3c, 5, 2, false) != 1.0f;
    failures += asc::std::__detail::__e8m0_encode(1.0f) != 127;
    failures += asc::std::__detail::__e8m0_decode(128) != 2.0f;

    // Public headers must remain usable with runtime-only bit casts.
    const asc::std::complex<float> response = asc::std::complex<float>(1, 2) / asc::std::complex<float>(2, 1);
    failures += response.real() != 0.8f || response.imag() != 0.6f;
    int keys[] = {1, 2, 2, 4};
    const auto matches = asc::std::equal_range(keys, keys + 4, 2);
    failures += matches.first != keys + 1 || matches.second != keys + 3;
    asc::std::mdspan<int, asc::std::extents<int, 2, 2>> matrix(keys);
    const auto row = asc::std::submdspan(matrix, 1, asc::std::pair<int, int>(0, 2));
    failures += row(0) != 2 || row(1) != 4;
    return failures;
}
