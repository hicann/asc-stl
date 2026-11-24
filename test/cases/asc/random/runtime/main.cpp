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
#include <vector>
#include "launch.h"
#include "vectors.h"
#if defined(ASC_STL_RANDOM_SIMULATION)
#include "simulation_runtime.h"
using random_runtime = random_simulation_runtime;
#else
#include "../../../../support/hardware_runtime.h"
using random_runtime = asc_stl_test::hardware_runtime;
#endif

bool verify(const std::vector<std::uint64_t>& actual, unsigned first, unsigned count)
{
    for (unsigned i = 0; i != count; ++i) {
        const auto offset = i * random_output_stride;
        if (actual[offset] != random_vectors[first + i].first ||
            actual[offset + 1] != random_vectors[first + i].second || actual[offset + 2] != 0) {
            std::cerr << "Mismatch at " << i << " first=" << actual[offset] << " second=" << actual[offset + 1]
                      << " status=" << actual[offset + 2] << '\n';
            return false;
        }
    }
    return true;
}

struct vector_range {
    unsigned first;
    unsigned count;
};

vector_range selected_vectors()
{
#if defined(ASC_STL_RANDOM_SIMULATION)
    const char* selected = std::getenv("ASC_STL_RANDOM_SEED_INDEX");
    if (selected != nullptr) {
        if (selected[0] < '0' || selected[0] > '5' || selected[1] != '\0')
            return {0, 0};
        return {static_cast<unsigned>(selected[0] - '0') * 9, 9};
    }
#endif
    return {0, sizeof(random_vectors) / sizeof(random_vectors[0])};
}

int main()
{
    const auto selected = selected_vectors();
    if (selected.count == 0)
        return 2;
    const unsigned count = selected.count;
    std::vector<std::uint64_t> input;
    for (unsigned i = selected.first; i != selected.first + count; ++i) {
        const auto& item = random_vectors[i];
        input.push_back(item.seed);
        input.push_back(item.skip);
    }
    std::vector<std::uint64_t> actual(count * random_output_stride, 0xbadc0ffeeULL);
    const auto input_bytes = input.size() * sizeof(input[0]);
    const auto output_bytes = actual.size() * sizeof(actual[0]);
    random_runtime runtime;
    std::uint64_t* device_input = nullptr;
    std::uint64_t* output = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_input), input_bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&output), output_bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
        passed = aclrtMemcpy(device_input, input_bytes, input.data(), input_bytes, ACL_MEMCPY_HOST_TO_DEVICE) ==
                ACL_SUCCESS &&
            aclrtMemcpy(output, output_bytes, actual.data(), output_bytes, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    }
    if (passed && runtime.ready()) {
        launch_random(output, device_input, count, stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(actual.data(), output_bytes, output, output_bytes, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        passed = passed && verify(actual, selected.first, count);
    }
    if (output)
        passed = runtime.free_device(output) == ACL_SUCCESS && passed;
    if (device_input)
        passed = runtime.free_device(device_input) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    if (passed)
        std::cout << "ASC_STL_RANDOM_RUNTIME_PASS comparisons=" << count * 2 << '\n';
    return passed ? 0 : 1;
}
