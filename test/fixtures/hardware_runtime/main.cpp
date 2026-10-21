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
#include <csignal>
#include <iostream>
#include "../../support/hardware_runtime.h"

namespace {
int failure = 0;
unsigned int calls = 0;

int record(unsigned int stage)
{
    calls |= 1U << stage;
    return failure == static_cast<int>(stage) ? 507999 : ACL_SUCCESS;
}
}  // namespace

aclError aclInit(const char*)
{
    return record(1);
}
aclError aclrtSetDevice([[maybe_unused]] int device)
{
    return record(2);
}
aclError aclrtSetOpExecuteTimeOut(std::uint32_t seconds)
{
    return seconds == 10U ? record(3) : 99;
}
aclError aclrtSynchronizeStreamWithTimeout(aclrtStream, std::int32_t timeout)
{
    return timeout == 10000 ? record(4) : 99;
}
aclError aclrtFree([[maybe_unused]] void* pointer)
{
    return record(5);
}
aclError aclrtDestroyStream(aclrtStream)
{
    return record(6);
}
aclError aclrtResetDevice([[maybe_unused]] int device)
{
    return record(7);
}
aclError aclFinalize()
{
    if (failure == 10)
        std::raise(SIGTERM);
    return record(8);
}

int main(int argc, char** argv)
{
    failure = argc > 1 ? std::atoi(argv[1]) : 0;
    asc_stl_test::hardware_runtime runtime;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS;
    if (failure == 11)
        std::raise(SIGTERM);
    if (passed && runtime.ready()) {
        std::cout << "fixture_launch" << std::endl;
        if (failure == 9)
            std::raise(SIGTERM);
        passed = runtime.synchronize(nullptr) == ACL_SUCCESS;
        passed = runtime.free_device(nullptr) == ACL_SUCCESS && passed;
        passed = runtime.destroy_stream(nullptr) == ACL_SUCCESS && passed;
    }
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    std::cout << "fixture_calls=" << calls << std::endl;
    return runtime.finish(passed);
}
