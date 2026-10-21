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

#include <dlfcn.h>

#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include "stage_api.h"
#include "types.h"

#if ASC_STL_B027_HARDWARE
#include "../../../../../../support/hardware_runtime.h"
#endif

namespace {
enum : unsigned {
    stage_count = 0
#define ASC_STL_B027_STAGE(name) +1
#include "stage_table.def"
#undef ASC_STL_B027_STAGE
};

class runtime_adapter {
public:
    aclError initialize()
    {
#if ASC_STL_B027_HARDWARE
        return protected_.initialize(nullptr);
#else
        return aclInit(nullptr);
#endif
    }
    aclError set_device()
    {
#if ASC_STL_B027_HARDWARE
        return protected_.set_device(0);
#else
        return aclrtSetDevice(0);
#endif
    }
    bool ready()
    {
#if ASC_STL_B027_HARDWARE
        return protected_.ready();
#else
        return true;
#endif
    }
    aclError synchronize(aclrtStream stream)
    {
#if ASC_STL_B027_HARDWARE
        return protected_.synchronize(stream);
#else
        return aclrtSynchronizeStream(stream);
#endif
    }
    aclError free_device(void* pointer)
    {
#if ASC_STL_B027_HARDWARE
        return protected_.free_device(pointer);
#else
        return aclrtFree(pointer);
#endif
    }
    aclError destroy_stream(aclrtStream stream)
    {
#if ASC_STL_B027_HARDWARE
        return protected_.destroy_stream(stream);
#else
        return aclrtDestroyStream(stream);
#endif
    }
    aclError reset_device(bool selected)
    {
#if ASC_STL_B027_HARDWARE
        (void)selected;
        return protected_.reset_device(0);
#else
        return selected ? aclrtResetDevice(0) : ACL_SUCCESS;
#endif
    }
    aclError finalize()
    {
#if ASC_STL_B027_HARDWARE
        return protected_.finalize();
#else
        return aclFinalize();
#endif
    }
    bool finish(bool passed)
    {
#if ASC_STL_B027_HARDWARE
        return protected_.finish(passed) == 0;
#else
        return passed;
#endif
    }

private:
#if ASC_STL_B027_HARDWARE
    asc_stl_test::hardware_runtime protected_;
#endif
};
struct module {
    const char* stage;
    const char* file;
    const char* symbol;
    void* handle = nullptr;
    asc_stl_b027_staged::launcher launch = nullptr;
};

template <class Operation>
bool acl_step(const char* name, Operation operation)
{
    std::cout << "ASC_STL_ACL begin=" << name << std::endl;
    const aclError status = operation();
    std::cout << "ASC_STL_ACL end=" << name << " status=" << status << std::endl;
    return status == ACL_SUCCESS;
}

bool close_modules(std::array<module, stage_count>& modules)
{
    bool clean = true;
    for (auto iterator = modules.rbegin(); iterator != modules.rend(); ++iterator) {
        if (iterator->handle) {
            const int status = dlclose(iterator->handle);
            std::cout << "ASC_STL_DLCLOSE stage=" << iterator->stage << " status=" << status << std::endl;
            if (status == 0) {
                iterator->handle = nullptr;
            } else {
                const char* error = dlerror();
                std::cerr << "ASC_STL_DLCLOSE_ERROR=" << (error ? error : "unknown") << std::endl;
                clean = false;
            }
        }
    }
    return clean;
}
struct staged_context {
    using state_type = asc_stl_b027_staged::storage;
    using string_type = asc_stl_b027_staged::string_type;
    std::array<module, stage_count> modules{{
#define ASC_STL_B027_STAGE(name) {#name, "libasc_stl_b027_" #name "_module.so", "asc_stl_b027_launch_" #name},
#include "stage_table.def"  // NOLINT(build/include)
#undef ASC_STL_B027_STAGE
    }};
    runtime_adapter runtime;
    bool passed = true;
    bool initialized = false;
    bool selected = false;
    bool pending = false;
    bool cleanup = true;
    unsigned completed = 0;
    asc_stl_b027_staged::stage_result result{};
    asc_stl_b027_staged::stage_result* device_result = nullptr;
    char* device_backing = nullptr;
    void* state_packet = nullptr;
    void* string_packet = nullptr;
    aclrtStream stream = nullptr;
    char backing[256]{};
    const char* classification = "HARNESS_SETUP_FAILURE";

