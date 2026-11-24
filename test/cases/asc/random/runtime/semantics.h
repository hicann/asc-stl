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

#ifndef ASC_STL_TEST_RANDOM_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_RANDOM_RUNTIME_SEMANTICS_H

#include "../../../../support/random_semantics.h"
#include "launch.h"

namespace asc_stl_random_runtime {

template <class Output>
CANN_ASC_STL_API void evaluate(Output output, asc::std::uint64_t seed, unsigned long long skip)
{
    asc::pcg64 engine(seed);
    engine.discard(skip);
    asc::pcg64 copy(engine);  // NOLINT(build/include_what_you_use)
    const auto first = engine();
    const auto second = engine();
    const auto copy_first = copy();
    const auto copy_second = copy();
    unsigned failures = first != copy_first || second != copy_second || engine != copy;
    copy = engine;
    failures += copy != engine;
    copy.seed(seed);
    failures += copy != asc::pcg64(seed);
    failures += !asc_stl_random_test::composition(seed);
    failures += !asc_stl_random_test::short_discard(seed, static_cast<unsigned>(skip & 63U));
    output[0] = first;
    output[1] = second;
    output[2] = failures;
}

}  // namespace asc_stl_random_runtime

#endif  // ASC_STL_TEST_RANDOM_RUNTIME_SEMANTICS_H
