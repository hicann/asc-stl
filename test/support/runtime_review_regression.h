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

#ifndef ASC_STL_TEST_RUNTIME_REVIEW_REGRESSION_H
#define ASC_STL_TEST_RUNTIME_REVIEW_REGRESSION_H

#include <asc/numeric>
#include <asc/utility>
#include <asc/std/algorithm>

namespace asc_stl_runtime_review {
struct count_static_calls {
    int* calls;
    template <class Index>
    CANN_ASC_STL_API void operator()(Index) const
    {
        ++*calls;
    }
};
struct increment_value {
    CANN_ASC_STL_API void operator()(int& value) const
    {
        ++value;
    }
};
CANN_ASC_STL_API bool nonpositive_counts()
{
    int calls = 0;
    asc::static_for<int, -1>(count_static_calls{&calls});
    int value = 7;
    const auto result = asc::std::ranges::for_each_n(&value, -__PTRDIFF_MAX__ - 1, increment_value{});
    return calls == 0 && value == 7 && result.in == &value;
}
CANN_ASC_STL_API bool checked_narrow_product()
{
    const auto overflow = asc::mul_overflow<unsigned short>(65535u, 65535u);
    const auto exact = asc::mul_overflow<unsigned short>(255u, 257u);
    return nonpositive_counts() && overflow.overflow && overflow.value == 1u && !exact.overflow &&
        exact.value == 65535u && asc::saturating_mul<unsigned short>(65535u, 65535u) == 65535u;
}
}  // namespace asc_stl_runtime_review

#endif  // ASC_STL_TEST_RUNTIME_REVIEW_REGRESSION_H
