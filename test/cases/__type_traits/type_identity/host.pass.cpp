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

#include <asc/std/__type_traits/type_identity.h>
#include <iostream>
#include <type_traits>

static int g_failures = 0;

template <typename T>
static void expect_eq(const char* expr, T got, T expected)
{
    bool ok = (got == expected);
    std::cout << "[host][type_identity] " << expr << " = " << got << " (expected " << expected << ") "
              << (ok ? "OK" : "FAIL") << std::endl;
    if (!ok)
        ++g_failures;
}

struct Empty {};

static void test_type_identity_int_type()
{
    // type_identity<int>::type is int
    {
        using T = asc::std::type_identity<int>::type;
        expect_eq("is_same<type_identity<int>::type, int>", std::is_same<T, int>::value, true);
    }
}

static void test_type_identity_int_int()
{
    // type_identity_t<int> is int
    {
        using T = asc::std::type_identity_t<int>;
        expect_eq("is_same<type_identity_t<int>, int>", std::is_same<T, int>::value, true);
    }
}

static void test_type_identity_float_type()
{
    // type_identity<float>::type is float
    {
        using T = asc::std::type_identity<float>::type;
        expect_eq("is_same<type_identity<float>::type, float>", std::is_same<T, float>::value, true);
    }
}

static void test_type_identity_float_float()
{
    // type_identity_t<float> is float
    {
        using T = asc::std::type_identity_t<float>;
        expect_eq("is_same<type_identity_t<float>, float>", std::is_same<T, float>::value, true);
    }
}

static void test_type_identity_empty_type()
{
    // type_identity<Empty>::type is Empty
    {
        using T = asc::std::type_identity<Empty>::type;
        expect_eq("is_same<type_identity<Empty>::type, Empty>", std::is_same<T, Empty>::value, true);
    }
}

static void test_type_identity_empty_empty()
{
    // type_identity_t<Empty> is Empty
    {
        using T = asc::std::type_identity_t<Empty>;
        expect_eq("is_same<type_identity_t<Empty>, Empty>", std::is_same<T, Empty>::value, true);
    }
}

static void test_type_identity_const_volatile()
{
    // type_identity with const/volatile
    {
        using T = asc::std::type_identity<const int>::type;
        expect_eq("is_same<type_identity<const int>::type, const int>", std::is_same<T, const int>::value, true);
    }
    {
        using T = asc::std::type_identity_t<volatile int>;
        expect_eq("is_same<type_identity_t<volatile int>, volatile int>", std::is_same<T, volatile int>::value, true);
    }
}

static void test_type_identity_pointer()
{
    // type_identity with pointer
    {
        using T = asc::std::type_identity<int*>::type;
        expect_eq("is_same<type_identity<int*>::type, int*>", std::is_same<T, int*>::value, true);
    }
    {
        using T = asc::std::type_identity_t<int*>;
        expect_eq("is_same<type_identity_t<int*>, int*>", std::is_same<T, int*>::value, true);
    }
}

static void test_type_identity_reference()
{
    // type_identity with reference
    {
        using T = asc::std::type_identity<int&>::type;
        expect_eq("is_same<type_identity<int&>::type, int&>", std::is_same<T, int&>::value, true);
    }
    {
        using T = asc::std::type_identity_t<int&&>;
        expect_eq("is_same<type_identity_t<int&&>, int&&>", std::is_same<T, int&&>::value, true);
    }
}

static void test_type_identity_array_type()
{
    // type_identity with array type
    {
        using T = asc::std::type_identity<int[3]>::type;
        expect_eq("is_same<type_identity<int[3]>::type, int[3]>", std::is_same<T, int[3]>::value, true);
    }
    {
        using T = asc::std::type_identity_t<int[3]>;
        expect_eq("is_same<type_identity_t<int[3]>, int[3]>", std::is_same<T, int[3]>::value, true);
    }
}

static void test_type_identity_used_establish()
{
    // type_identity used to establish non-deduced context (its canonical use case)
    {
        auto f = [](auto&& x, asc::std::type_identity_t<decltype(x)> y) { return x + y; };
        int result = f(10, 20);
        expect_eq("non-deduced context f(10, 20)", result, 30);
    }
}

static void test_type_identity_void()
{
    // type_identity with void
    {
        using T = asc::std::type_identity<void>::type;
        expect_eq("is_same<type_identity<void>::type, void>", std::is_same<T, void>::value, true);
    }
    {
        using T = asc::std::type_identity_t<void>;
        expect_eq("is_same<type_identity_t<void>, void>", std::is_same<T, void>::value, true);
    }
}

int main()
{
    test_type_identity_int_type();
    test_type_identity_int_int();
    test_type_identity_float_type();
    test_type_identity_float_float();
    test_type_identity_empty_type();
    test_type_identity_empty_empty();
    test_type_identity_const_volatile();
    test_type_identity_pointer();
    test_type_identity_reference();
    test_type_identity_array_type();
    test_type_identity_used_establish();
    test_type_identity_void();

    return g_failures == 0 ? 0 : 1;
}
