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

#ifndef ASC_STL_TEST_SUPPORT_ZIP_PIPELINE_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_ZIP_PIPELINE_SEMANTICS_H

#include <asc/std/algorithm>
#include <asc/std/ranges>
#include <asc/std/span>
#include <asc/std/tuple>
#include <asc/std/utility>

namespace asc_stl_zip_pipeline_test {
struct scale_score {
    CANN_ASC_STL_API constexpr int operator()(int score) const
    {
        return score * 2;
    }
};
struct add_correction {
    template <class Pair>
    CANN_ASC_STL_API constexpr int operator()(Pair values) const
    {
        return asc::std::get<0>(values) + asc::std::get<1>(values);
    }
};

CANN_ASC_STL_API constexpr int evaluate()
{
    using ReferenceTuple = asc::std::tuple<int, int&>;
    using ValueTuple = asc::std::tuple<int, int>;
    static_assert(asc::std::is_convertible_v<ReferenceTuple&&, ValueTuple>);
    static_assert(asc::std::is_constructible_v<ValueTuple, ReferenceTuple&&>);
    int score = 7;
    ReferenceTuple row(2, score);
    ValueTuple snapshot = asc::std::move(row);  // NOLINT(build/include_what_you_use): asc/std/utility provides move.
    score = 9;
    if (asc::std::get<0>(snapshot) != 2 || asc::std::get<1>(snapshot) != 7) {
        return 5;
    }
    int scores[] = {1, 6, -4, 3, 8};
    int correction[] = {0, -2, 7, 0};
    int output[5] = {-99, -99, -99, -99, -99};
    auto scaled = scores | asc::std::ranges::views::transform(scale_score{});
    static_assert(asc::std::ranges::random_access_range<decltype(scaled)>);
    auto paired = asc::std::ranges::views::zip(scaled, correction);
    using Iterator = decltype(paired.begin());
    static_assert(asc::std::default_initializable<Iterator>);
    static_assert(asc::std::ranges::random_access_range<decltype(paired)>);
    static_assert(asc::std::is_same_v<typename asc::std::iterator_traits<Iterator>::iterator_category,
        asc::std::input_iterator_tag>);
    if (Iterator{} != Iterator{}) {
        return 1;
    }
    const auto result = asc::std::ranges::transform(paired, output, add_correction{});
    if (result.out != output + 4 || output[0] != 2 || output[1] != 10 || output[2] != -1 || output[3] != 6 ||
        output[4] != -99) {
        return 2;
    }
    auto empty = asc::std::ranges::views::zip(asc::std::span<int>(scores, 0), correction);
    if (asc::std::ranges::transform(empty, output, add_correction{}).out != output || output[0] != 2) {
        return 3;
    }
    auto raw = asc::std::ranges::views::zip(scores, correction);
    auto references = *raw.begin();
    asc::std::get<0>(references) = 9;
    const auto const_raw = raw;
    if (scores[0] != 9 || const_raw.size() != 4 || asc::std::get<1>(*const_raw.begin()) != 0) {
        return 4;
    }
    return 0;
}
}  // namespace asc_stl_zip_pipeline_test

#endif  // ASC_STL_TEST_SUPPORT_ZIP_PIPELINE_SEMANTICS_H
