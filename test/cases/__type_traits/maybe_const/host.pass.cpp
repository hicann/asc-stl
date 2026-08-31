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

#include <asc/std/__type_traits/maybe_const.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][maybe_const] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

int main()
{
    // __maybe_const<true, T> should be const T
    expect_true("is_same<__maybe_const<true, int>, const int>",
        (std::is_same<asc::std::__maybe_const<true, int>, const int>::value));
    expect_true("is_same<__maybe_const<true, float>, const float>",
        (std::is_same<asc::std::__maybe_const<true, float>, const float>::value));
    expect_true("is_same<__maybe_const<true, double>, const double>",
        (std::is_same<asc::std::__maybe_const<true, double>, const double>::value));

    // __maybe_const<false, T> should be T (non-const)
    expect_true(
        "is_same<__maybe_const<false, int>, int>", (std::is_same<asc::std::__maybe_const<false, int>, int>::value));
    expect_true("is_same<__maybe_const<false, float>, float>",
        (std::is_same<asc::std::__maybe_const<false, float>, float>::value));
    expect_true("is_same<__maybe_const<false, double>, double>",
        (std::is_same<asc::std::__maybe_const<false, double>, double>::value));

    // __maybe_const<true, const T> should be const T (already const)
    expect_true("is_same<__maybe_const<true, const int>, const int>",
        (std::is_same<asc::std::__maybe_const<true, const int>, const int>::value));

    // __maybe_const<false, const T> should be const T (preserves const)
    expect_true("is_same<__maybe_const<false, const int>, const int>",
        (std::is_same<asc::std::__maybe_const<false, const int>, const int>::value));

    // Test with pointer types: const applied to the pointer itself
    expect_true("is_same<__maybe_const<true, int*>, int* const>",
        (std::is_same<asc::std::__maybe_const<true, int*>, int* const>::value));
    expect_true(
        "is_same<__maybe_const<false, int*>, int*>", (std::is_same<asc::std::__maybe_const<false, int*>, int*>::value));

    return g_failures == 0 ? 0 : 1;
}
