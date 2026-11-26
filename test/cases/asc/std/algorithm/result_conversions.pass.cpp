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

#include <asc/std/algorithm>
#include <asc/std/type_traits>
#include <cassert>

namespace ranges = asc::std::ranges;

struct token {
    int value;
    operator int() const&
    {
        return value;
    }
    operator int() &&
    {
        return -value;
    }
};

struct move_only {
    operator int() const& = delete;
    operator int() &&
    {
        return 1;
    }
};

int main()
{
    const ranges::in_fun_result<token, token> fun{{1}, {2}};
    ranges::in_fun_result<int, int> copied_fun = fun;
    ranges::in_fun_result<int, int> moved_fun = ranges::in_fun_result<token, token>{{3}, {4}};
    assert(copied_fun.in == 1 && copied_fun.fun == 2);
    assert(moved_fun.in == -3 && moved_fun.fun == -4);

    const ranges::in_in_out_result<token, token, token> merged{{2}, {3}, {4}};
    ranges::in_in_out_result<long, int, long> copied_merged = merged;
    ranges::in_in_out_result<long, int, long> moved_merged =
        ranges::in_in_out_result<token, token, token>{{4}, {5}, {6}};
    assert(copied_merged.in1 == 2 && copied_merged.in2 == 3 && copied_merged.out == 4);
    assert(moved_merged.in1 == -4 && moved_merged.in2 == -5 && moved_merged.out == -6);

    const ranges::in_out_out_result<token, token, token> split{{7}, {8}, {9}};
    ranges::in_out_out_result<int, long, int> copied_split = split;
    ranges::in_out_out_result<int, long, int> moved_split =
        ranges::in_out_out_result<token, token, token>{{8}, {9}, {10}};
    assert(copied_split.in == 7 && copied_split.out1 == 8 && copied_split.out2 == 9);
    assert(moved_split.in == -8 && moved_split.out1 == -9 && moved_split.out2 == -10);

    const ranges::in_out_result<token, token> out{{11}, {12}};
    const ranges::in_out_result<int, int> copied_out = out;
    const ranges::in_out_result<int, int> moved_out = ranges::in_out_result<token, token>{{13}, {14}};
    assert(copied_out.in == 11 && copied_out.out == 12);
    assert(moved_out.in == -13 && moved_out.out == -14);

    using source = ranges::in_out_result<token, move_only>;
    using target = ranges::in_out_result<int, int>;
    static_assert(!asc::std::is_convertible_v<const source&, target>);
    static_assert(asc::std::is_convertible_v<source&&, target>);
}
