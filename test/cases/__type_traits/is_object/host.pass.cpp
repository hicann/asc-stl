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

#include <asc/std/__type_traits/is_object.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][is_object] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][is_object] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

struct S {};
union U {};

int main()
{
    // scalar types
    expect_true("is_object_v<int>", asc::std::is_object_v<int>);
    expect_true("is_object_v<double>", asc::std::is_object_v<double>);
    expect_true("is_object_v<int*>", asc::std::is_object_v<int*>);
    expect_true("is_object_v<decltype(nullptr)>", asc::std::is_object_v<decltype(nullptr)>);

    // array type
    expect_true("is_object_v<int[5]>", asc::std::is_object_v<int[5]>);

    // class type
    expect_true("is_object_v<S>", asc::std::is_object_v<S>);

    // union type
    expect_true("is_object_v<U>", asc::std::is_object_v<U>);

    // non-object types
    expect_false("is_object_v<void>", asc::std::is_object_v<void>);
    expect_false("is_object_v<int&>", asc::std::is_object_v<int&>);
    expect_false("is_object_v<int()>", asc::std::is_object_v<int()>);

    // struct template
    expect_true("is_object<int>::value", asc::std::is_object<int>::value);
    expect_false("is_object<void>::value", asc::std::is_object<void>::value);

    return g_failures == 0 ? 0 : 1;
}
