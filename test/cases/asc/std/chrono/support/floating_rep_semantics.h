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

#ifndef ASC_STL_CHRONO_TEST_FLOATING_REP_SEMANTICS_H
#define ASC_STL_CHRONO_TEST_FLOATING_REP_SEMANTICS_H

#include <asc/std/chrono>
#include <asc/std/type_traits>

namespace asc_stl_chrono_trait_test {

struct customized_rep {
    float value;
    CANN_ASC_STL_API constexpr customized_rep(float input = 0) noexcept : value(input)
    {}
};

struct ordinary_rep {
    float value;
    CANN_ASC_STL_API constexpr ordinary_rep(float input = 0) noexcept : value(input)
    {}
};

}  // namespace asc_stl_chrono_trait_test

namespace asc::std::chrono {

template <>
struct treat_as_floating_point<::asc_stl_chrono_trait_test::customized_rep> : true_type {};

}  // namespace asc::std::chrono

namespace asc_stl_chrono_trait_test {

static_assert(!asc::std::is_floating_point_v<customized_rep>);
static_assert(asc::std::chrono::treat_as_floating_point_v<customized_rep>);
static_assert(!asc::std::chrono::treat_as_floating_point_v<ordinary_rep>);
static_assert(asc::std::is_constructible_v<asc::std::chrono::duration<customized_rep>, float>);
static_assert(!asc::std::is_constructible_v<asc::std::chrono::duration<ordinary_rep>, float>);

CANN_ASC_STL_API int evaluate_custom_floating_rep()
{
    const asc::std::chrono::duration<customized_rep> value(1.5F);
    return value.count().value == 1.5F ? 0 : 1;
}

}  // namespace asc_stl_chrono_trait_test

#endif  // ASC_STL_CHRONO_TEST_FLOATING_REP_SEMANTICS_H
