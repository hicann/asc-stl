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

#define ASC_IGNORE_DEPRECATED_API
#include <asc/std/__type_traits/is_pod.h>
#include <iostream>

static int g_failures = 0;

static void expect_eq(const char* expr, bool got, bool expected)
{
    bool ok = (got == expected);
    std::cout << "[host][is_pod] " << expr << " = " << (got ? "true" : "false") << " (expected "
              << (expected ? "true" : "false") << ") " << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

// POD types
struct SimpleStruct {
    int a;
    double b;
};

enum MyEnum { A, B, C };

// Non-POD types
struct WithConstructor {
    int a;
    WithConstructor() : a(0)
    {}
};

struct WithVirtual {
    int a;
    virtual void foo()
    {}
};

struct WithNonPODMember {
    WithConstructor member;
};

int main()
{
    // Basic POD types (true)
    expect_eq("is_pod_v<int>", asc::std::is_pod_v<int>, true);
    expect_eq("is_pod_v<double>", asc::std::is_pod_v<double>, true);
    expect_eq("is_pod_v<char>", asc::std::is_pod_v<char>, true);
    expect_eq("is_pod_v<float>", asc::std::is_pod_v<float>, true);
    expect_eq("is_pod_v<long>", asc::std::is_pod_v<long>, true);
    expect_eq("is_pod_v<unsigned>", asc::std::is_pod_v<unsigned>, true);
    expect_eq("is_pod_v<bool>", asc::std::is_pod_v<bool>, true);
    expect_eq("is_pod_v<int*>", asc::std::is_pod_v<int*>, true);
    expect_eq("is_pod_v<SimpleStruct>", asc::std::is_pod_v<SimpleStruct>, true);
    expect_eq("is_pod_v<MyEnum>", asc::std::is_pod_v<MyEnum>, true);
    expect_eq("is_pod_v<int[5]>", asc::std::is_pod_v<int[5]>, true);

    // Non-POD types (false)
    expect_eq("is_pod_v<WithConstructor>", asc::std::is_pod_v<WithConstructor>, false);
    expect_eq("is_pod_v<WithVirtual>", asc::std::is_pod_v<WithVirtual>, false);
    expect_eq("is_pod_v<WithNonPODMember>", asc::std::is_pod_v<WithNonPODMember>, false);

    // is_pod struct with ::value member
    expect_eq("is_pod<int>::value", asc::std::is_pod<int>::value, true);
    expect_eq("is_pod<double>::value", asc::std::is_pod<double>::value, true);
    expect_eq("is_pod<WithConstructor>::value", asc::std::is_pod<WithConstructor>::value, false);
    expect_eq("is_pod<WithVirtual>::value", asc::std::is_pod<WithVirtual>::value, false);

    // Verify bool_constant inheritance: is_pod<T> is implicitly convertible to bool
    expect_eq("static_cast<bool>(is_pod<int>)", static_cast<bool>(asc::std::is_pod<int>()), true);
    expect_eq("static_cast<bool>(is_pod<WithVirtual>)", static_cast<bool>(asc::std::is_pod<WithVirtual>()), false);

    // Verify is_pod<T>() callable returns value
    expect_eq("is_pod<int>()()", asc::std::is_pod<int>()(), true);
    expect_eq("is_pod<WithConstructor>()()", asc::std::is_pod<WithConstructor>()(), false);

    return g_failures == 0 ? 0 : 1;
}
