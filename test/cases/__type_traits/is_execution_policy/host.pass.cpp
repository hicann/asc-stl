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

#include <asc/std/__type_traits/is_execution_policy.h>
#include <asc/std/__fwd/execution_policy.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_execution_policy] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_execution_policy] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

// ---- Fake execution policy types that mimic real policies ----
// They must expose __asc_policy_ (detected by void_t) and __get_policy().
struct FakeSeqPolicy {
    static constexpr int __asc_policy_ = 0;
    static constexpr asc::std::execution::__execution_policy __get_policy()
    {
        return asc::std::execution::__execution_policy::__sequenced;
    }
};

struct FakeParallelPolicy {
    static constexpr int __asc_policy_ = 0;
    static constexpr asc::std::execution::__execution_policy __get_policy()
    {
        return asc::std::execution::__execution_policy::__parallel;
    }
};

struct FakeUnsequencedPolicy {
    static constexpr int __asc_policy_ = 0;
    static constexpr asc::std::execution::__execution_policy __get_policy()
    {
        return asc::std::execution::__execution_policy::__unsequenced;
    }
};

struct FakeParallelUnsequencedPolicy {
    static constexpr int __asc_policy_ = 0;
    static constexpr asc::std::execution::__execution_policy __get_policy()
    {
        return asc::std::execution::__execution_policy::__parallel_unsequenced;
    }
};

// ---- Non-policy types ----
struct NonPolicy {
    int value;
};

int main()
{
    // ===== is_execution_policy_v =====
    expect_true("is_execution_policy_v<FakeSeqPolicy>", asc::std::is_execution_policy_v<FakeSeqPolicy>);
    expect_true("is_execution_policy_v<FakeParallelPolicy>", asc::std::is_execution_policy_v<FakeParallelPolicy>);
    expect_true("is_execution_policy_v<FakeUnsequencedPolicy>", asc::std::is_execution_policy_v<FakeUnsequencedPolicy>);
    expect_true("is_execution_policy_v<FakeParallelUnsequencedPolicy>",
        asc::std::is_execution_policy_v<FakeParallelUnsequencedPolicy>);
    expect_false("is_execution_policy_v<NonPolicy>", asc::std::is_execution_policy_v<NonPolicy>);
    expect_false("is_execution_policy_v<int>", asc::std::is_execution_policy_v<int>);
    expect_false("is_execution_policy_v<double>", asc::std::is_execution_policy_v<double>);

    // ===== is_execution_policy (struct, inherits bool_constant) =====
    expect_true("is_execution_policy<FakeSeqPolicy>::value", asc::std::is_execution_policy<FakeSeqPolicy>::value);
    expect_true(
        "is_execution_policy<FakeParallelPolicy>::value", asc::std::is_execution_policy<FakeParallelPolicy>::value);
    expect_false("is_execution_policy<NonPolicy>::value", asc::std::is_execution_policy<NonPolicy>::value);
    expect_false("is_execution_policy<int>::value", asc::std::is_execution_policy<int>::value);

    // Verify is_execution_policy derives from bool_constant (true_type / false_type)
    expect_true("is_base_of_v<asc::std::true_type, asc::std::is_execution_policy<FakeSeqPolicy>>",
        std::is_base_of_v<asc::std::true_type, asc::std::is_execution_policy<FakeSeqPolicy>>);
    expect_true("is_base_of_v<asc::std::false_type, asc::std::is_execution_policy<NonPolicy>>",
        std::is_base_of_v<asc::std::false_type, asc::std::is_execution_policy<NonPolicy>>);

    // ===== __is_parallel_execution_policy_v =====
    expect_false(
        "__is_parallel_execution_policy_v<FakeSeqPolicy>", asc::std::__is_parallel_execution_policy_v<FakeSeqPolicy>);
    expect_true("__is_parallel_execution_policy_v<FakeParallelPolicy>",
        asc::std::__is_parallel_execution_policy_v<FakeParallelPolicy>);
    expect_false("__is_parallel_execution_policy_v<FakeUnsequencedPolicy>",
        asc::std::__is_parallel_execution_policy_v<FakeUnsequencedPolicy>);
    expect_true("__is_parallel_execution_policy_v<FakeParallelUnsequencedPolicy>",
        asc::std::__is_parallel_execution_policy_v<FakeParallelUnsequencedPolicy>);
    expect_false("__is_parallel_execution_policy_v<NonPolicy>", asc::std::__is_parallel_execution_policy_v<NonPolicy>);

    // ===== __is_unsequenced_execution_policy_v =====
    expect_false("__is_unsequenced_execution_policy_v<FakeSeqPolicy>",
        asc::std::__is_unsequenced_execution_policy_v<FakeSeqPolicy>);
    expect_false("__is_unsequenced_execution_policy_v<FakeParallelPolicy>",
        asc::std::__is_unsequenced_execution_policy_v<FakeParallelPolicy>);
    expect_true("__is_unsequenced_execution_policy_v<FakeUnsequencedPolicy>",
        asc::std::__is_unsequenced_execution_policy_v<FakeUnsequencedPolicy>);
    expect_true("__is_unsequenced_execution_policy_v<FakeParallelUnsequencedPolicy>",
        asc::std::__is_unsequenced_execution_policy_v<FakeParallelUnsequencedPolicy>);
    expect_false(
        "__is_unsequenced_execution_policy_v<NonPolicy>", asc::std::__is_unsequenced_execution_policy_v<NonPolicy>);

    return g_failures == 0 ? 0 : 1;
}
