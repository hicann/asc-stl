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

#include <type_traits>

#include "device_checks.h"

namespace s = asc::std;
namespace l = asc::std::linalg;

struct explicit_accessor : s::default_accessor<const float> {
    explicit explicit_accessor(s::default_accessor<float>)
    {}
};

using matrix_extents = s::extents<int, 2, 3>;
using transpose_layout = l::layout_transpose<s::layout_right>;
using transpose_mapping = transpose_layout::mapping<matrix_extents>;
static_assert(std::is_same_v<transpose_mapping::extents_type, matrix_extents>);
static_assert(
    std::is_same_v<transpose_mapping::index_type, int> && std::is_same_v<transpose_mapping::size_type, unsigned>);
static_assert(std::is_same_v<transpose_mapping::rank_type, matrix_extents::rank_type>);
static_assert(std::is_same_v<transpose_mapping::layout_type, transpose_layout>);
bool accessor_conversions()
{
    using a = s::default_accessor<float>;
    using b = s::default_accessor<const float>;
    static_assert(std::is_default_constructible_v<l::scaled_accessor<int, a>>);
    static_assert(std::is_convertible_v<l::scaled_accessor<int, a>, l::scaled_accessor<float, b>>);
    static_assert(!std::is_convertible_v<l::scaled_accessor<int, a>, l::scaled_accessor<float, explicit_accessor>>);
    static_assert(std::is_convertible_v<l::conjugated_accessor<a>, l::conjugated_accessor<b>>);
    static_assert(!std::is_convertible_v<l::conjugated_accessor<a>, l::conjugated_accessor<explicit_accessor>>);
    const l::scaled_accessor<int, a> zero_initialized{};
    const l::scaled_accessor<int, a> scaled{-2, a{}};
    const l::scaled_accessor<float, b> implicit_scaled = scaled;
    const l::scaled_accessor<float, explicit_accessor> explicit_scaled(scaled);
    const l::conjugated_accessor<a> conj{};
    const l::conjugated_accessor<b> implicit_conj = conj;
    const l::conjugated_accessor<explicit_accessor> explicit_conj(conj);
    float values[] = {-3, 1, -2};
    return zero_initialized.access(values, 1) == 0 && implicit_scaled.access(values, 2) == 4 &&
        explicit_scaled.access(values, 0) == 6 && implicit_conj.access(values, 2) == -2 &&
        explicit_conj.access(values, 0) == -3;
}

int main()
{
    return accessor_conversions() ? asc_stl_test_linalg::check() : 6;
}
