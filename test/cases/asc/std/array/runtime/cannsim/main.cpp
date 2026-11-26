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

#include <cstdlib>
#include <iostream>
#include <string_view>

#include "../semantics.h"

using asc_stl_standard_runtime::kCoreGroupCount;
using asc_stl_standard_runtime::kGroupCount;
using asc_stl_standard_runtime::test_data;

int main()
{
    const char* groups[] = {
        "calendar",
        "algorithms",
        "function_objects",
        "value_types",
        "ranges",
        "layouts",
        "bytes_and_complex",
        "text",
        "memory",
        "numeric",
        "random",
#if defined(ASC_STL_STANDARD_RUNTIME_SIMT)
        "sequences",
        "ordered_set",
        "unordered_set",
        "unordered_map",
        "scoped_allocator",
        "adaptors",
        "synchronization",
#endif
    };
    static_assert(sizeof(groups) / sizeof(groups[0]) == kGroupCount);
    test_data data{};
    data.seed = 19;
    for (int& failure : data.failures)
        failure = -1;

    int selected = -1;
#if defined(ASC_STL_STANDARD_RUNTIME_PROFILES)
    const char* name = std::getenv("ASC_STL_STANDARD_RUNTIME_CASE");
    if (name != nullptr) {
        for (int i = kCoreGroupCount; i < kGroupCount; ++i) {
            if (name == std::string_view(groups[i]))
                selected = i;
        }
    }
    if (selected < 0) {
        std::cerr << "Unknown standard library cannsim case\n";
        return 1;
    }
#endif

    bool passed = asc_stl_standard_runtime::run(data, selected);
    if (!passed) {
        std::cerr << "Unable to run the standard library test kernel\n";
        return 1;
    }
    const int last = selected < 0 ? kCoreGroupCount : 1;
    for (int i = 0; i < last; ++i) {
        if (data.failures[i] != 0) {
            std::cerr << groups[selected < 0 ? i : selected] << " returned " << data.failures[i] << '\n';
            passed = false;
        }
    }
    if (passed)
        std::cout << "ASC_STL_STANDARD_RUNTIME_PASS " << (selected < 0 ? "core" : groups[selected]) << '\n';
    return passed ? 0 : 1;
}
