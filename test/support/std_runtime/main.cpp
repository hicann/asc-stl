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
#include <iostream>
#include <iterator>
#include <string_view>

#include "support/device_runtime.h"

#include "launch.h"

namespace {
constexpr const char* headers[] = {
#define ASC_STL_REGISTER_CHECK(header) #header,
#include "checks.inc"
#undef ASC_STL_REGISTER_CHECK
};
unsigned find_header(std::string_view name)
{
    for (unsigned i = 0; i < std::size(headers); ++i)
        if (name == headers[i])
            return i;
    return std::size(headers);
}
}  // namespace

int main(int argc, char** argv)
{
    const unsigned first = argc > 1 ? find_header(argv[1]) : 0;
    const unsigned last = argc > 2 ? find_header(argv[2]) : (argc > 1 ? first : std::size(headers) - 1);
    if (argc > 3 || first > last || last >= std::size(headers)) {
        std::cerr << "usage: " << argv[0] << " [first-header [last-header]]\n";
        return 2;
    }
    asc_stl_test::device_runtime runtime;
    int results[std::size(headers)]{};
    int* device = nullptr;
    unsigned char* workspace = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), sizeof(results), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemset(device, sizeof(results), 0xA5, sizeof(results)) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&workspace), std::size(headers) * workspace_stride,
            ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
        launch_checks(device, workspace, first, last - first + 1, 7, stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(results, sizeof(results), device, sizeof(results), ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        if (passed) {
            for (unsigned i = first; i <= last; ++i) {
                std::cout << "asc/std/" << headers[i] << " check=" << results[i] << '\n';
                passed = passed && results[i] == 0;
            }
        }
    }
    if (workspace)
        passed = runtime.free_device(workspace) == ACL_SUCCESS && passed;
    if (device)
        passed = runtime.free_device(device) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    if (runtime.finish(passed))
        return 1;
    std::cout << "ASC_STL_STD_RUNTIME_PASS\n";
    return 0;
}
