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

#ifndef ASC_STL_TEST_FORMAT_DEVICE_CHECKS_H
#define ASC_STL_TEST_FORMAT_DEVICE_CHECKS_H

#include <asc/std/format>

namespace asc_stl_test_format {

CANN_ASC_STL_API int check(int seed = 7)
{
    namespace s = asc::std;
    char output[12] = {'!', '!', '!', '!', '!', '!', '!', '!', '!', '!', '!', '!'};
#if CANN_ASC_STL_HAS_FORMAT
    const char expected[] = "{-7:FF}";
    char* end = s::format_to(output + 1, "{{{}:{:X}}}", -seed, 255);
    if (end != output + 8 || output[0] != '!' || *end != '!' || s::formatted_size("{{{}:{:X}}}", -seed, 255) != 7)
        return 1;
    for (int i = 0; i < 7; ++i)
        if (output[i + 1] != expected[i])
            return 2;
    for (int i = -1; i <= 5; ++i) {
        char small[7] = {'#', '#', '#', '#', '#', '#', '#'};
        auto rendered = s::format_to_n(small + 1, i, "{:b}", seed);
        const int written = i < 0 ? 0 : (i < 3 ? i : 3);
        if (rendered.out != small + 1 + written || rendered.size != 3 || small[0] != '#' || *rendered.out != '#')
            return 3;
        for (int j = 0; j < written; ++j)
            if (small[1 + j] != '1')
                return 4;
    }
#else
    s::format_to_n_result<char*> result{output + 1, seed};
    if (result.out != output + 1 || result.size != 7)
        return 5;
#endif
    return 0;
}

}  // namespace asc_stl_test_format

#endif  // ASC_STL_TEST_FORMAT_DEVICE_CHECKS_H
