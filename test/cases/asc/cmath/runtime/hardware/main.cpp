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

#include <acl/acl.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include "../../../../../support/cmath_runtime.h"
#include "../../../../../support/cmath_trig_goldens.h"
#include "launch.h"

namespace {

std::vector<float> make_reference()
{
    const auto& goldens = asc_stl_cmath_test::trig_goldens;
    std::vector<float> reference;
    reference.reserve(sizeof(goldens) / sizeof(float));
    for (const auto& triple : goldens) {
        for (float value : triple) {
            reference.push_back(value);
        }
    }
    return reference;
}

bool select_vectors(unsigned total, unsigned& first, unsigned& count)
{
    const char* first_text = std::getenv("ASC_STL_CMATH_FIRST_VECTOR");
    const char* count_text = std::getenv("ASC_STL_CMATH_VECTOR_COUNT");
    char* end = nullptr;
    if (first_text) {
        const unsigned long value = std::strtoul(first_text, &end, 10);
        if (end == first_text || *end != '\0' || value >= total)
            return false;
        first = static_cast<unsigned>(value);
    }
    count = total - first;
    if (count_text) {
        const unsigned long value = std::strtoul(count_text, &end, 10);
        if (end == count_text || *end != '\0' || value > count)
            return false;
        count = static_cast<unsigned>(value);
    }
    return true;
}

}  // namespace

int main()
{
    asc_stl_cmath_test::runtime runtime;
    float* result = nullptr;
    unsigned long long* inputs = nullptr;
    float* trig = nullptr;
    aclrtStream stream = nullptr;
    const unsigned long long integers[] = {~0ULL, 7};
    const auto& goldens = asc_stl_cmath_test::trig_goldens;
    unsigned first = 0;
    unsigned count = 0;
    if (!select_vectors(sizeof(goldens) / sizeof(goldens[0]), first, count))
        return 2;
#if defined(ASC_STL_B026_SIMD)
    const unsigned participants = 1;
#else
    const unsigned participants = count + 1;
#endif
    const unsigned result_bytes = participants * 3 * sizeof(float);
    std::vector<float> cells(participants * 3, -1.0F);
    auto reference = make_reference();
    const char* injection = std::getenv("ASC_STL_CMATH_INJECT_MISMATCH");
    if (injection && std::strcmp(injection, "1") == 0) {
        if (count < 3)
            return 2;
        reference[3 * (first + count / 2) + 2] += 1.0F;
    }
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&result), result_bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&inputs), sizeof(integers), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&trig), sizeof(goldens), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
        passed =
            aclrtMemcpy(result, result_bytes, cells.data(), result_bytes, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
            aclrtMemcpy(inputs, sizeof(integers), integers, sizeof(integers), ACL_MEMCPY_HOST_TO_DEVICE) ==
                ACL_SUCCESS &&
            aclrtMemcpy(trig, sizeof(goldens), reference.data(), sizeof(goldens), ACL_MEMCPY_HOST_TO_DEVICE) ==
                ACL_SUCCESS;
    }
    if (passed && runtime.ready()) {
#if defined(ASC_STL_B026_SIMD)
        launch_asc_stl_b026_cmath_simd(result, inputs, trig + 3 * first, count, stream);
#else
        launch_asc_stl_b026_cmath_simt(result, inputs, trig + 3 * first, count, stream);
#endif
        float failures = 0;
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(cells.data(), result_bytes, result, result_bytes, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        for (unsigned i = 0; i < participants; ++i) {
            failures += cells[3 * i] != 0.0F;
        }
        std::cout << "b026_cmath_failures=" << failures << " trig_vectors=" << count << '\n';
        passed = passed && failures == 0;
    }
    if (trig)
        passed = runtime.free_device(trig) == ACL_SUCCESS && passed;
    if (inputs)
        passed = runtime.free_device(inputs) == ACL_SUCCESS && passed;
    if (result)
        passed = runtime.free_device(result) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    if (passed)
        std::cout << "ASC_STL_B026_CMATH_HARDWARE_PASS\n";
    return passed ? 0 : 1;
}
