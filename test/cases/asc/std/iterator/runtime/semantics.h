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

#ifndef ASC_STL_TEST_ASC_STD_ITERATOR_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_ASC_STD_ITERATOR_RUNTIME_SEMANTICS_H

#include "../../../../../support/b024_semantics.h"

namespace asc_stl_b024_runtime {
template <class OutputPointer, class CursorPointer>
CANN_ASC_STL_API void evaluate(OutputPointer output, CursorPointer cursor)
{
    output[0] = asc_stl_b024_test::evaluate();
    // Deterministic device randomness and caller-owned work claiming on top of
    // the shared payload: the second LCG draw after seeding must stay
    // reproducible, and a serialized cursor claim must tile its range.
    asc::std::minstd_rand engine;
    engine();
    output[1] = engine() != 182605794u;
    __UINT64_TYPE__ begin = 0;
    __UINT64_TYPE__ end = 0;
    int claims = 0;
    __UINT64_TYPE__ expected = 0;
    while (cursor->try_claim(begin, end)) {
        if (begin != expected) {
            output[1] += 2;
            break;
        }
        expected = end;
        ++claims;
    }
    output[1] += (claims != 3 || expected != 10) * 4;
}
}  // namespace asc_stl_b024_runtime

#endif  // ASC_STL_TEST_ASC_STD_ITERATOR_RUNTIME_SEMANTICS_H
