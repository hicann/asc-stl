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

#include <asc/std/__exception/terminate.h>

#include <atomic>
#include <csignal>
#include <cstdlib>
#include <functional>

namespace {
std::atomic<int> handler_calls{0};
}

int main()
{
    // The Host branch delegates to the currently installed terminate handler.
    std::set_terminate([]() {
        ++handler_calls;
        std::_Exit(0);
    });
    const int previous = handler_calls.load();
    if (previous != 0) {
        return 1;
    }
    asc::std::terminate();
    // terminate never returns; reaching this point is the failure.
    return 2;
}
