/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include <asc/std/__fwd/execution_policy.h>
#include <iostream>
#include <cstdint>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][execution_policy] " << expr << " = " << +got << " (expected " << +expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

int main()
{
    namespace ex = asc::std::execution;

    // Test __execution_policy enum values
    expect_eq("ex::__execution_policy::__invalid_execution_policy",
        static_cast<uint8_t>(ex::__execution_policy::__invalid_execution_policy), uint8_t(0));
    expect_eq("ex::__execution_policy::__sequenced", static_cast<uint8_t>(ex::__execution_policy::__sequenced),
        uint8_t(1 << 0));
    expect_eq("ex::__execution_policy::__parallel", static_cast<uint8_t>(ex::__execution_policy::__parallel),
        uint8_t(1 << 1));
    expect_eq("ex::__execution_policy::__unsequenced", static_cast<uint8_t>(ex::__execution_policy::__unsequenced),
        uint8_t(1 << 2));
    expect_eq("ex::__execution_policy::__parallel_unsequenced",
        static_cast<uint8_t>(ex::__execution_policy::__parallel_unsequenced), uint8_t((1 << 1) | (1 << 2)));

    // Test __policy_to_execution_policy
    expect_eq("ex::__policy_to_execution_policy<0x01>", static_cast<uint8_t>(ex::__policy_to_execution_policy<0x01>),
        uint8_t(1 << 0));
    expect_eq("ex::__policy_to_execution_policy<0x02>", static_cast<uint8_t>(ex::__policy_to_execution_policy<0x02>),
        uint8_t(1 << 1));
    expect_eq("ex::__policy_to_execution_policy<0x06>", static_cast<uint8_t>(ex::__policy_to_execution_policy<0x06>),
        uint8_t((1 << 1) | (1 << 2)));

    // Test __execution_backend enum values
    expect_eq("ex::__execution_backend::__none", static_cast<uint8_t>(ex::__execution_backend::__none), uint8_t(0));

    // Test __policy_to_execution_backend
    expect_eq("ex::__policy_to_execution_backend<0x0000>",
        static_cast<uint8_t>(ex::__policy_to_execution_backend<0x0000>), uint8_t(0));
    expect_eq("ex::__policy_to_execution_backend<0x0100>",
        static_cast<uint8_t>(ex::__policy_to_execution_backend<0x0100>), uint8_t(1));

    // Test __with_backend
    expect_eq("ex::__with_backend<0x00000001, ex::__execution_backend(1)>",
        ex::__with_backend<0x00000001, static_cast<ex::__execution_backend>(1)>(), 0x00000101u);
    expect_eq("ex::__with_backend<0x0000FF00, ex::__execution_backend(0)>",
        ex::__with_backend<0x0000FF00, static_cast<ex::__execution_backend>(0)>(), 0x00000000u);

    // Test __has_backend
    expect_eq("ex::__has_backend<0x00000101, static_cast<ex::__execution_backend>(1)>",
        static_cast<int>(ex::__has_backend<0x00000101, static_cast<ex::__execution_backend>(1)>()), 1);
    expect_eq("ex::__has_backend<0x00000001, static_cast<ex::__execution_backend>(1)>",
        static_cast<int>(ex::__has_backend<0x00000001, static_cast<ex::__execution_backend>(1)>()), 0);

    return g_failures == 0 ? 0 : 1;
}
