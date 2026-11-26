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

#ifndef ASC_STL_TEST_STRING_VIEW_DEVICE_CHECKS_H
#define ASC_STL_TEST_STRING_VIEW_DEVICE_CHECKS_H

#include <asc/std/string_view>

#include "comparison_checks.h"

namespace asc_stl_test_string_view {
CANN_ASC_STL_API int check(int seed = 7)
{
    if (int result = check_comparison(seed))
        return 20 + result;
    using view = asc::std::string_view;
    const char data[] = {'a', 0, static_cast<char>('[' + seed), 'a', 0};
    view v(data, 4);
    view empty;
    if (!empty.empty() || v.empty() || v.length() != 4 || v.size() != 4 || v.max_size() < v.size() ||
        v.begin() != v.cbegin() || v.end() != v.cend() || v.rbegin() != v.crbegin() || v.rend() != v.crend() ||
        *v.rbegin() != v.back() || v[1] != 0 || !v.starts_with('a') || !v.starts_with("a") ||
        !v.starts_with(view(data, 2)) || !v.ends_with('a') || !v.ends_with("ba") || !v.ends_with(empty))
        return 1;
    if (v.find(view(data + 1, 2)) != 1 || v.rfind('a') != 3 || v.find("", 5) != view::npos || v.rfind("", 8) != 4 ||
        v.find_first_of("bx") != 2 || v.find_last_of("a") != 3 || v.find_first_not_of("a") != 1 ||
        v.find_last_not_of("a") != 2 || empty.find('a') != view::npos)
        return 2;
    v.remove_prefix(1);
    v.remove_suffix(1);
    v.swap(empty);
    return v.empty() && empty.data() == data + 1 && empty.front() == 0 && empty.back() == 'b' ? 0 : 3;
}
}  // namespace asc_stl_test_string_view

#endif  // ASC_STL_TEST_STRING_VIEW_DEVICE_CHECKS_H