    bool load_modules()
    {
        for (auto& item : modules) {
            const std::string path = std::string(ASC_STL_B027_MODULE_DIR) + "/" + item.file;
            item.handle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
            if (!item.handle) {
                const char* error = dlerror();
                std::cerr << "ASC_STL_DLOPEN_FAILED stage=" << item.stage << " error=" << (error ? error : "unknown")
                          << std::endl;
                passed = false;
                break;
            }
            dlerror();
            item.launch = reinterpret_cast<asc_stl_b027_staged::launcher>(dlsym(item.handle, item.symbol));
            const char* error = dlerror();
            if (error || !item.launch) {
                std::cerr << "ASC_STL_DLSYM_FAILED stage=" << item.stage
                          << " error=" << (error ? error : "null_launcher") << std::endl;
                passed = false;
                break;
            }
            std::cout << "ASC_STL_DLOPEN_OK stage=" << item.stage << " local=1 now=1" << std::endl;
        }
        return passed;
    }

    void initialize_runtime()
    {
        result.code = 0xB027FFFFU;
        initialized = acl_step("aclInit", [&] { return runtime.initialize(); });
        passed = initialized;
        if (passed) {
            selected = acl_step("aclrtSetDevice", [&] { return runtime.set_device(); });
            passed = selected;
        }
        if (passed) {
            passed = acl_step("aclrtCreateStream", [&] { return aclrtCreateStream(&stream); });
        }
    }

    void prepare_storage()
    {
        if (passed) {
            passed = acl_step("aclrtMalloc_result", [&] {
                return aclrtMalloc(reinterpret_cast<void**>(&device_result), sizeof(result), ACL_MEM_MALLOC_HUGE_FIRST);
            });
        }
        if (passed) {
            passed = acl_step("aclrtMalloc_backing", [&] {
                return aclrtMalloc(
                    reinterpret_cast<void**>(&device_backing), sizeof(backing), ACL_MEM_MALLOC_HUGE_FIRST);
            });
        }
        if (passed) {
            passed = acl_step(
                "aclrtMalloc_state", [&] { return aclrtMalloc(&state_packet, 64, ACL_MEM_MALLOC_HUGE_FIRST); });
        }
        if (passed) {
            passed = acl_step(
                "aclrtMalloc_string", [&] { return aclrtMalloc(&string_packet, 128, ACL_MEM_MALLOC_HUGE_FIRST); });
        }
        if (passed) {
            passed = acl_step("aclrtMemcpy_backing_H2D", [&] {
                return aclrtMemcpy(
                    device_backing, sizeof(backing), backing, sizeof(backing), ACL_MEMCPY_HOST_TO_DEVICE);
            });
        }
        if (passed) {
            passed = reinterpret_cast<std::uintptr_t>(state_packet) % alignof(state_type) == 0 &&
                reinterpret_cast<std::uintptr_t>(string_packet) % alignof(string_type) == 0;
            std::cout << "ASC_STL_LAYOUT state=" << sizeof(state_type) << " string=" << sizeof(string_type)
                      << " packets=64,128 backing=256 aligned=" << (passed ? 1 : 0) << std::endl;
        }
    }

    bool execute_stage(unsigned index)
    {
        auto& item = modules[index];
        const unsigned sentinel = 0xB0270100U + index;
        result = {};
        result.code = sentinel;
        std::cout << "ASC_STL_STAGE_BEGIN stage=" << item.stage << " sentinel=" << sentinel << std::endl;
        if (!acl_step("aclrtMemcpy_result_sentinel_H2D", [&] {
                return aclrtMemcpy(device_result, sizeof(result), &result, sizeof(result), ACL_MEMCPY_HOST_TO_DEVICE);
            })) {
            classification = "HARNESS_SENTINEL_UPLOAD_FAILURE";
            passed = false;
            return false;
        }
        if (!runtime.ready()) {
            classification = "HARNESS_CANCELLED_BEFORE_LAUNCH";
            passed = false;
            return false;
        }
        pending = true;
        item.launch(device_result, device_backing, state_packet, string_packet, stream);
        if (!acl_step("aclrtSynchronizeStream", [&] { return runtime.synchronize(stream); })) {
            classification = "HARNESS_OR_DEVICE_SYNCHRONIZATION_FAILURE";
            passed = false;
            return false;
        }
        pending = false;
        if (!acl_step("aclrtMemcpy_result_D2H", [&] {
                return aclrtMemcpy(&result, sizeof(result), device_result, sizeof(result), ACL_MEMCPY_DEVICE_TO_HOST);
            })) {
            classification = "HARNESS_RESULT_COPY_FAILURE";
            passed = false;
            return false;
        }
        std::cout << "ASC_STL_STAGE_RESULT stage=" << item.stage << " result=" << result.code << std::endl;
        if (result.code != 0) {
            classification = result.code == sentinel ? "HARNESS_RESULT_SENTINEL_UNCHANGED" : "SEMANTIC_STAGE_FAILURE";
            passed = false;
            return false;
        }
        ++completed;
        return true;
    }

