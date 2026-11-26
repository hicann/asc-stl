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

#include <asc/std/mdspan>
#include <type_traits>

int main()
{
    namespace s = asc::std;
    using scalar = s::extents<int>;
    s::layout_stride::mapping<scalar> zero_rank{};
    s::layout_left::mapping<scalar> column_major = zero_rank;
    s::layout_right::mapping<scalar> row_major = zero_rank;
    if (zero_rank.required_span_size() != 1 || zero_rank() != 0 || row_major() != 0 || column_major() != 0 ||
        !(row_major == zero_rank) || column_major != zero_rank)
        return 1;
    using fixed = s::extents<unsigned, 2, 3>;
    using dynamic = s::dextents<int, 2>;
    s::layout_left::mapping<fixed> fixed_columns;
    s::layout_left::mapping<dynamic> columns(dynamic(2, 3)), shorter_columns(dynamic(2, 2));
    if (!(fixed_columns == columns) || shorter_columns == fixed_columns)
        return 7;
    s::layout_right::mapping<dynamic> dynamic_rows(dynamic(2, 3));
    using strided = s::layout_stride::mapping<fixed>;
    static_assert(std::is_base_of_v<strided::base::base, strided::base>);
    strided canonical{}, converted(dynamic_rows);
    static_assert(strided::is_always_unique() && !strided::is_always_exhaustive() && strided::is_always_strided());
    if (converted(1, 2) != 5 || canonical.stride(0) != 3 || canonical.stride(1) != 1 || !(dynamic_rows == converted) ||
        dynamic_rows != canonical)
        return 2;
    auto& strides = canonical.strides_m();
    const strided& view = canonical;
    if (&strides != &view.strides_m() || strides[0] != 3 || strides[1] != 1)
        return 4;
    strides[0] = 4;
    if (canonical(1, 2) != 6 || canonical.required_span_size() != 7)
        return 5;
    strided padded(canonical);
    canonical = converted;
    if (padded(1, 2) != 6 || canonical(1, 2) != 5)
        return 6;
    int first = 12, second = -1;
    s::mdspan<int, scalar> a(&first), b(&second), copied(a);
    using s::swap;
    swap(a, b);  // NOLINT(build/include_what_you_use)
    return a.data_handle() == &second && b.data_handle() == &first && copied() == 12 && a() == -1 ? 0 : 3;
}
