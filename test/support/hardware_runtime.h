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

#ifndef ASC_STL_TEST_SUPPORT_HARDWARE_RUNTIME_H
#define ASC_STL_TEST_SUPPORT_HARDWARE_RUNTIME_H

#include <acl/acl.h>

#include <csignal>
#include <iostream>

namespace asc_stl_test {

// This helper is Host-only test infrastructure, never an installed product Header.
// An SDK without these two timeout APIs must fail to build: an unbounded fallback
// cannot safely run this hardware suite.
class hardware_runtime {
public:
    hardware_runtime()
        : previous_term_(std::signal(SIGTERM, request_stop)), previous_int_(std::signal(SIGINT, request_stop))
    {
        interrupted_ = 0;
    }

    ~hardware_runtime()
    {
        if (selected_)
            reset_device(device_);
        if (initialized_)
            finalize();
        std::signal(SIGTERM, previous_term_);
        std::signal(SIGINT, previous_int_);
    }

    hardware_runtime(const hardware_runtime&) = delete;
    hardware_runtime& operator=(const hardware_runtime&) = delete;

    aclError initialize(const char* config)
    {
        const auto status = call("aclInit", [config] { return aclInit(config); });
        initialized_ = status == ACL_SUCCESS;
        return status;
    }

    aclError set_device(int device)
    {
        if (interrupted_)
            return interrupted_status();
        const auto status = call("aclrtSetDevice", [device] { return aclrtSetDevice(device); });
        selected_ = status == ACL_SUCCESS;
        device_ = device;
        if (!selected_)
            return status;
        std::cout << "ASC_STL_RUNTIME op_timeout_seconds=10 stream_timeout_ms=10000" << std::endl;
        return call("aclrtSetOpExecuteTimeOut", [] { return aclrtSetOpExecuteTimeOut(10U); });
    }

    bool ready()
    {
        if (interrupted_)
            interrupted_status();
        return !failed_ && !interrupted_;
    }

    aclError synchronize(aclrtStream stream)
    {
        const auto status = call(
            "aclrtSynchronizeStreamWithTimeout", [stream] { return aclrtSynchronizeStreamWithTimeout(stream, 10000); });
        synchronization_failed_ = synchronization_failed_ || status != ACL_SUCCESS;
        return status == ACL_SUCCESS && interrupted_ ? interrupted_status() : status;
    }

    aclError free_device(void* pointer)
    {
        if (synchronization_failed_)
            return skip_after_failed_sync("aclrtFree");
        return call("aclrtFree", [pointer] { return aclrtFree(pointer); });
    }

    aclError destroy_stream(aclrtStream stream)
    {
        if (synchronization_failed_)
            return skip_after_failed_sync("aclrtDestroyStream");
        return call("aclrtDestroyStream", [stream] { return aclrtDestroyStream(stream); });
    }

    aclError reset_device(int device)
    {
        if (!selected_)
            return ACL_SUCCESS;
        const auto status = call("aclrtResetDevice", [device] { return aclrtResetDevice(device); });
        // Never retry a failed cleanup invisibly from the destructor.
        selected_ = false;
        return status;
    }

    aclError finalize()
    {
        if (!initialized_)
            return ACL_SUCCESS;
        const auto status = call("aclFinalize", [] { return aclFinalize(); });
        initialized_ = false;
        return status;
    }

    int finish(bool passed)
    {
        const bool complete = !failed_ && !initialized_ && !selected_ && !interrupted_;
        std::cout << "ASC_STL_RUNTIME_COMPLETE=" << (complete ? 1 : 0) << std::endl;
        return passed && complete ? 0 : 1;
    }

private:
    using signal_handler = void (*)(int);
    inline static volatile std::sig_atomic_t interrupted_ = 0;
    signal_handler previous_term_;
    signal_handler previous_int_;
    bool initialized_ = false;
    bool selected_ = false;
    bool failed_ = false;
    bool synchronization_failed_ = false;
    int device_ = 0;

    static void request_stop(int signal)
    {
        interrupted_ = signal;
    }

    aclError skip_after_failed_sync(const char* name)
    {
        // A failed synchronization does not prove kernels stopped using their
        // buffers. Leave context-owned resources for reset instead of freeing
        // storage underneath a possibly running kernel.
        std::cerr << "ASC_STL_RUNTIME skipped=" << name << " reason=failed_synchronization" << std::endl;
        return static_cast<aclError>(-1);
    }

    aclError interrupted_status()
    {
        failed_ = true;
        std::cerr << "ASC_STL_RUNTIME interrupted=" << interrupted_ << std::endl;
        return static_cast<aclError>(-1);
    }

    template <class Operation>
    aclError call(const char* name, Operation operation)
    {
        std::cout << "ASC_STL_RUNTIME begin=" << name << std::endl;
        const aclError status = operation();
        std::cout << "ASC_STL_RUNTIME end=" << name << " status=" << status << std::endl;
        failed_ = failed_ || status != ACL_SUCCESS;
        return status;
    }
};

}  // namespace asc_stl_test

#endif  // ASC_STL_TEST_SUPPORT_HARDWARE_RUNTIME_H
