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

#include <asc/std/version>
#include <asc/std/source_location>
#include <asc/std/type_traits>
#include <asc/std/bit>
#include <asc/std/utility>

#include "support/std_feature_semantics.h"

static_assert(CANN_ASC_STL_HAS_CONCEPT_PREDICATES && CANN_ASC_STL_HAS_SPAN && CANN_ASC_STL_HAS_TO_ARRAY);
static_assert(CANN_ASC_STL_HAS_MDSPAN && CANN_ASC_STL_HAS_SUBMDSPAN && CANN_ASC_STL_HAS_EXPECTED);
static_assert(CANN_ASC_STL_HAS_OPTIONAL_REFERENCE && CANN_ASC_STL_HAS_INPLACE_VECTOR && CANN_ASC_STL_HAS_PHILOX);
static_assert(CANN_ASC_STL_HAS_ALLOCATE_AT_LEAST && CANN_ASC_STL_HAS_FORMAT_TO_N_RESULT);
#if defined(__cpp_concepts) && __cpp_concepts >= 201907L
static_assert(CANN_ASC_STL_HAS_NATIVE_CONCEPTS);
#else
static_assert(!CANN_ASC_STL_HAS_NATIVE_CONCEPTS);
#endif
#if defined(__cpp_consteval)
static_assert(CANN_ASC_STL_HAS_FORMAT);
#else
static_assert(!CANN_ASC_STL_HAS_FORMAT);
#endif

int main()
{
    static_assert(CANN_ASC_STL_HAS_SOURCE_LOCATION && CANN_ASC_STL_HAS_UNREACHABLE);
    static_assert(CANN_ASC_STL_HAS_TYPE_IDENTITY && CANN_ASC_STL_HAS_ENDIAN);
    static_assert(CANN_ASC_STL_DETAIL_LIB_type_identity == 201806L);
    static_assert(CANN_ASC_STL_DETAIL_LIB_endian == 201907L);
    static_assert(CANN_ASC_STL_DETAIL_LIB_unreachable == 202202L);
    static_assert(asc::std::is_same_v<asc::std::type_identity_t<int>, int>);
    static_assert(asc::std::source_location::current().line() != 0);
    static_assert(asc::std::endian::little != asc::std::endian::big);
#if CANN_ASC_STL_HAS_IS_CONSTANT_EVALUATED
    static_assert(asc::std::is_constant_evaluated());
#endif
    const auto unavailable = &asc::std::unreachable;
    (void)unavailable;
    static_assert(std_feature_tests::semantics());
    static_assert(std_feature_tests::numeric_semantics());
    return std_feature_tests::semantics() && std_feature_tests::numeric_semantics() &&
            std_feature_tests::storage_semantics() ?
        0 :
        1;
}
