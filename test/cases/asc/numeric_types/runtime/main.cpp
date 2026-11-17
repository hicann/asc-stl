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

#include <iostream>
#include <vector>

#include "launch.h"
#include "../reference.h"
#if defined(ASC_STL_NUMERIC_TYPES_SIMULATION)
#include "simulation_runtime.h"
using numeric_runtime = numeric_simulation_runtime;
#else
#include "../../../../support/hardware_runtime.h"
using numeric_runtime = asc_stl_test::hardware_runtime;
#endif

namespace {
numeric_parameters parameters()
{
    return {asc::from_bits<asc::float16>(0x7e15), asc::from_bits<asc::bfloat16>(0xffc1),
        asc::from_bits<asc::float8_e4m3fn>(0xff), asc::from_bits<asc::float8_e5m2>(0x7d),
        asc::from_bits<asc::float8_e8m0>(0), asc::from_bits<asc::hifloat8>(0xa5),
        asc::from_bits<asc::float4_e2m1x2>(0x83), asc::from_bits<asc::float4_e1m2x2>(0x7c),
        asc::from_bits<asc::int4x2>(0xf0), asc::from_bits<asc::int4>(0x0e)};
}

bool verify(const std::vector<unsigned>& actual, const std::vector<unsigned>& records)
{
    const auto count = records.size() / 5;
    for (std::size_t i = 0; i < count; ++i) {
        if (actual[i] != records[i * 5 + 4]) {
            std::cerr << "Mismatch at " << i << " format=" << records[i * 5] << " direction=" << records[i * 5 + 1]
                      << " option=" << records[i * 5 + 2] << " input=" << std::hex << records[i * 5 + 3]
                      << " actual=" << actual[i] << " expected=" << records[i * 5 + 4] << '\n';
            return false;
        }
    }
    std::cout << "numeric_types device comparisons=" << count
              << " invariant_failures=" << actual[numeric_invariant_base(count)] << '\n';
    for (unsigned lane = 0; lane < numeric_lanes; ++lane) {
        if (actual[numeric_invariant_base(count) + lane * numeric_cache_words] != 0)
            return false;
    }
    return true;
}
}  // namespace

int main()
{
#if defined(ASC_STL_NUMERIC_TYPES_SIMULATION)
    const auto records = numeric_types_reference::device_vectors(true);
#else
    const auto records = numeric_types_reference::device_vectors();
#endif
    const unsigned count = records.size() / 5;
    std::vector<unsigned> actual(numeric_invariant_base(count) + numeric_lanes * numeric_cache_words, 0xffffffffU);
    const auto prepared = numeric_types_host_prepare(numeric_types_reference::from_float_bits(0x3fc00000U));
    if (asc::to_bits(prepared) != 0x3e00)
        return 1;
    numeric_runtime runtime;
    unsigned* device_records = nullptr;
    unsigned* output = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_records), records.size() * 4, ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&output), actual.size() * 4, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
        passed = aclrtMemcpy(device_records, records.size() * 4, records.data(), records.size() * 4,
                     ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
            aclrtMemcpy(output, actual.size() * 4, actual.data(), actual.size() * 4, ACL_MEMCPY_HOST_TO_DEVICE) ==
                ACL_SUCCESS;
    }
    if (passed && runtime.ready()) {
        launch_numeric_types(output, device_records, count, parameters(), stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(actual.data(), actual.size() * 4, output, actual.size() * 4, ACL_MEMCPY_DEVICE_TO_HOST) ==
                ACL_SUCCESS;
        passed = passed && verify(actual, records);
    }
    if (output)
        passed = runtime.free_device(output) == ACL_SUCCESS && passed;
    if (device_records)
        passed = runtime.free_device(device_records) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    if (passed)
        std::cout << "ASC_STL_NUMERIC_TYPES_RUNTIME_PASS\n";
    return passed ? 0 : 1;
}
