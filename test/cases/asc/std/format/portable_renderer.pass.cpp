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

#include <asc/std/format>
#include <asc/std/cstddef>
#include <asc/std/version>

int main()
{
    static_assert(CANN_ASC_STL_HAS_FORMAT_TO_N_RESULT);
    char buffer[20]{};
    const auto rendered = asc::std::__format_detail::render_unchecked(buffer, 20, "{}:{}:{}", 8, 42, true, 'x');
    if (rendered.total != 9 || buffer[0] != '4' || buffer[1] != '2' || buffer[2] != ':' || buffer[3] != 't' ||
        buffer[6] != 'e' || buffer[7] != ':' || buffer[8] != 'x')
        return 1;
    char short_buffer[3]{};
    const auto truncated = asc::std::__format_detail::render_unchecked(short_buffer, 3, "{}", 2, -1234);
    if (truncated.total != 5 || short_buffer[0] != '-' || short_buffer[2] != '2')
        return 2;
    asc::std::format_to_n_result<char*> result{short_buffer + 3, static_cast<asc::std::ptrdiff_t>(truncated.total)};
    if (result.out != short_buffer + 3 || result.size != 5)
        return 3;
#if CANN_ASC_STL_HAS_FORMAT
    char checked[8]{};
    char* end = asc::std::format_to(checked, "{}", 17);
    if (end != checked + 2 || checked[0] != '1' || checked[1] != '7')
        return 4;
#endif
    return 0;
}
