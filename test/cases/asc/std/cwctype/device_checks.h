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

#include <asc/std/cwctype>

namespace asc_stl_test_cwctype {

CANN_ASC_STL_API int check()
{
    for (int i = 0; i != 256; ++i) {
        const bool upper = i >= 'A' && i <= 'Z';
        const bool lower = i >= 'a' && i <= 'z';
        const bool digit = i >= '0' && i <= '9';
        if ((asc::std::iswalpha(i) != 0) != (upper || lower))
            return 1;
        if ((asc::std::iswalnum(i) != 0) != (upper || lower || digit))
            return 2;
        if ((asc::std::iswblank(i) != 0) != (i == ' ' || i == '\t'))
            return 3;
        if ((asc::std::iswcntrl(i) != 0) != (i < 32 || i == 127))
            return 4;
        if ((asc::std::iswdigit(i) != 0) != (digit))
            return 5;
        if ((asc::std::iswgraph(i) != 0) != (i >= 33 && i <= 126))
            return 6;
        if ((asc::std::iswlower(i) != 0) != (lower))
            return 7;
        if ((asc::std::iswprint(i) != 0) != (i >= 32 && i <= 126))
            return 8;
        if ((asc::std::iswpunct(i) != 0) != (i >= 33 && i <= 126 && !digit && !upper && !lower))
            return 9;
        if ((asc::std::iswspace(i) != 0) != (i == ' ' || (i >= 9 && i <= 13)))
            return 10;
        if ((asc::std::iswupper(i) != 0) != (upper))
            return 11;
        if ((asc::std::iswxdigit(i) != 0) != (digit || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F')))
            return 12;
        if (asc::std::towlower(i) != static_cast<decltype(asc::std::towlower(i))>(upper ? i + 32 : i) ||
            asc::std::towupper(i) != static_cast<decltype(asc::std::towupper(i))>(lower ? i - 32 : i))
            return 13;
    }
    const char digit_name[] = {'d', 'i', 'g', 'i', 't', 0};
    const char transform_name[] = {'t', 'o', 'u', 'p', 'p', 'e', 'r', 0};
    const auto property = asc::std::wctype(digit_name);
    const auto transform = asc::std::wctrans(transform_name);
    if (!property || !transform || !asc::std::iswctype(L'8', property) || asc::std::iswctype(L'A', property) ||
        asc::std::towctrans(L'b', transform) != L'B')
        return 14;
    return 0;
}

}  // namespace asc_stl_test_cwctype
