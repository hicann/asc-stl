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

#include <asc/std/__type_traits/is_nothrow_destructible.h>
#include <iostream>

static int g_failures = 0;

static void expect_true(const char* expr, bool got)
{
    std::cout << "[host][is_nothrow_destructible] " << expr << " = " << (got ? "true" : "false") << " (expected true) "
              << (got ? "OK" : "FAIL") << std::endl;
    if (!got)
        ++g_failures;
}

static void expect_false(const char* expr, bool got)
{
    std::cout << "[host][is_nothrow_destructible] " << expr << " = " << (got ? "true" : "false") << " (expected false) "
              << (!got ? "OK" : "FAIL") << std::endl;
    if (got)
        ++g_failures;
}

struct NoexceptDtor {
    ~NoexceptDtor() noexcept
    {}
};

struct ThrowingDtor {
    ~ThrowingDtor() noexcept(false)
    {}
};

struct ImplicitNoexceptDtor {
    // implicitly noexcept destructor
};

struct ProtectedDtorProbe {
protected:
    ~ProtectedDtorProbe()
    {}
    // 本测试专有标记成员, 与 destructible 概念测试中的同名场景去重
    static constexpr int __nothrow_probe_tag = 2;
};

struct PrivateDtorProbe {
private:
    ~PrivateDtorProbe()
    {}
    // 本测试专有标记成员, 与 destructible 概念测试中的同名场景去重
    static constexpr int __private_probe_tag = 3;
};

int main()
{
    // Basic scalar types - all nothrow destructible
    expect_true("is_nothrow_destructible_v<int>", asc::std::is_nothrow_destructible_v<int>);
    expect_true("is_nothrow_destructible_v<float>", asc::std::is_nothrow_destructible_v<float>);
    expect_true("is_nothrow_destructible_v<double>", asc::std::is_nothrow_destructible_v<double>);
    expect_true("is_nothrow_destructible_v<char>", asc::std::is_nothrow_destructible_v<char>);
    expect_true("is_nothrow_destructible_v<bool>", asc::std::is_nothrow_destructible_v<bool>);
    expect_true("is_nothrow_destructible_v<long>", asc::std::is_nothrow_destructible_v<long>);
    expect_true("is_nothrow_destructible_v<unsigned>", asc::std::is_nothrow_destructible_v<unsigned>);

    // const/volatile qualified scalars
    expect_true("is_nothrow_destructible_v<const int>", asc::std::is_nothrow_destructible_v<const int>);
    expect_true("is_nothrow_destructible_v<volatile int>", asc::std::is_nothrow_destructible_v<volatile int>);

    // Pointer types
    expect_true("is_nothrow_destructible_v<int*>", asc::std::is_nothrow_destructible_v<int*>);
    expect_true("is_nothrow_destructible_v<void*>", asc::std::is_nothrow_destructible_v<void*>);

    // Reference types - always true
    expect_true("is_nothrow_destructible_v<int&>", asc::std::is_nothrow_destructible_v<int&>);
    expect_true("is_nothrow_destructible_v<int&&>", asc::std::is_nothrow_destructible_v<int&&>);
    expect_true("is_nothrow_destructible_v<NoexceptDtor&>", asc::std::is_nothrow_destructible_v<NoexceptDtor&>);
    expect_true("is_nothrow_destructible_v<ThrowingDtor&>", asc::std::is_nothrow_destructible_v<ThrowingDtor&>);
    expect_true("is_nothrow_destructible_v<NoexceptDtor&&>", asc::std::is_nothrow_destructible_v<NoexceptDtor&&>);

    // Array types
    expect_true("is_nothrow_destructible_v<int[3]>", asc::std::is_nothrow_destructible_v<int[3]>);
    expect_true("is_nothrow_destructible_v<NoexceptDtor[5]>", asc::std::is_nothrow_destructible_v<NoexceptDtor[5]>);
    expect_false("is_nothrow_destructible_v<ThrowingDtor[5]>", asc::std::is_nothrow_destructible_v<ThrowingDtor[5]>);
    expect_false("is_nothrow_destructible_v<int[]>", asc::std::is_nothrow_destructible_v<int[]>);

    // void - not destructible
    expect_false("is_nothrow_destructible_v<void>", asc::std::is_nothrow_destructible_v<void>);

    // Function types - not destructible
    expect_false("is_nothrow_destructible_v<void()>", asc::std::is_nothrow_destructible_v<void()>);

    // Class types
    expect_true("is_nothrow_destructible_v<NoexceptDtor>", asc::std::is_nothrow_destructible_v<NoexceptDtor>);
    expect_false("is_nothrow_destructible_v<ThrowingDtor>", asc::std::is_nothrow_destructible_v<ThrowingDtor>);
    expect_true(
        "is_nothrow_destructible_v<ImplicitNoexceptDtor>", asc::std::is_nothrow_destructible_v<ImplicitNoexceptDtor>);
    expect_false(
        "is_nothrow_destructible_v<ProtectedDtorProbe>", asc::std::is_nothrow_destructible_v<ProtectedDtorProbe>);
    expect_false("is_nothrow_destructible_v<PrivateDtorProbe>", asc::std::is_nothrow_destructible_v<PrivateDtorProbe>);

    // ::value form
    expect_true("is_nothrow_destructible<int>::value", asc::std::is_nothrow_destructible<int>::value);
    expect_false("is_nothrow_destructible<void>::value", asc::std::is_nothrow_destructible<void>::value);
    expect_true("is_nothrow_destructible<NoexceptDtor>::value", asc::std::is_nothrow_destructible<NoexceptDtor>::value);
    expect_false(
        "is_nothrow_destructible<ThrowingDtor>::value", asc::std::is_nothrow_destructible<ThrowingDtor>::value);

    return g_failures == 0 ? 0 : 1;
}
