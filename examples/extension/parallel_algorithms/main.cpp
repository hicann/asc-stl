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

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "parallel_example.h"

namespace {
volatile std::sig_atomic_t stop_requested = 0;
void request_stop(int signal)
{
    stop_requested = signal;
}

struct runtime_state {
    bool initialized{};
    bool device_selected{};
};

bool checked(const char* phase, aclError code)
{
    std::printf("{\"phase\":\"%s\",\"code\":%d}\n", phase, static_cast<int>(code));
    return code == ACL_SUCCESS;
}

bool initialize(runtime_state& state)
{
    state.initialized = checked("initialize", aclInit(nullptr));
    if (!state.initialized)
        return false;
    state.device_selected = checked("select_device", aclrtSetDevice(0));
    if (!state.device_selected)
        return false;
    return checked("task_timeout_seconds", aclrtSetOpExecuteTimeOut(10U));
}

bool shutdown(runtime_state& state, bool safe)
{
    if (!safe) {
        std::printf("{\"phase\":\"shutdown\",\"state\":\"not_attempted_after_failure\"}\n");
        return false;
    }
    bool passed = true;
    if (state.device_selected) {
        if (!checked("reset_device", aclrtResetDevice(0)))
            return false;
        state.device_selected = false;
    }
    if (state.initialized) {
        passed = checked("finalize", aclFinalize());
        if (passed)
            state.initialized = false;
    }
    return passed;
}
}  // namespace

int main(int argc, char** argv)
{
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    std::signal(SIGTERM, request_stop);
    std::signal(SIGINT, request_stop);
    asc::std::size_t count = 0;
    const auto* cases = parallel_example_cases(count);
    if (argc == 2 && std::strcmp(argv[1], "--describe") == 0) {
        std::printf("{\"case_count\":%llu,\"cplusplus\":%ld}\n", static_cast<unsigned long long>(count), __cplusplus);
        return 0;
    }
    if (argc != 2)
        return 64;
    char* end = nullptr;
    const auto selected = std::strtoul(argv[1], &end, 10);
    if (*argv[1] == '\0' || *end != '\0' || selected >= count)
        return 64;
    const auto& current = cases[selected];
    std::printf("{\"case\":\"%s\",\"phase\":\"begin\",\"cplusplus\":%ld}\n", current.name, __cplusplus);
    runtime_state state;
    const bool ready = initialize(state);
    parallel_example_context context(current.name);
    const bool opened = ready && context.open();
    const bool golden = opened && !stop_requested && current.run(context);
    std::printf("{\"case\":\"%s\",\"phase\":\"golden\",\"passed\":%s}\n", current.name, golden ? "true" : "false");
    const bool released = context.close();
    const bool finalized = shutdown(state, released && context.safe_to_release());
    const bool passed = golden && released && finalized && !stop_requested;
    std::printf("{\"case\":\"%s\",\"phase\":\"result\",\"passed\":%s,\"cleanup\":%s}\n", current.name,
        passed ? "true" : "false", released && finalized ? "true" : "false");
    std::fflush(stdout);
    return passed ? 0 : 1;
}