    void execute_stages()
    {
        for (unsigned index = 0; passed && runtime.ready() && index < modules.size(); ++index) {
            if (!execute_stage(index))
                break;
        }
    }

    void check_profile()
    {
        if (passed && completed == stage_count) {
            std::cout << "ASC_STL_STRING_COUNTS allocations=" << result.allocations
                      << " deallocations=" << result.deallocations << " used=" << result.used
                      << " sizes=" << result.allocation_sizes[0] << ',' << result.allocation_sizes[1] << ','
                      << result.allocation_sizes[2] << " sso_allocations=" << result.sso_allocations
                      << " sso_deallocations=" << result.sso_deallocations << std::endl;
            passed = result.allocations == 3 && result.deallocations == 3 && result.used == 171 &&
                result.allocation_sizes[0] == 25 && result.allocation_sizes[1] == 49 &&
                result.allocation_sizes[2] == 97 && result.sso_allocations == 0 && result.sso_deallocations == 0;
            if (!passed) {
                classification = "SEMANTIC_ALLOCATION_PROFILE_FAILURE";
            }
        }
    }

    void release_resources()
    {
        if (!pending) {
            cleanup = close_modules(modules) && cleanup;
            if (string_packet) {
                cleanup = acl_step("aclrtFree_string", [&] { return runtime.free_device(string_packet); }) && cleanup;
            }
            if (state_packet) {
                cleanup = acl_step("aclrtFree_state", [&] { return runtime.free_device(state_packet); }) && cleanup;
            }
            if (device_backing) {
                cleanup = acl_step("aclrtFree_backing", [&] { return runtime.free_device(device_backing); }) && cleanup;
            }
            if (device_result) {
                cleanup = acl_step("aclrtFree_result", [&] { return runtime.free_device(device_result); }) && cleanup;
            }
            if (stream) {
                cleanup = acl_step("aclrtDestroyStream", [&] { return runtime.destroy_stream(stream); }) && cleanup;
            }
        } else {
            cleanup = false;
            std::cout << "ASC_STL_PENDING_UNKNOWN skip=dlclose,free,destroy_stream handles_retained=1" << std::endl;
        }
    }

    void shutdown_runtime()
    {
        if (initialized) {
            cleanup = acl_step("aclrtResetDevice", [&] { return runtime.reset_device(selected); }) && cleanup;
        }
        if (initialized) {
            cleanup = acl_step("aclFinalize", [&] { return runtime.finalize(); }) && cleanup;
        }
    }

    int finish()
    {
        const bool semantics_passed = passed && completed == stage_count;
        passed = runtime.finish(semantics_passed && cleanup && !pending);
        if (passed) {
            classification = "PASS_FULL_CORE_AND_STRING_FIXTURE";
        } else if (semantics_passed && !cleanup) {
            classification = "HARNESS_CLEANUP_FAILURE";
        }
        std::cout << "ASC_STL_STAGED_CLASSIFICATION=" << classification << std::endl;
        std::cout << "ASC_STL_STAGED_COMPLETE stages=" << completed << " cleanup=" << (cleanup ? 1 : 0)
                  << " pending=" << (pending ? 1 : 0) << " diagnostic_result=" << result.code << std::endl;
        if (pending) {
            // Normal exit would run the loaded ASC modules' unregister finalizers.
            std::cout << "ASC_STL_PENDING_EXIT without_module_finalizers=1" << std::endl;
            std::cout.flush();
            std::cerr.flush();
            std::_Exit(1);
        }
        if (passed && completed == stage_count && cleanup && !pending) {
#if ASC_STL_B027_HARDWARE
            std::cout << "ASC_STL_B027_HARDWARE_PASS" << std::endl;
#else
            std::cout << "ASC_STL_B027_CANNSIM_PASS" << std::endl;
#endif
            return 0;
        }
        return 1;
    }
};
}  // namespace

int main()
{
    staged_context context;
    if (!context.load_modules()) {
        close_modules(context.modules);
        std::cout << "ASC_STL_STAGED_CLASSIFICATION=HARNESS_MODULE_LOAD_FAILURE" << std::endl;
        return 1;
    }
    context.initialize_runtime();
    context.prepare_storage();
    context.execute_stages();
    context.check_profile();
    context.release_resources();
    context.shutdown_runtime();
    return context.finish();
}
