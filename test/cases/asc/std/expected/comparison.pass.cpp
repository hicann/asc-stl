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

#include <asc/std/expected>
#include <utility>

template <class Left, class Right>
bool compare(const Left& a, const Right& b, bool same)
{
    return (a == b) == same && (b == a) == same && (a != b) != same && (b != a) != same;
}

int main()
{
    using asc::std::expected;
    using asc::std::unexpect;
    using asc::std::unexpected;
    expected<int, int> a(7), b(8), e(unexpect, -9), f(unexpect, -8);
    expected<long, short> other(7L), bad(unexpect, short{-9});
    const unexpected<short> tag(short{-9}), different(short{-8});
    if (!compare(a, a, true) || !compare(a, b, false) || !compare(a, e, false) || !compare(e, e, true) ||
        !compare(e, f, false))
        return 1;
    if (!compare(a, other, true) || !compare(b, other, false) || !compare(e, other, false) || !compare(a, bad, false) ||
        !compare(e, bad, true) || !compare(f, bad, false))
        return 2;
    if (!compare(a, 7L, true) || !compare(b, 7L, false) || !compare(e, 7L, false) || !compare(e, tag, true) ||
        !compare(a, tag, false) || !compare(e, different, false))
        return 3;
    using std::swap;
    swap(a, e);
    const int fallback = -77;
    const auto value_or = static_cast<int (expected<int, int>::*)(const int&) const>(&expected<int, int>::value_or);
    return a.has_value() || e != 7 || (a.*value_or)(fallback) != -77 || (e.*value_or)(fallback) != 7;
}
