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

#include <asc/std/__type_traits/copy_cv.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename A, typename B>
static void expect_same(const char* expr)
{
    bool ok = std::is_same<A, B>::value;
    std::cout << "[host][copy_cv] " << expr << " => " << (ok ? "same" : "DIFFERENT") << " (expected same) "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct CustomType {};

int main()
{
    // Basic: copy nothing
    expect_same<asc::std::__copy_cv_t<int, int>, int>("__copy_cv_t<int, int>");

    // Copy const
    expect_same<asc::std::__copy_cv_t<const int, int>, const int>("__copy_cv_t<const int, int>");

    // Copy volatile
    expect_same<asc::std::__copy_cv_t<volatile int, int>, volatile int>("__copy_cv_t<volatile int, int>");

    // Copy const volatile
    expect_same<asc::std::__copy_cv_t<const volatile int, int>, const volatile int>(
        "__copy_cv_t<const volatile int, int>");

    // From has no cv, To already has const -> result is const (no extra cv added)
    expect_same<asc::std::__copy_cv_t<int, const int>, const int>("__copy_cv_t<int, const int>");

    // From const, To volatile -> const volatile
    expect_same<asc::std::__copy_cv_t<const int, volatile int>, const volatile int>(
        "__copy_cv_t<const int, volatile int>");

    // From volatile, To const -> const volatile
    expect_same<asc::std::__copy_cv_t<volatile int, const int>, const volatile int>(
        "__copy_cv_t<volatile int, const int>");

    // From const volatile, To const -> const volatile
    expect_same<asc::std::__copy_cv_t<const volatile int, const int>, const volatile int>(
        "__copy_cv_t<const volatile int, const int>");

    // Custom type
    expect_same<asc::std::__copy_cv_t<const CustomType, CustomType>, const CustomType>(
        "__copy_cv_t<const CustomType, CustomType>");
    expect_same<asc::std::__copy_cv_t<volatile CustomType, CustomType>, volatile CustomType>(
        "__copy_cv_t<volatile CustomType, CustomType>");
    expect_same<asc::std::__copy_cv_t<const volatile CustomType, CustomType>, const volatile CustomType>(
        "__copy_cv_t<const volatile CustomType, CustomType>");

    // Copy cv onto a pointer type
    expect_same<asc::std::__copy_cv_t<const int, int*>, int* const>("__copy_cv_t<const int, int*>");
    expect_same<asc::std::__copy_cv_t<volatile int, int*>, int* volatile>("__copy_cv_t<volatile int, int*>");
    expect_same<asc::std::__copy_cv_t<const volatile int, int*>, int* const volatile>(
        "__copy_cv_t<const volatile int, int*>");

    return g_failures == 0 ? 0 : 1;
}
