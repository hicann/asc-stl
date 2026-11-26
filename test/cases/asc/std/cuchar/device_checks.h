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

#pragma once

#include <asc/std/cuchar>

namespace asc_stl_test_cuchar {

CANN_ASC_STL_API int check()
{
    asc::std::mbstate_t state{};
    char bytes[] = {'?', '!'};
    char16_t u16 = u'X';
    char32_t u32 = U'X';
    if (asc::std::c16rtomb(bytes, u'A', &state) != 1 || bytes[0] != 'A' ||
        asc::std::mbrtoc16(&u16, bytes, 1, &state) != 1 || u16 != u'A' ||
        asc::std::c32rtomb(bytes, U'B', &state) != 1 || bytes[0] != 'B' ||
        asc::std::mbrtoc32(&u32, bytes, 1, &state) != 1 || u32 != U'B' || bytes[1] != '!')
        return 1;
    if (asc::std::mbrtoc16(&u16, bytes, 0, &state) != static_cast<asc::std::size_t>(-2) || u16 != u'A')
        return 2;
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
    char8_t u8 = u8'X';
    if (asc::std::c8rtomb(bytes, u8'C', &state) != 1 || bytes[0] != 'C' ||
        asc::std::mbrtoc8(&u8, bytes, 1, &state) != 1 || u8 != u8'C')
        return 3;
#endif
    bytes[0] = 0;
    return asc::std::mbrtoc32(&u32, bytes, 1, &state) != 0 || u32 != 0;
}

}  // namespace asc_stl_test_cuchar
