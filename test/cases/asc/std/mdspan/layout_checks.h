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

#ifndef ASC_STL_TEST_MDSPAN_LAYOUT_H
#define ASC_STL_TEST_MDSPAN_LAYOUT_H

#include <asc/std/mdspan>

namespace asc_stl_test_mdspan {
template <class Layout, class OtherLayout>
CANN_ASC_STL_API bool convert_rank_one(int n)
{
    namespace s = asc::std;
    using fixed = s::extents<int, 7>;
    using dynamic = s::dextents<long, 1>;
    typename Layout::template mapping<fixed> initial{};
    typename Layout::template mapping<dynamic> same(initial);
    typename OtherLayout::template mapping<dynamic> other(initial);
    typename Layout::template mapping<fixed> from_same(same);
    typename Layout::template mapping<fixed> from_other(other);
    s::layout_stride::mapping<dynamic> stride(other);
    typename Layout::template mapping<dynamic> from_stride(stride);
    typename Layout::template mapping<fixed> narrowed_stride(stride);
    auto copied = same;
    typename Layout::template mapping<dynamic> shorter{dynamic(n - 1)};
    same = shorter;
    return same.extents().extent(0) == n - 1 && copied.extents().extent(0) == n && other(n - 1) == n - 1 &&
        from_same.is_unique() && from_other.is_exhaustive() && from_stride.is_strided() &&
        narrowed_stride.required_span_size() == n && narrowed_stride.stride(0) == 1 &&
        decltype(initial)::is_always_unique() && decltype(initial)::is_always_strided() &&
        decltype(initial)::is_always_exhaustive();
}

CANN_ASC_STL_API int check_layout(int seed)
{
    namespace s = asc::std;
    if (!convert_rank_one<s::layout_left, s::layout_right>(seed) ||
        !convert_rank_one<s::layout_right, s::layout_left>(seed))
        return 1;
    alignas(32) int raw[28]{};
    s::aligned_accessor<int, 32> aligned(s::default_accessor<int>{});
    s::aligned_accessor<const int, 16> weak(aligned);
    static_assert(!s::is_convertible_v<decltype(weak), s::default_accessor<int>>);
    s::default_accessor<const int> ordinary = aligned;
    s::default_accessor<const int> cv(s::default_accessor<int>{});
    if (aligned.offset(raw, 3) != raw + 3 || &weak.access(raw, 5) != raw + 5 || ordinary.offset(raw, 2) != raw + 2 ||
        &cv.access(raw, 6) != raw + 6)
        return 2;
    using dyn = s::dextents<unsigned, 2>;
    using partial = s::extents<unsigned, 3, s::dynamic_extent>;
    s::array<int, 2> shape{{3, seed}};
    s::array<int, 1> dynamic_extent{{seed}};
    s::span<int, 2> full(shape);
    s::span<int, 1> tail(dynamic_extent);
    partial a(shape), b(dynamic_extent), c(full), d(tail);
    if (!(a == b && b == c && c == d) || d.rank_dynamic() != 1 || d.static_extent(0) != 3)
        return 3;
    dyn dimensions(a);
    partial narrowed(dimensions);
    s::array<int, 2> stride{{9, 1}};
    s::layout_stride::mapping<partial> padded(narrowed, s::span<int, 2>(stride));
    auto padded_copy = padded;
    padded_copy = padded;
    if (!(padded_copy == padded) || padded.strides()[0] != 9 || padded.is_exhaustive() ||
        padded.required_span_size() != 25 || !padded.is_unique() || !padded.is_strided())
        return 4;
    s::mdspan<int, partial> first(raw, dynamic_extent), second(raw, shape);
    s::mdspan<int, partial> third(raw, full), fourth(raw + 1, tail);
    s::mdspan<const int, dyn> converted = first;
    s::mdspan<const int, partial> explicit_back(converted);
    s::mdspan<const int, dyn> default_view;
    if (default_view.data_handle() != nullptr || default_view.extent(0) != 0 || default_view.extent(1) != 0 ||
        !default_view.empty())
        return 7;
    default_view = explicit_back;
    auto moved = static_cast<decltype(first)&&>(first);
    if (fourth.data_handle() != raw + 1 || moved.data_handle() != raw)
        return 8;
    fourth = static_cast<decltype(moved)&&>(moved);
    s::mdspan<const int, partial, s::layout_stride, decltype(weak)> with_accessor(raw, padded, weak);
    if (default_view.extent(1) != static_cast<unsigned>(seed) || &default_view(2, 6) != raw + 20 ||
        &second(1, 6) != &third(1, 6) || &third(1, 6) != &fourth(1, 6) || &with_accessor(2, 6) != raw + 24)
        return 5;
    auto sub = s::submdspan_mapping(padded, s::full_extent, 4);
    auto ext = s::submdspan_extents(a, s::full_extent, 4);
    return sub.offset == 4 && sub.mapping.stride(0) == 9 && sub.mapping.extents() == ext && ext.extent(0) == 3 ? 0 : 6;
}
}  // namespace asc_stl_test_mdspan

#endif  // ASC_STL_TEST_MDSPAN_LAYOUT_H
