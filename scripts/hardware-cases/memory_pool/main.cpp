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

#include <asc/memory_pool>

#include <cstddef>
#include <iostream>
#include "../../../test/support/hardware_runtime.h"

namespace {
bool run_memory_pool(asc_stl_test::hardware_runtime& runtime)
{
    asc::stream stream;
    asc::device_memory_pool pool;
    void* block = nullptr;
    bool passed = asc::make_stream(stream);
    asc::execution_status close_status{asc::execution_errc::backend_error};
    if (passed && runtime.ready()) {
        const asc::device_memory_pool_config config{0, 1 << 20, 0};
        passed = asc::device_memory_pool::create(pool, config).success() &&
            pool.allocate_async(&block, 4096, 32, stream).success() &&
            aclrtMemsetAsync(block, 4096, 0x5a, 4096, stream.native_handle()) == 0 &&
            pool.deallocate_async(block, stream).success();
    }
    if (passed) {
        std::cout << "ASC_STL_RUNTIME begin=memory_pool.close" << std::endl;
        close_status = pool.close();
        std::cout << "ASC_STL_RUNTIME end=memory_pool.close status=" << static_cast<int>(close_status.code())
                  << std::endl;
        passed = close_status.success() && !pool.valid();
    }
    std::cout << "b025_memory_pool_close_code=" << static_cast<int>(close_status.code()) << '\n';
    std::cout << "b025_memory_pool_valid_after_close=" << pool.valid() << '\n';

    if (pool.valid()) {
        passed = pool.close().success() && passed;
    }
    passed = stream.close() && passed;
    return passed;
}
}  // namespace

int main()
{
    asc_stl_test::hardware_runtime runtime;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS;
    if (passed && runtime.ready())
        passed = run_memory_pool(runtime);
    passed = runtime.reset_device(0) == 0 && passed;
    passed = runtime.finalize() == 0 && passed;
    passed = runtime.finish(passed) == 0;
    if (passed) {
        std::cout << "ASC_STL_B025_MEMORY_POOL_HARDWARE_PASS\n";
    }
    return passed ? 0 : 1;
}
