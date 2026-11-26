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

#ifndef ASC_STL_TEST_STRING_VIEW_COMPARISON_H
#define ASC_STL_TEST_STRING_VIEW_COMPARISON_H

#include <asc/std/string_view>

namespace asc_stl_test_string_view {
template <class View>
CANN_ASC_STL_API bool compare_views(View lo, View hi)
{
    auto p = lo.data();
    auto q = hi.data();
    return lo < hi && lo <= q && p < hi && hi > lo && hi >= p && q > lo && lo != hi && lo == p && p == lo && lo != q &&
        q != lo && p <= lo && q >= lo && hi > p && lo < q && p <= hi && !(q > hi);
}
CANN_ASC_STL_API int check_comparison(int seed)
{
    namespace s = asc::std;
    using asc::std::literals::string_view_literals::operator""sv;
    if (!compare_views("a"sv, "b"sv) || !compare_views(u"a"sv, u"b"sv) || !compare_views(U"a"sv, U"b"sv) ||
        !compare_views(L"a"sv, L"b"sv))
        return 1;
#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
    if (!compare_views(u8"a"sv, u8"b"sv))
        return 2;
#endif
    const char a[] = {static_cast<char>(seed + 90), 0, 'x', 0};
    const char b[] = {'a', 0, 'x', 0};
    const s::string_view lhs(a, 3), rhs(b, 3);
    return lhs == rhs && s::hash<s::string_view>{}(lhs) == s::hash<s::string_view>{}(rhs) &&
            lhs.compare(s::string_view(b, 1)) > 0 && s::string_view(b, 1).compare(rhs) < 0 ?
        0 :
        3;
}
}  // namespace asc_stl_test_string_view

#endif  // ASC_STL_TEST_STRING_VIEW_COMPARISON_H
