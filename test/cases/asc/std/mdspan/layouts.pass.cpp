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

namespace {

namespace ast = asc::std;

using mixed = ast::extents<int, 2, ast::dynamic_extent>;
using dense = ast::mdspan<int, mixed>;
using strided = ast::mdspan<int, mixed, ast::layout_stride>;
using plain_accessor = ast::default_accessor<int>;
using aligned = ast::aligned_accessor<int, 16>;

static_assert(std::is_same_v<ast::dims<2, int>, ast::dextents<int, 2>>);
static_assert(std::is_same_v<mixed::index_type, int>);
static_assert(std::is_same_v<mixed::size_type, unsigned>);
static_assert(std::is_same_v<mixed::rank_type, ast::size_t>);
static_assert(mixed::rank() == 2 && mixed::rank_dynamic() == 1);
static_assert(mixed::static_extent(0) == 2 && mixed::static_extent(1) == ast::dynamic_extent);
static_assert(std::is_same_v<dense::index_type, int> && std::is_same_v<dense::size_type, unsigned>);
static_assert(std::is_same_v<dense::rank_type, mixed::rank_type>);
static_assert(std::is_same_v<dense::element_type, int> && std::is_same_v<dense::value_type, int>);
static_assert(std::is_same_v<dense::reference, int&> && std::is_same_v<dense::data_handle_type, int*>);
static_assert(std::is_same_v<dense::layout_type, ast::layout_right>);
static_assert(std::is_same_v<dense::extents_type, mixed>);
static_assert(std::is_same_v<dense::accessor_type, plain_accessor>);
static_assert(std::is_same_v<dense::mapping_type, ast::layout_right::mapping<mixed>>);
static_assert(dense::rank() == 2 && dense::rank_dynamic() == 1);
static_assert(dense::static_extent(0) == 2 && dense::static_extent(1) == ast::dynamic_extent);
static_assert(dense::is_always_strided() && dense::is_always_unique() && dense::is_always_exhaustive());
static_assert(strided::is_always_strided() && strided::is_always_unique() && !strided::is_always_exhaustive());
static_assert(std::is_same_v<plain_accessor::data_handle_type, int*>);
static_assert(std::is_same_v<plain_accessor::element_type, int>);
static_assert(std::is_same_v<plain_accessor::offset_policy, plain_accessor>);
static_assert(std::is_same_v<plain_accessor::reference, int&>);
static_assert(aligned::byte_alignment == 16);
static_assert(std::is_same_v<aligned::data_handle_type, int*> && std::is_same_v<aligned::element_type, int>);
static_assert(std::is_same_v<aligned::offset_policy, plain_accessor> && std::is_same_v<aligned::reference, int&>);

bool check_access()
{
    alignas(16) int storage[] = {3, 4, 5, 6, 7, 8, 9, 10};
    const plain_accessor basic{};
    const ast::default_accessor<const int> constant{basic};
    const aligned aligned_accessor{};
    if (basic.offset(storage, 3) != storage + 3 || &basic.access(storage, 2) != storage + 2 ||
        constant.access(storage, 4) != 7 || aligned_accessor.offset(storage, 1) != storage + 1) {
        return false;
    }

    const dense empty{storage, mixed{0}};
    dense view{storage, mixed{3}};
    if (!empty.empty() || empty.size() != 0 || view.empty() || view.size() != 6 || view.data_handle() != storage ||
        view.extent(0) != 2 || view.extent(1) != 3 || view.extents().extent(1) != 3 || !view.is_strided() ||
        !view.is_exhaustive() || !view.is_unique()) {
        return false;
    }
    view.accessor().access(view.data_handle(), 4) = 41;
    if (storage[4] != 41) {
        return false;
    }
    view = dense{storage + 2, mixed{2}};
    return view.data_handle() == storage + 2 && view.extent(1) == 2 && view.size() == 4 &&
        view.accessor().access(view.data_handle(), 0) == 5;
}

constexpr bool check_subviews()
{
    const mixed shape{5};
    const auto clipped = ast::submdspan_extents(shape, ast::full_extent_t{}, ast::pair<int, int>{1, 4});
    const auto dropped = ast::submdspan_extents(shape, 1, ast::full_extent_t{});
    const ast::layout_right::mapping<mixed> base{shape};
    const auto section = submdspan_mapping(base, ast::full_extent_t{}, ast::pair<int, int>{1, 4});
    const ast::submdspan_mapping_result<decltype(section.mapping)> independent{section.mapping, section.offset};
    return clipped.extent(0) == 2 && clipped.extent(1) == 3 && dropped.rank() == 1 && dropped.extent(0) == 5 &&
        independent.offset == 1 && independent.mapping(1, 2) == 7 && independent.mapping.required_span_size() == 8 &&
        !independent.mapping.is_exhaustive();
}
static_assert(check_subviews());

bool check_strides()
{
    int storage[16]{};
    const auto contiguous = ast::layout_stride::mapping<mixed>{mixed{3}, ast::array<int, 2>{3, 1}};
    const auto with_gap = ast::layout_stride::mapping<mixed>{mixed{3}, ast::array<int, 2>{5, 1}};
    const strided compact{storage, contiguous};
    const strided padded{storage, with_gap};
    return compact.is_exhaustive() && padded.is_unique() && padded.is_strided() && !padded.is_exhaustive() &&
        padded.mapping().required_span_size() == 8 && compact.mapping().required_span_size() == 6 &&
        padded.mapping()(1, 2) == 7;
}

}  // namespace

int main()
{
    return check_access() && check_strides() ? 0 : 1;
}
