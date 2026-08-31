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

#include <asc/std/__fwd/span.h>
#include <iostream>
#include <cstddef>
#include <cstdint>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][span] " << expr << " = " << got << " (expected " << expected << ") " << (ok ? "OK" : "FAIL")
              << std::endl;
    if (!ok)
        ++g_failures;
}

static void expect_true(const char* expr, bool cond)
{
    std::cout << "[host][span] " << expr << " = " << (cond ? "true" : "false") << " (expected true) "
              << (cond ? "OK" : "FAIL") << std::endl;
    if (!cond)
        ++g_failures;
}

static void expect_false(const char* expr, bool cond)
{
    std::cout << "[host][span] " << expr << " = " << (cond ? "true" : "false") << " (expected false) "
              << (cond ? "FAIL" : "OK") << std::endl;
    if (cond)
        ++g_failures;
}

int main()
{
    // 1. dynamic_extent equals SIZE_MAX
    expect_eq("dynamic_extent", asc::std::dynamic_extent, static_cast<size_t>(-1));
    expect_eq("dynamic_extent == SIZE_MAX", asc::std::dynamic_extent, SIZE_MAX);

    // 2. __is_asc_std_span_v: true for span specializations
    expect_true("__is_asc_std_span_v<span<int>>", asc::std::__is_asc_std_span_v<asc::std::span<int>>);
    expect_true("__is_asc_std_span_v<span<int, 4>>", asc::std::__is_asc_std_span_v<asc::std::span<int, 4>>);
    expect_true("__is_asc_std_span_v<span<double>>", asc::std::__is_asc_std_span_v<asc::std::span<double>>);
    expect_true("__is_asc_std_span_v<span<float, dynamic_extent>>",
        asc::std::__is_asc_std_span_v<asc::std::span<float, asc::std::dynamic_extent>>);

    // 3. __is_asc_std_span_v: false for non-span types
    expect_false("__is_asc_std_span_v<int>", asc::std::__is_asc_std_span_v<int>);
    expect_false("__is_asc_std_span_v<double>", asc::std::__is_asc_std_span_v<double>);
    expect_false("__is_asc_std_span_v<size_t>", asc::std::__is_asc_std_span_v<size_t>);

    // 4. span can be used as a forward-declared type (pointer / reference)
    using SpanInt = asc::std::span<int>;
    SpanInt* p = nullptr;
    (void)p;
    expect_true("span<int>* is usable as type", true);

    return g_failures == 0 ? 0 : 1;
}
