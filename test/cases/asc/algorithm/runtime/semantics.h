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

#ifndef ASC_STL_TEST_ASC_ALGORITHM_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_ASC_ALGORITHM_RUNTIME_SEMANTICS_H

#include "../../../../support/b023_semantics.h"

namespace asc_stl_b023_runtime {
template <class OutputPointer>
CANN_ASC_STL_API void evaluate(OutputPointer output)
{
    int failures = asc_stl_b023_test::evaluate_core();
    int aligned = 23;
    failures += asc::std::__runtime_assume_aligned(&aligned, alignof(int)) != &aligned;
    alignas(int) unsigned char raw[sizeof(int) * 2]{};
    int source[] = {7, 8};
    auto* values = reinterpret_cast<int*>(raw);
    failures += asc::std::uninitialized_copy(source, source + 2, values) != values + 2;
    failures += values[0] != 7 || values[1] != 8;
    asc::std::destroy(values, values + 2);
    output[0] = failures;
}
}  // namespace asc_stl_b023_runtime

#endif  // ASC_STL_TEST_ASC_ALGORITHM_RUNTIME_SEMANTICS_H
