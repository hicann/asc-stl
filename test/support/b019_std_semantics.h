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

#ifndef ASC_STL_TEST_B019_STD_SEMANTICS_H
#define ASC_STL_TEST_B019_STD_SEMANTICS_H

#include <asc/std/__compare/ordering.h>
#include <asc/std/__execution/execution_policy.h>
#include <asc/std/__execution/type_traits.h>
#include <asc/std/__iterator/indirectly_comparable.h>
#include <asc/std/__iterator/mergeable.h>
#include <asc/std/__iterator/move_iterator.h>
#include <asc/std/__iterator/permutable.h>
#include <asc/std/__type_traits/aligned_storage.h>

namespace asc_stl_b019_test {

CANN_ASC_STL_API int evaluate_std() noexcept
{
    static_assert(asc::std::is_execution_policy_v<asc::std::execution::sequenced_policy>);
    static_assert(asc::std::is_execution_policy_v<asc::std::execution::parallel_policy>);
    static_assert(!asc::std::is_execution_policy_v<int>);
    static_assert(sizeof(asc::std::aligned_storage_t<7, 4>) == 8);
    static_assert(alignof(asc::std::aligned_storage_t<7, 4>) == 4);
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
    static_assert(asc::std::indirectly_comparable<int*, int*, asc::std::ranges::equal_to>);
    static_assert(asc::std::permutable<int*>);
    static_assert(asc::std::mergeable<int*, int*, int*>);
#endif
    int values[] = {1, 2, 3};
    auto iterator = asc::std::make_move_iterator(values);
    int failures = *iterator != 1;
    ++iterator;
    failures += iterator.base() != values + 1;
    failures += asc::std::partial_ordering::less.value() != -1;
    failures += !(asc::std::strong_ordering::equal == asc::std::strong_ordering::equivalent);
    failures += !(asc::std::weak_ordering::less < 0);
    failures += !(0 < asc::std::partial_ordering::greater);
    failures += asc::std::partial_ordering::unordered >= 0;
    return failures;
}

}  // namespace asc_stl_b019_test

#endif  // ASC_STL_TEST_B019_STD_SEMANTICS_H
