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

#include <asc/std/__type_traits/is_final.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_final] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_final] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (!cond ? "OK" : "FAIL") << std::endl;
    if (cond)
        ++g_failures;
}

// Test types
struct NonFinal {};
struct Final final {};
class NonFinalClass {
public:
    int x;
};
class FinalClass final {
public:
    int x;
};

// Enum types
enum E1 { e1_a, e1_b };
enum class E2 { a, b };

// Union
union U1 {
    int a;
    float b;
};

int main()
{
    // Non-final types → false
    expect_false("is_final_v<NonFinal>", asc::std::is_final_v<NonFinal>);
    expect_false("is_final_v<NonFinalClass>", asc::std::is_final_v<NonFinalClass>);
    expect_false("is_final_v<int>", asc::std::is_final_v<int>);
    expect_false("is_final_v<E1>", asc::std::is_final_v<E1>);
    expect_false("is_final_v<E2>", asc::std::is_final_v<E2>);
    expect_false("is_final_v<U1>", asc::std::is_final_v<U1>);

    // Final types → true
    expect_true("is_final_v<Final>", asc::std::is_final_v<Final>);
    expect_true("is_final_v<FinalClass>", asc::std::is_final_v<FinalClass>);

    // is_final struct → value member
    expect_false("is_final<NonFinal>::value", asc::std::is_final<NonFinal>::value);
    expect_true("is_final<Final>::value", asc::std::is_final<Final>::value);

    // is_final inherits from bool_constant
    expect_true("is_final<Final> is true_type", asc::std::is_final<Final>::value == true);
    expect_true("is_final<NonFinal> is false_type", asc::std::is_final<NonFinal>::value == false);

    return g_failures == 0 ? 0 : 1;
}
