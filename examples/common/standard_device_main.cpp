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

#include <cstdio>

#include "check.h"
#include "standard_device.h"

namespace {

struct Resources {
    void* input = nullptr;
    void* output = nullptr;
    aclrtStream stream = nullptr;
    bool initialized = false;
    bool selected = false;
    bool pending = false;
};

bool checked(aclError status, const char* operation)
{
    std::printf("%s=%d\n", operation, static_cast<int>(status));
    return status == ACL_SUCCESS;
}

bool prepare(Resources& resources, const example::Input& input)
{
    resources.initialized = checked(aclInit(nullptr), "aclInit");
    if (!resources.initialized)
        return false;
    resources.selected = checked(aclrtSetDevice(0), "aclrtSetDevice");
    if (!resources.selected || !checked(aclrtSetOpExecuteTimeOut(10), "aclrtSetOpExecuteTimeOut"))
        return false;
    if (!checked(aclrtCreateStream(&resources.stream), "aclrtCreateStream"))
        return false;
    if (!checked(aclrtMalloc(&resources.input, sizeof(input), ACL_MEM_MALLOC_HUGE_FIRST), "input.allocate"))
        return false;
    if (!checked(aclrtMalloc(&resources.output, sizeof(DeviceOutput), ACL_MEM_MALLOC_HUGE_FIRST), "output.allocate"))
        return false;
    if (!checked(aclrtMemcpy(resources.input, sizeof(input), &input, sizeof(input), ACL_MEMCPY_HOST_TO_DEVICE),
            "input.upload"))
        return false;
    return checked(aclrtMemset(resources.output, sizeof(DeviceOutput), 0xa5, sizeof(DeviceOutput)), "output.sentinel");
}

bool execute(Resources& resources, DeviceOutput& actual)
{
    resources.pending = true;
    launch_standard_example(static_cast<const example::Input*>(resources.input),
        static_cast<DeviceOutput*>(resources.output), resources.stream);
    if (!checked(aclrtSynchronizeStreamWithTimeout(resources.stream, 10000), "stream.synchronize"))
        return false;
    resources.pending = false;
    return checked(aclrtMemcpy(&actual, sizeof(actual), resources.output, sizeof(actual), ACL_MEMCPY_DEVICE_TO_HOST),
        "output.download");
}

bool cleanup(Resources& resources)
{
    bool passed = !resources.pending;
    if (!resources.pending) {
        if (resources.output != nullptr)
            passed = checked(aclrtFree(resources.output), "output.free") && passed;
        if (resources.input != nullptr)
            passed = checked(aclrtFree(resources.input), "input.free") && passed;
        if (resources.stream != nullptr)
            passed = checked(aclrtDestroyStream(resources.stream), "stream.destroy") && passed;
    }
    if (resources.selected)
        passed = checked(aclrtResetDevice(0), "device.reset") && passed;
    if (resources.initialized)
        passed = checked(aclFinalize(), "aclFinalize") && passed;
    return passed;
}

}  // namespace

int main()
{
    std::printf("example=%s standard=%d\n", ASC_STL_EXAMPLE_NAME, ASC_STL_EXAMPLE_LANGUAGE);
    Resources resources;
    DeviceOutput actual{};
    const auto input = example::make_input();
    bool passed = prepare(resources, input);
    if (passed)
        passed = execute(resources, actual);
    if (passed) {
        const unsigned int expected_language = ASC_STL_EXAMPLE_LANGUAGE == 17 ? 201703U : 202002U;
        std::printf("device_cplusplus=%u\n", actual.cplusplus);
        passed = example::report(actual.result) && actual.cplusplus == expected_language;
    }
    const bool clean = cleanup(resources);
    std::printf("cleanup_passed=%d\n", clean ? 1 : 0);
    passed = passed && clean;
    std::printf("%s\n", passed ? "ASC_STL_STANDARD_DEVICE_PASS" : "ASC_STL_STANDARD_DEVICE_FAIL");
    return passed ? 0 : 1;
}
